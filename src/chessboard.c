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

#include <dbx/bootcontainer.h>
#include <dbx/gomoku.h>
#include <dbx/debug.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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

static gboolean win_fail_dialog_close() {
    init_chessboard();
    return FALSE;
}

static void do_win() {
    static GtkWidget *win_image = NULL;
    if (win_image == NULL)
        win_image = gtk_image_new_from_file("./resource/win.png");
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(disui_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "恭喜，您已胜利：\n"
        "\t翻动次数：%d", disbox_move_count
    );
    gtk_message_dialog_set_image(GTK_MESSAGE_DIALOG(dialog), win_image);
    gtk_widget_show_all(dialog);	/* 显示对话框和所有控件 */

    g_signal_connect(G_OBJECT(dialog), "delete_event",
        G_CALLBACK(win_fail_dialog_close), NULL);
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

static void fail_game(const char *why) {
    static GtkWidget *fail_image = NULL;
    if (fail_image == NULL)
        fail_image = gtk_image_new_from_file("./resource/fail.png");
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(disui_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_CLOSE,
        "非常抱歉，您输了。%s\n"
        "\t还剩%d个方块\n"
        "\t移动了%d次",
        why, disbox_count, disbox_move_count);
    gtk_message_dialog_set_image(GTK_MESSAGE_DIALOG(dialog), fail_image);
    gtk_widget_show_all(dialog);
    g_signal_connect(G_OBJECT(dialog), "delete_event",
        G_CALLBACK(win_fail_dialog_close), NULL);
}

static gboolean after_a_second(gpointer data) {
    disbox_tm_count++;
    dbgprintf("-C:%d:C-", disbox_tm_count);
    char s[32];
    gtk_label_set_label(GTK_LABEL(disui_tm_lable), itoa(disbox_tm_count, s, 10));
    if (disbox_tm_count == DISBOX_FAIL_TIME_COUNT) {
        fail_game("时间到");
        return FALSE;
    }
    return TRUE;
}

static void set_timer() {
    disbox_tm_count = 0;
    static bool
        timeout_set = false; /* 防止同时有多个定时器 */
    if (timeout_set == false) {
        timeout_set = true;
        gtk_label_set_label(GTK_LABEL(disui_tm_lable), "--");
        g_timeout_add(1000, after_a_second, NULL);
    }
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
       
    set_timer();
}


static GtkWidget *chessboard = NULL;
static bool chess_first_init = true;

GtkWidget *create_chessboard() {
    static char last_disbox_x;
    static char last_disbox_y;
    /* 第一次制作时需要初始化 */
    if (chess_first_init) {
        chessboard = gtk_table_new(disbox_x, disbox_y, TRUE);	// 表格布局
        for (int i = 0; i < DISBOX_M_S; i++) {
            disbox_boxs[i] = gtk_button_new();
            g_signal_connect(
                disbox_boxs[i],
                "enter-notify-event",
                G_CALLBACK(mouse_moved),
                disbox_colorno + i
            );
        }
        
    } else {
        /* 移除方块 */
        for (int i = 0; i < last_disbox_x * last_disbox_y; i++) {
            assert(disbox_boxs[i] != NULL);
            /* 需要再添加一个引用，因为原先的引用会因为
                gtk_container_remove而消失，导致对象销毁。 */
            GtkWidget *c = g_object_ref(G_OBJECT(disbox_boxs[i]));
            assert(c != NULL);
            gtk_container_remove(GTK_CONTAINER(chessboard), c);
        }
        /* 重新制作时只需要重新设置 */
        gtk_table_resize(GTK_TABLE(chessboard), disbox_x, disbox_y);
    }


    /* 方块放到表格上 */
    for (int i = 0, go_x = 0, go_y = 0; i < DISBOX_S; i++, go_x++) {
        assert(go_x <= disbox_x);
        assert(go_y <= disbox_y);
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
    last_disbox_x = disbox_x;
    last_disbox_y = disbox_y;

    return chessboard; /* 返回值用于加到窗口上 */
}
