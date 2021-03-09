#include <smoku/bootcontainer.h>
#include <smoku/gomoku.h>
#include <smoku/debug.h>

/* 棋子点击事件处理函数 */
static gboolean pieces_mouse_press(GtkWidget *piece, GdkEventButton *event, gomoku_status_t *status);
/* 绘制空棋子回调函数 */
static gboolean draw_chessboar_sub(GtkWidget *chessboard_sub, GdkEventExpose *event, gpointer data);

GtkWidget *gomoku_piece_black_image;
GtkWidget *gomoku_piece_write_image;

GtkWidget *create_chessboard() {
    GtkWidget *chessboard = gtk_table_new(GOMOKU_X, GOMOKU_Y, TRUE);	// 表格布局
     
    
    /* 初始化所有棋子 */
    for (int i = 0, go_x = 0, go_y = 0; i < GOMOKU_S; i++, go_x++) {
        /* 捎带角初始化gomoku_map */
        gomoku_mapp[i] = GOMOKU_HAVENT;
        /* 换行 */
        if (go_x >= GOMOKU_Y) {
            go_x = 0;
            go_y++;
        }
        /* 创建棋子 */
        gomoku_pieces[i] = gtk_button_new();
        /* 画棋子那的棋盘 */
        g_signal_connect(gomoku_pieces[i],
            "expose-event",
            G_CALLBACK(draw_chessboar_sub),
            NULL
        );
        /* 棋子放到表格上 */
        gtk_table_attach_defaults(
            GTK_TABLE(chessboard),
            gomoku_pieces[i],
            go_x, go_x + 1, go_y, go_y + 1
        );
        /* 给棋子注册点击事件处理程序 */
        g_signal_connect(gomoku_pieces[i],
            "button-press-event",
            G_CALLBACK(pieces_mouse_press),
            gomoku_mapp + i
        );
    }
    return chessboard; /* 返回值用于加到窗口上 */
}

static gboolean pieces_mouse_press(GtkWidget *piece, GdkEventButton *event, gomoku_status_t *status) {
    dbgputs("HHHHA1");
    /* 不该用户下 */
    if (gomoku_own == GOOWN_SMOKU) {
        return TRUE;
        dbgputs("HHHHA2");
    }
    dbgputs("HHHHA3");
    /* 已经有子了 */
// TODO: 直接注销事件处理程序
    if (*status != GOMOKU_HAVENT) {
        return TRUE;
        dbgputs("HHHHA4");
    }
    /* 该程序下了 */
    gomoku_own = GOOWN_SMOKU;

    /* 给用户下白棋 */
    *status = GOMOKU_WHITE;
    /* 子落到上面去 */
    gtk_button_set_image(GTK_BUTTON(piece), gomoku_piece_write_image);

    calculation();
    return TRUE;
}

static gboolean draw_chessboar_sub(GtkWidget *chessboard_sub, GdkEventExpose *event, gpointer data) {
    cairo_t *cr = gdk_cairo_create(chessboard_sub->window);	// 创建cairo环境

    cairo_set_source_rgb(cr, 0, 1, 1);
    cairo_set_line_width(cr, CHESSBOARD_LINE_WIDTH);
    
    /* 画横线 */
    cairo_move_to(cr, 0, CHESSBOARD_LINE_SPACING / 2);
    cairo_line_to(cr, CHESSBOARD_LINE_SPACING, CHESSBOARD_LINE_SPACING / 2);

    /* 画竖线 */
    cairo_move_to(cr, CHESSBOARD_LINE_SPACING / 2, 0);
    cairo_line_to(cr, CHESSBOARD_LINE_SPACING / 2, CHESSBOARD_LINE_SPACING);

    cairo_paint(cr);

    cairo_destroy(cr);	// 回收所有Cairo环境所占用的内存资源
    return FALSE;
}
