#if !defined(_SMOKU_DISBOX_H)
#define _SMOKU_DISBOX_H

#define DISBOX_X 15 /* 棋盘X轴数目 */
#define DISBOX_Y 15 /* 棋盘Y轴数目 */
#define DISBOX_S (DISBOX_X * DISBOX_Y) /* 方块数量 */

extern GtkWidget *disbox_boxs[DISBOX_S];

#endif // _SMOKU_DISBOX_H
