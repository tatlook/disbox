#if !defined(_SMOKU_DISBOX_H)
#define _SMOKU_DISBOX_H

extern char disbox_x; /* 棋盘X轴数目 */
extern char disbox_y; /* 棋盘Y轴数目 */
#define DISBOX_M_X 20 /* 方块最大列数 */
#define DISBOX_M_Y 20 /* 方块最大行数 */
#define DISBOX_D_X 15 /* 方块默认列数 */
#define DISBOX_D_Y 15 /* 方块默认行数 */
#define DISBOX_S (disbox_x * disbox_y) /* 方块数量 */
#define DISBOX_M_S (DISBOX_M_X * DISBOX_M_Y) /* 方块最大数量 */
#define DISBOX_D_S (DISBOX_D_X * DISBOX_D_Y) /* 方块默认数量 */

extern GtkWidget *disbox_boxs[DISBOX_M_S];

extern unsigned int color_number;

#endif // _SMOKU_DISBOX_H
