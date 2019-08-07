// SIMD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<immintrin.h>
#include<stdio.h>

int main()
{
	long long aa = ~7ul;

	__m256 s1 = _mm256_set1_ps(1.0f);
	s1.m256_f32[0] = 0;
	for (int i = 0; i < 8; ++i)
	{
		s1.m256_f32[i] = i;
	}
	printf("the original order is:\n");
	for (int i = 0; i < 8; ++i)
	{
		printf("%f\t", s1.m256_f32[i]);
	}
	printf("\n");
	__m256 result = _mm256_permute2f128_ps(s1, s1, 0x01);
	printf("the contral is 0x01:\n");
	for (int i = 0; i < 8; ++i)
	{
		printf(" %f\t", result.m256_f32[i]);
	}
	printf("\n");
	printf("the contral is 0x00:\n");
	result = _mm256_permute2f128_ps(s1, s1, 0x00);
	for (int i = 0; i < 8; ++i)
	{
		printf("%f\t", result.m256_f32[i]);
	}
	printf("\n");
	printf("the contral is 0x10:\n");
	result = _mm256_permute2f128_ps(s1, s1, 0x10);
	for (int i = 0; i < 8; ++i)
	{
		printf("%f\t", result.m256_f32[i]);
	}
	printf("\n");
	printf("the contral is 0x11:\n");
	result = _mm256_permute2f128_ps(s1, s1, 0x11);
	for (int i = 0; i < 8; ++i)
	{
		printf("%f\t", result.m256_f32[i]);
	}
	getchar();
    return 0;
}

