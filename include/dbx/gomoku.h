/* Disbox - The Disable Box Game.
 * Copyright (C) 2021 Tatlook
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined(_SMOKU_DISBOX_H)
#define _SMOKU_DISBOX_H


extern char disbox_x; /* 棋盘X轴数目 */
extern char disbox_y; /* 棋盘Y轴数目 */
#define DISBOX_M_X 20 /* 方块最大列数 */
#define DISBOX_M_Y 20 /* 方块最大行数 */
#define DISBOX_D_X 20 /* 方块默认列数 */
#define DISBOX_D_Y 20 /* 方块默认行数 */
#define DISBOX_S (disbox_x * disbox_y) /* 方块数量 */
#define DISBOX_M_S (DISBOX_M_X * DISBOX_M_Y) /* 方块最大数量 */
#define DISBOX_D_S (DISBOX_D_X * DISBOX_D_Y) /* 方块默认数量 */
#define DISBOX_FAIL_TIME_COUNT 100 /* 输掉的时间（秒） */

extern int disbox_tm_count;

extern GtkWidget *disbox_boxs[DISBOX_M_S];

extern unsigned int color_number;

#include <stdbool.h>

/* 其他功能 */

/* 出去才变色 */
extern bool disbox_out_change;
/* 进入即变色 */
extern bool disbox_in_change;
/* 在箱子上停留时间过长就输 */
extern bool disbox_fail_longtime_at_box;
/* 不允许光标离开窗口 */
extern bool disbox_no_outside;

#endif // _SMOKU_DISBOX_H
