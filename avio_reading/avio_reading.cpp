// avio_reading.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
/**
 * @file
 * libavformat AVIOContext API example.
 *
 * Make libavformat demuxer access media content through a custom
 * AVIOContext read callback.
 * @example avio_reading.c
 */

extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/file.h>
}

#include <iostream>

struct buffer_data {
	uint8_t *ptr;
	size_t size; ///< size left in the buffer
};

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

int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";

	AVFormatContext *fmt_ctx = NULL;
	AVIOContext *avio_ctx = NULL;
	uint8_t *buffer = NULL, *avio_ctx_buffer = NULL;
	size_t buffer_size, avio_ctx_buffer_size = 4096*8*10;
	char *input_filename = NULL;
	int ret = 0;
	struct buffer_data bd = { 0 };

	if (argc != 2) {
		fprintf(stderr, "usage: %s input_file\n"
			"API example program to show how to read from a custom buffer "
			"accessed through AVIOContext.\n", argv[0]);
		return 1;
	}
	input_filename = argv[1];

	/* slurp file content into buffer */
	ret = av_file_map(input_filename, &buffer, &buffer_size, 0, NULL);
	if (ret < 0)
		goto end;

	/* fill opaque structure used by the AVIOContext read callback */
	bd.ptr = buffer;
	bd.size = buffer_size;

	if (!(fmt_ctx = avformat_alloc_context())) {
		ret = AVERROR(ENOMEM);
		goto end;
	}

	avio_ctx_buffer = (uint8_t *)av_malloc(avio_ctx_buffer_size);
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
	fmt_ctx->pb = avio_ctx;

	ret = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
	if (ret < 0) {
		fprintf(stderr, "Could not open input\n");
		goto end;
	}

	ret = avformat_find_stream_info(fmt_ctx, NULL);
	if (ret < 0) {
		fprintf(stderr, "Could not find stream information\n");
		goto end;
	}

	av_dump_format(fmt_ctx, 0, input_filename, 0);

	AVPacket pkt;
	while (1) {
		ret = av_read_frame(fmt_ctx, &pkt);
		if (ret < 0)
			break;
	}

end:
	avformat_close_input(&fmt_ctx);

	/* note: the internal buffer could have changed, and be != avio_ctx_buffer */
	if (avio_ctx)
		av_freep(&avio_ctx->buffer);
	avio_context_free(&avio_ctx);

	av_file_unmap(buffer, buffer_size);

	if (ret < 0) {
		//fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
		return 1;
	}

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
