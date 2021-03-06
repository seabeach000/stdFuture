// mxfRemux.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libavutil/mathematics.h>
#include <libavutil/file.h>
}

//c++编译环境不允许这样赋值 解决方案右键，属性c / c++那一列的高级，编译为c这个问题就能解决了
//如果想要用c++编译就分开操作，先生成左值表达式再作为右值进行赋值 int a[2] = { 10,20 }; pt1 = a;

//char av_error[AV_ERROR_MAX_STRING_SIZE] = { 0 };
//#define av_err2str(errnum) \
    //av_make_error_string(av_error, AV_ERROR_MAX_STRING_SIZE, errnum)

struct buffer_data {
	uint8_t *ptr;
	size_t size; ///< size left in the buffer
};

static void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt, const char *tag)
{
	AVRational *time_base = &fmt_ctx->streams[pkt->stream_index]->time_base;

	//printf("%s: pts:%s pts_time:%s dts:%s dts_time:%s duration:%s duration_time:%s stream_index:%d\n",
	//	tag,
	//	av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, time_base),
	//	av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, time_base),
	//	av_ts2str(pkt->duration), av_ts2timestr(pkt->duration, time_base),
	//	pkt->stream_index);
}

static int read_packet(void *opaque, uint8_t *buf, int buf_size)
{
	struct buffer_data *bd = (struct buffer_data *)opaque;
	buf_size = FFMIN(buf_size, bd->size);

	if (!buf_size)
		return AVERROR_EOF;
	printf("ptr:%p size:%zu\n", bd->ptr, bd->size);

	/* copy internal buffer data to buf */
	memcpy(buf, bd->ptr, buf_size);
	bd->ptr += buf_size;
	bd->size -= buf_size;

	return buf_size;
}
int main(int argc, char **argv)
{
	AVOutputFormat *ofmt = NULL;
	AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
	AVPacket pkt;

	//二、自定义释放器
	//用如下方式使用带自定义资源释放的unique_ptr
	//auto delete_Investment = [](Investment* pInv)
	//{
	//	pInv->getObjectType();
	//	delete pInv;
	//};
	//unique_ptr<Investment, decltype(delete_Investment)> pInvest(nullptr, delete_Investment);
	//或者也可以使用函数指针
	//void deleteInv(Investment* pInv) {}
	//std::unique_ptr<Investment, void(*)(Investment*)>ptr(nullptr, deleteInv);

	//std::unique_ptr<AVPacket, std::function<void(AVPacket*)>> packet{
	//			new AVPacket,
	//			[](AVPacket* p) { av_packet_unref(p); delete p; } };

	const char *in_filename, *out_filename;
	int ret, i;
	int stream_index = 0;
	int *stream_mapping = NULL;
	int stream_mapping_size = 0;

	if (argc < 3) {
		printf("usage: %s input output\n"
			"API example program to remux a media file with libavformat and libavcodec.\n"
			"The output format is guessed according to the file extension.\n"
			"\n", argv[0]);
		return 1;
	}

	in_filename = argv[1];
	out_filename = argv[2];

	//wxg20201204
	AVDictionary* options = nullptr;
	//av_dict_set(&options, "rtbufsize", "655360", 0);
	//av_dict_set(&options, "packetsize", "655360", 0);  //没找到相应的参数

	/*
	AVIOContext *avio_ctx = NULL;
	uint8_t *buffer = NULL, *avio_ctx_buffer = NULL;
	size_t buffer_size, avio_ctx_buffer_size = 32768*20;
	struct buffer_data bd = { 0 };
	ret = av_file_map(in_filename, &buffer, &buffer_size, 0, nullptr);
	if (ret < 0)
		goto end;
	//* fill opaque structure used by the AVIOContext read callback 
	bd.ptr = buffer;
	bd.size = buffer_size;

	if (!(ifmt_ctx = avformat_alloc_context())) {
		ret = AVERROR(ENOMEM);
		goto end;
	}

	avio_ctx_buffer = (uint8_t*)av_malloc(avio_ctx_buffer_size);
	if (!avio_ctx_buffer) {
		ret = AVERROR(ENOMEM);
		goto end;
	}

	avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size,
		0, &bd, &read_packet, NULL, NULL);
	if (!avio_ctx) {
		ret = AVERROR(ENOMEM);
		goto end;
	}
	ifmt_ctx->pb = avio_ctx;
	if ((ret = avformat_open_input(&ifmt_ctx, nullptr, 0, &options)) < 0) {
		fprintf(stderr, "Could not open input file '%s'", in_filename);
		goto end;
	}
	*/
	//wxgend

	av_log_set_level(AV_LOG_DEBUG);

	if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, &options)) < 0) {
		fprintf(stderr, "Could not open input file '%s'", in_filename);
		goto end;
	}

	av_dump_format(ifmt_ctx, 0, in_filename, 0);

	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
	if (!ofmt_ctx) {
		fprintf(stderr, "Could not create output context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}

	stream_mapping_size = ifmt_ctx->nb_streams;
	stream_mapping = (int*)av_mallocz_array(stream_mapping_size, sizeof(*stream_mapping));
	if (!stream_mapping) {
		ret = AVERROR(ENOMEM);
		goto end;
	}

	ofmt = ofmt_ctx->oformat;

	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
		AVStream *out_stream;
		AVStream *in_stream = ifmt_ctx->streams[i];
		AVCodecParameters *in_codecpar = in_stream->codecpar;

		if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
			in_codecpar->codec_type != AVMEDIA_TYPE_SUBTITLE) {
			stream_mapping[i] = -1;
			continue;
		}

		stream_mapping[i] = stream_index++;

		out_stream = avformat_new_stream(ofmt_ctx, NULL);
		if (!out_stream) {
			fprintf(stderr, "Failed allocating output stream\n");
			ret = AVERROR_UNKNOWN;
			goto end;
		}

		ret = avcodec_parameters_copy(out_stream->codecpar, in_codecpar);

		//wxg20180815
		out_stream->time_base = in_stream->time_base;

		if (ret < 0) {
			fprintf(stderr, "Failed to copy codec parameters\n");
			goto end;
		}
		out_stream->codecpar->codec_tag = 0;
	}

	av_dump_format(ofmt_ctx, 0, out_filename, 1);

	if (!(ofmt->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);
		if (ret < 0) {
			fprintf(stderr, "Could not open output file '%s'", out_filename);
			goto end;
		}
	}
	
	ret = avformat_write_header(ofmt_ctx, NULL);
	if (ret < 0) {
		fprintf(stderr, "Error occurred when opening output file\n");
		goto end;
	}

	int aa = avformat_seek_file(
		ifmt_ctx,
		0,
		0,
		39,
		1000,
		AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_ANY | AVSEEK_FLAG_FRAME);

	while (1) {
		AVStream *in_stream, *out_stream;

		ret = av_read_frame(ifmt_ctx, &pkt);
		if (ret < 0)
			break;

		in_stream = ifmt_ctx->streams[pkt.stream_index];
		if (pkt.stream_index >= stream_mapping_size ||
			stream_mapping[pkt.stream_index] < 0) {
			av_packet_unref(&pkt);
			continue;
		}

		pkt.stream_index = stream_mapping[pkt.stream_index];
		out_stream = ofmt_ctx->streams[pkt.stream_index];
		log_packet(ifmt_ctx, &pkt, "in");

		/* copy packet */
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, AVRounding(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		log_packet(ofmt_ctx, &pkt, "out");

		ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
		if (ret < 0) {
			fprintf(stderr, "Error muxing packet\n");
			break;
		}
		av_packet_unref(&pkt);
	}
	av_write_trailer(ofmt_ctx);

end:

	avformat_close_input(&ifmt_ctx);

	/* close output */
	if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
		avio_closep(&ofmt_ctx->pb);
	avformat_free_context(ofmt_ctx);

	av_freep(&stream_mapping);

	if (ret < 0 && ret != AVERROR_EOF) {
		//fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
		return 1;
	}
    return 0;
}

