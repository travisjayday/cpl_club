#include "render_intrinsics.h"
#include <arm_neon.h>

bool cmp_mask(const unsigned int *src, const unsigned int *cache, const unsigned int simd_inc, int count) {
	const uint8x16_t bitMask = { 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1 };

	while (count >= simd_inc) {
		uint32x4_t v = vld1q_u32((const uint32x4_t*)src);
		uint32x4_t d = vld1q_u32((const uint32x4_t*)cache);
		uint32x4_t cmp = vceqq_u32(v,c);
		//vandp_u8(cmp, bitMask);
		//cmp = vpaddq_u8(cmp,cmp);
		//cmp = vaddq_u8

	}
	return false;
}
