#include <smoku/bootcontainer.h>
#include <smoku/gomoku.h>
#include <smoku/debug.h>
#include <stdbool.h>
#include <stdlib.h>

GtkWidget *disbox_boxs[DISBOX_S];
bool disbox_status[DISBOX_S];
static GdkColor disnohave_color = {0, 0xff00, 0xff0f, 0xfff0};
static GdkColor dishave_color = {0, 0xffff, 0x0000, 0x0000};

/* 当前盒子的数量 */
static unsigned int disbox_count = 0;
/* 移动次数 */
static unsigned long disbox_move_count = 0;

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
}

static gboolean mouse_moved(GtkWidget *box,
                    GdkEvent  *event,
                    bool *status) {
    disbox_move_count++;
    if (*status) {
        *status = false;
        disbox_count--;
        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &disnohave_color);
    } else {
        *status = true;
        disbox_count++;
        gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &dishave_color);
    }
    if (disbox_count == 0) {
        do_win();
    }
    return TRUE;
}

static void init_chessboard(GtkWidget *chessboard) {
    /* 初始化所有方块 */
    for (int i = 0; i < DISBOX_S; i++) {
        if (rand() < (RAND_MAX / 2)) {
            disbox_status[i] = false;
            gtk_widget_modify_bg(disbox_boxs[i], GTK_STATE_NORMAL, &disnohave_color);
        } else {
            disbox_status[i] = true;
            disbox_count++;
            gtk_widget_modify_bg(disbox_boxs[i], GTK_STATE_NORMAL, &dishave_color);
        }
    }
}

GtkWidget *create_chessboard() {
    GtkWidget *chessboard = gtk_table_new(DISBOX_X, DISBOX_Y, TRUE);	// 表格布局
    
    /* 创建方块 */
    for (int i = 0, go_x = 0, go_y = 0; i < DISBOX_S; i++, go_x++) {
        /* 换行 */
        if (go_x >= DISBOX_Y) {
            go_x = 0;
            go_y++;
        }
        disbox_boxs[i] = gtk_button_new();
        /* 方块放到表格上 */
        gtk_table_attach_defaults(
            GTK_TABLE(chessboard),
            disbox_boxs[i],
            go_x, go_x + 1, go_y, go_y + 1
        );
        g_signal_connect(
            disbox_boxs[i],
            "enter-notify-event",
            G_CALLBACK(mouse_moved),
            disbox_status + i
        );
    }
    /* 初始化所有方块 */
    init_chessboard(chessboard);
    return chessboard; /* 返回值用于加到窗口上 */
}
