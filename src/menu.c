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

#include <gtk/gtkseparatormenuitem.h>
#include <gtk/gtkradiomenuitem.h>
#include <gtk/gtkcheckmenuitem.h>
#include <gtk/gtkmenubar.h>
#include <dbx/bootcontainer.h>
#include <dbx/gomoku.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static void show_rule();
static void show_license();
static void function_change(GtkCheckMenuItem *checkmenuitem, bool *chageable) {
    *chageable = !(*chageable);
    init_chessboard();
}
#define setdiff(N, N2) static void set_colorful##N2() { \
    color_number = N * 2; \
    init_chessboard(); \
}
setdiff(4, _1)
setdiff(3, _2)
setdiff(2, _3)
setdiff(1, _4)
#undef setdiff
#define setdiff(N, N2) static void set_big##N2() { \
    disbox_x = disbox_y = N * 5; \
    create_chessboard(); \
}
setdiff(4, _1)
setdiff(3, _2)
setdiff(2, _3)
setdiff(1, _4)
#undef setdiff

GtkWidget *create_menubar() {
    GtkWidget *menubar = gtk_menu_bar_new();

    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *game_menu = gtk_menu_new();
    GtkWidget *help_menu = gtk_menu_new();

    GtkWidget *file_ml = gtk_menu_item_new_with_mnemonic("文件(_F)");
    GtkWidget *game_ml = gtk_menu_item_new_with_mnemonic("游戏(_G)");
    GtkWidget *help_ml = gtk_menu_item_new_with_mnemonic("帮助(_H)");

    GtkWidget *quit_mi = gtk_menu_item_new_with_mnemonic("退出\t\t\t(_E)");

    GtkWidget *restart_mi = gtk_menu_item_new_with_mnemonic("重新开始\t\t(_R)");

    GtkWidget *rule_mi = gtk_menu_item_new_with_mnemonic("查看规则\t\t(_R)");
    GtkWidget *about_mi = gtk_menu_item_new_with_mnemonic("关于\t\t\t(_A)");

    GtkWidget *colorful_3_mi = gtk_radio_menu_item_new_with_label(NULL, "中等");
    GtkWidget *colorful_1_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(colorful_3_mi)),
        "五颜六色");
    GtkWidget *colorful_2_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(colorful_3_mi)),
        "色彩丰富");
    GtkWidget *colorful_4_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(colorful_3_mi)),
        "色彩单凋");
    GtkWidget *big_1_mi = gtk_radio_menu_item_new_with_label(NULL, "巨大");
    GtkWidget *big_3_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(big_1_mi)), "中等");
    GtkWidget *big_2_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(big_1_mi)),
        "较大");
    GtkWidget *big_4_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(big_1_mi)),
        "小");

    GtkWidget *f_chout_mi = gtk_check_menu_item_new_with_label("离开区域即变色");
    GtkWidget *f_chin_mi = gtk_check_menu_item_new_with_label("进入区域即变色");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(f_chin_mi), TRUE);
    GtkWidget *f_attimeout_mi = gtk_check_menu_item_new_with_label("计算停留时间");
    GtkWidget *f_nooutside_mi = gtk_check_menu_item_new_with_label("不允许光标离开窗口");
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(f_nooutside_mi), TRUE);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_ml), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(game_ml), game_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_ml), help_menu);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), restart_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), colorful_1_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), colorful_2_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), colorful_3_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), colorful_4_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), big_1_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), big_2_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), big_3_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), big_4_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), f_chout_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), f_chin_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), f_attimeout_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), f_nooutside_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), rule_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_mi);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_ml);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), game_ml);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_ml);

    g_signal_connect(G_OBJECT(quit_mi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(rule_mi), "activate",
        G_CALLBACK(show_rule), NULL);

    g_signal_connect(G_OBJECT(restart_mi), "activate",
        G_CALLBACK(init_chessboard), NULL);

    g_signal_connect(G_OBJECT(about_mi), "activate",
        G_CALLBACK(show_license), NULL);

#define df(M, P) g_signal_connect(G_OBJECT(M), "activate",\
        G_CALLBACK(function_change), &P)
    df(f_chout_mi, disbox_out_change);
    df(f_chin_mi, disbox_in_change);
    df(f_attimeout_mi, disbox_fail_longtime_at_box);
    df(f_nooutside_mi, disbox_no_outside);
#undef df
    
#define gsdf(N) g_signal_connect(G_OBJECT(colorful##N##_mi), "toggled",\
        G_CALLBACK(set_colorful##N), NULL)
    gsdf(_1);
    gsdf(_2);
    gsdf(_3);
    gsdf(_4);
#undef gsdf

#define gssf(N) g_signal_connect(G_OBJECT(big##N##_mi), "toggled",\
        G_CALLBACK(set_big##N), NULL)
    gssf(_1);
    gssf(_2);
    gssf(_3);
    gssf(_4);
#undef gssf

    return menubar;
}


#include <gtk/gtkmessagedialog.h>

static void show_rule() {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(disui_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_CLOSE,
        "每次鼠标进入方格区域后，方格的颜色会改变一次。"
        "当所有方格的颜色都是白色时，游戏结束。"
    );
    gtk_widget_show_all(dialog);	/* 显示对话框和所有控件 */
}

#include <gtk/gtkaboutdialog.h>

static void show_license() {
    GtkWidget *dialog = gtk_about_dialog_new();
    
    static const gchar *authors[3] = {
        "Tatlook"
    };

    static gchar *dislice = NULL;
    /* 只需要加载一次 */
    if (dislice == NULL) {
        struct stat st;
        int ret = stat("LICENSE", &st);
        /* LICENSE文件不见了 */
        if (ret) {
            dislice = "本地协议加载错误，请查看在线版本：https://www.gnu.org/licenses/gpl-3.0.txt";
        /* 还在就读入 */
        } else {
            dislice = malloc(st.st_size);
            FILE *f = fopen("LICENSE", "r");
            fread(dislice, st.st_size, 1, f);
            fclose(f);
        }
    }

    assert(dislice != NULL);

    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), 
        "Tatlook disbox [版本 1.0.0]\n"
        "版权所有 (c) 2021 Tatlook. 保留所有权利。");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "消失方块游戏");
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Disbox");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0.0");
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog), dislice);

    gtk_widget_show_all(dialog);	/* 显示对话框和所有控件 */
}
