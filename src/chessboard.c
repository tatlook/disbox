#include <dbx/bootcontainer.h>
#include <dbx/gomoku.h>
#include <dbx/debug.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

GtkWidget *disbox_boxs[DISBOX_M_S];
char disbox_colorno[DISBOX_M_S];
static GdkColor disnohave_color = {0, 0xff00, 0xff0f, 0xfff0};

char disbox_x = DISBOX_D_X;
char disbox_y = DISBOX_D_Y;

/* 最多颜色数 */
#define COLOR_NUMBER_MAX 10
/* 有几种颜色 */
unsigned int color_number = COLOR_NUMBER_MAX / 3;

/* 没有颜色的颜色号码 */
#define DISBOX_HAVENT_COLOR 0
/* 随机生成的颜色模板 */
static GdkColor disbox_colors[COLOR_NUMBER_MAX];

/* 当前盒子的数量 */
static unsigned int disbox_count = 0;
/* 移动次数 */
static unsigned long disbox_move_count = 0;

static gboolean win_dialog_close() {
    init_chessboard();
    return FALSE;
}

static void do_win() {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(disui_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "恭喜，您已胜利：\n"
        "\t翻动次数：%d", disbox_move_count
    );
    gtk_widget_show_all(dialog);	/* 显示对话框和所有控件 */

    g_signal_connect(G_OBJECT(dialog), "delete_event",
        G_CALLBACK(win_dialog_close), NULL);
}

static gboolean mouse_moved(GtkWidget *box,
                    GdkEvent  *event,
                    char *color) {
    /* 挪了一次 */
    disbox_move_count++;
    /* 此时没有颜色意味着数量即将增多。*/
    if (*color == DISBOX_HAVENT_COLOR) {
        disbox_count++;
    }
    /* 一般情况下颜色数直接加一就可以了，但... */
    if (*color == color_number) {
        /* ...到达最后时就又归零了。 */
        *color = DISBOX_HAVENT_COLOR;
    } else {
        (*color) ++;
    }
    /* 此时没有颜色意味着数量减少。*/
    if (*color == DISBOX_HAVENT_COLOR) {
        disbox_count--;
    }
    /* 重新设定颜色 */
    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &disbox_colors[(*color)]);
    /* 全部颜色都没有了，就结束。 */
    if (disbox_count == 0) {
        do_win();
    }
    dbgprintf(":%d", disbox_count);
    return TRUE;
}

void init_chessboard() {
    /* 初始化游戏信息 */
    disbox_count = 0;
    disbox_move_count = 0;
    /* 初始化没有颜色。 */
    memcpy(&disbox_colors, &disnohave_color, sizeof(GdkColor));
    /* 初始化其他颜色。 */
    for (int i = 1; i < color_number; i++) {
        static GdkColor color = (GdkColor) { .pixel = 0 };
        color.red = rand() % 0xFFFF;
        color.green = rand() % 0xFFFF;
        color.blue = rand() % 0xFFFF;
        /* 拷贝过去 */
        memcpy(&disbox_colors[i], &color, sizeof(GdkColor));
    }
    
    /* 初始化所有方块 */
    for (int i = 0; i < DISBOX_S; i++) {
        /* 随机颜色 */
        char colorn = rand() % color_number;
        disbox_colorno[i] = colorn;
        if (colorn != DISBOX_HAVENT_COLOR) {
            disbox_count++;
        }
        gtk_widget_modify_bg(disbox_boxs[i], GTK_STATE_NORMAL, &disbox_colors[colorn]);
    }
}


static GtkWidget *chessboard = NULL;
static bool chess_first_init = true;

GtkWidget *create_chessboard() {
    /* 有可能是重新制作 *
    if (!chess_first_init) {
        gtk_container_remove(GTK_CONTAINER(disui_main_panel), chessboard);
       // gtk_widget_destroy(chessboard);
    }*/
    chessboard = gtk_table_new(disbox_x, disbox_y, TRUE);	// 表格布局
    /* 有可能是重新制作 *
    if (!chess_first_init) {
        gtk_container_add(GTK_CONTAINER(disui_main_panel), chessboard);
    }

    /* 创建方块 */
    if (chess_first_init) for (int i = 0; i < DISBOX_M_S; i++) {
        disbox_boxs[i] = gtk_button_new();
        g_signal_connect(
            disbox_boxs[i],
            "enter-notify-event",
            G_CALLBACK(mouse_moved),
            disbox_colorno + i
        );
    } else for (int i = 0; i < DISBOX_S; i++) {
        gtk_container_remove(GTK_CONTAINER(chessboard), disbox_boxs[i]);
    }

    /* 方块放到表格上 */
    for (int i = 0, go_x = 0, go_y = 0; i < DISBOX_S; i++, go_x++) {
        /* 换行 */
        if (go_x >= disbox_y) {
            go_x = 0;
            go_y++;
        }
        /* 方块放到表格上 */
        gtk_table_attach_defaults(
            GTK_TABLE(chessboard),
            disbox_boxs[i],
            go_x, go_x + 1, go_y, go_y + 1
        );
    }
    /* 初始化所有方块 */
    init_chessboard();
    chess_first_init = false;
    return chessboard; /* 返回值用于加到窗口上 */
}
