#if !defined(_SMOKU_GOMOKU_H)
#define _SMOKU_GOMOKU_H

#define GOMOKU_X 15 /* 棋盘X轴数目 */
#define GOMOKU_Y 15 /* 棋盘Y轴数目 */
#define GOMOKU_S (GOMOKU_X * GOMOKU_Y) /* 棋子数量 */
/* 棋子坐标,C=棋子序列号 */
#define GOMOKU_XY(C) \
    (C / GOMOKU_Y), (C / GOMOKU_Y + 1), (C / GOMOKU_X), (C / GOMOKU_X + 1)

/* 棋子状态枚举 */
#define GOMOKU_HAVENT 0 /* 没有 */
#define GOMOKU_WHITE 1 /* 黑子 */
#define GOMOKU_BLACK 2 /* 白字 */
typedef char gomoku_status_t; /* 类型 */

/* 棋该谁下 */
extern enum gomoku_own_t {
    GOOWN_USER, /* 该用户了 */
    GOOWN_SMOKU /* 该程序了 */
} gomoku_own;

/* 棋子map */
extern gomoku_status_t gomoku_map[GOMOKU_X][GOMOKU_Y];
extern gomoku_status_t *gomoku_mapp;
extern GtkWidget *gomoku_pieces[GOMOKU_S];

void calculation();

#endif // _SMOKU_GOMOKU_H
