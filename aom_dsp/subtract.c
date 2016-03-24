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

#include <stdlib.h>

#include "./vpx_config.h"
#include "./vpx_dsp_rtcd.h"

#include "aom/vpx_integer.h"
#include "aom_ports/mem.h"

void vpx_subtract_block_c(int rows, int cols, int16_t *diff,
                          ptrdiff_t diff_stride, const uint8_t *src,
                          ptrdiff_t src_stride, const uint8_t *pred,
                          ptrdiff_t pred_stride) {
  int r, c;

  for (r = 0; r < rows; r++) {
    for (c = 0; c < cols; c++) diff[c] = src[c] - pred[c];

    diff += diff_stride;
    pred += pred_stride;
    src += src_stride;
  }
}

#if CONFIG_VPX_HIGHBITDEPTH
void vpx_highbd_subtract_block_c(int rows, int cols, int16_t *diff,
                                 ptrdiff_t diff_stride, const uint8_t *src8,
                                 ptrdiff_t src_stride, const uint8_t *pred8,
                                 ptrdiff_t pred_stride, int bd) {
  int r, c;
  uint16_t *src = CONVERT_TO_SHORTPTR(src8);
  uint16_t *pred = CONVERT_TO_SHORTPTR(pred8);
  (void)bd;

  for (r = 0; r < rows; r++) {
    for (c = 0; c < cols; c++) {
      diff[c] = src[c] - pred[c];
    }

    diff += diff_stride;
    pred += pred_stride;
    src += src_stride;
  }
}
#endif  // CONFIG_VPX_HIGHBITDEPTH