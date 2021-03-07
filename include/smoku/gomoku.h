#if !defined(_SMOKU_DISBOX_H)
#define _SMOKU_DISBOX_H

extern char disbox_x; /* 棋盘X轴数目 */
extern char disbox_y; /* 棋盘Y轴数目 */

#define DISBOX_D_X 5
#define DISBOX_D_Y 5
#define DISBOX_S (disbox_x * disbox_y) /* 方块数量 */
#define DISBOX_D_S (DISBOX_D_X * DISBOX_D_Y) /* 方块数量 */

extern GtkWidget *disbox_boxs[DISBOX_D_S];

extern unsigned int color_number;

#endif // _SMOKU_DISBOX_H
