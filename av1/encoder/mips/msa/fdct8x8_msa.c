/*
 * Copyright (c) 2016, Alliance for Open Media. All rights reserved
 *
 * This source code is subject to the terms of the BSD 2 Clause License and
 * the Alliance for Open Media Patent License 1.0. If the BSD 2 Clause License
 * was not distributed with this source code in the LICENSE file, you can
 * obtain it at www.aomedia.org/license/software. If the Alliance for Open
 * Media Patent License 1.0 was not distributed with this source code in the
 * PATENTS file, you can obtain it at www.aomedia.org/license/patent.
 */

#include <assert.h>

#include "av1/common/enums.h"
#include "av1/encoder/mips/msa/fdct_msa.h"

void vp10_fht8x8_msa(const int16_t *input, int16_t *output, int32_t stride,
                     int32_t tx_type) {
  v8i16 in0, in1, in2, in3, in4, in5, in6, in7;

  LD_SH8(input, stride, in0, in1, in2, in3, in4, in5, in6, in7);
  SLLI_4V(in0, in1, in2, in3, 2);
  SLLI_4V(in4, in5, in6, in7, 2);

  switch (tx_type) {
    case DCT_DCT:
      VPX_FDCT8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2,
                         in3, in4, in5, in6, in7);
      VPX_FDCT8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      break;
    case ADST_DCT:
      VPX_ADST8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2,
                         in3, in4, in5, in6, in7);
      VPX_FDCT8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      break;
    case DCT_ADST:
      VPX_FDCT8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2,
                         in3, in4, in5, in6, in7);
      VPX_ADST8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      break;
    case ADST_ADST:
      VPX_ADST8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2,
                         in3, in4, in5, in6, in7);
      VPX_ADST8(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3, in4,
                in5, in6, in7);
      break;
    default: assert(0); break;
  }

  TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7, in0, in1, in2, in3,
                     in4, in5, in6, in7);
  SRLI_AVE_S_4V_H(in0, in1, in2, in3, in4, in5, in6, in7);
  ST_SH8(in0, in1, in2, in3, in4, in5, in6, in7, output, 8);
}