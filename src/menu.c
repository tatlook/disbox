#include <smoku/bootcontainer.h>
#include <smoku/gomoku.h>

static void show_rule();
#define setdiff(N) static void set_dif_to##N();
setdiff(_1)
setdiff(_2)
setdiff(_3)
setdiff(_4)
#undef setdiff
#define setdiff(N) static void set_sif_to##N();
setdiff(_1)
setdiff(_2)
setdiff(_3)
setdiff(_4)
#undef setdiff


GtkWidget *create_menubar() {
    GtkWidget *menubar = gtk_menu_bar_new();

    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *game_menu = gtk_menu_new();
    GtkWidget *help_menu = gtk_menu_new();

    GtkWidget *file_ml = gtk_menu_item_new_with_label("文件");
    GtkWidget *game_ml = gtk_menu_item_new_with_label("游戏");
    GtkWidget *help_ml = gtk_menu_item_new_with_label("帮助");

    GtkWidget *quit_mi = gtk_menu_item_new_with_label("退出");

    GtkWidget *restart_mi = gtk_menu_item_new_with_label("重新开始");

    GtkWidget *rule_mi = gtk_menu_item_new_with_label("查看规则");
    GtkWidget *license_mi = gtk_menu_item_new_with_label("版权信息");

    GtkWidget *dif_1_mi = gtk_radio_menu_item_new_with_label(NULL, "艰巨");
    GtkWidget *dif_2_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(dif_1_mi)),
        "困难");
    GtkWidget *dif_3_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(dif_1_mi)),
        "中等");
    GtkWidget *dif_4_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(dif_1_mi)),
        "简单");
    GtkWidget *sif_1_mi = gtk_radio_menu_item_new_with_label(NULL, "巨大");
    GtkWidget *sif_2_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(sif_1_mi)),
        "较大");
    GtkWidget *sif_3_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(sif_1_mi)),
        "中等");
    GtkWidget *sif_4_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(sif_1_mi)),
        "小");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_ml), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(game_ml), game_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_ml), help_menu);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), restart_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), dif_1_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), dif_2_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), dif_3_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), dif_4_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), sif_1_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), sif_2_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), sif_3_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), sif_4_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), rule_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), license_mi);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_ml);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), game_ml);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_ml);

    g_signal_connect(G_OBJECT(quit_mi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(rule_mi), "activate",
        G_CALLBACK(show_rule), NULL);

    g_signal_connect(G_OBJECT(restart_mi), "activate",
        G_CALLBACK(init_chessboard), NULL);
#define gsdf(N) g_signal_connect(G_OBJECT(dif##N##_mi), "activate",\
        G_CALLBACK(set_dif_to##N), NULL)
    gsdf(_1);
    gsdf(_2);
    gsdf(_3);
    gsdf(_4);
#undef gsdf

#define gssf(N) g_signal_connect(G_OBJECT(sif##N##_mi), "activate",\
        G_CALLBACK(set_sif_to##N), NULL)
    gssf(_1);
    gssf(_2);
    gssf(_3);
    gssf(_4);
#undef gssf

    return menubar;
}

static void show_rule() {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(disui_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "每次鼠标进入方格区域后，方格的颜色会改变一次。"
        "当所有方格的颜色都是白色时，游戏结束。"
    );

    gtk_widget_show_all(dialog);	/* 显示对话框和所有控件 */
}

#define setdiff(N, N2) static void set_dif_to##N2() { \
    color_number = N * 2; \
    init_chessboard(); \
}

setdiff(4, _1)
setdiff(3, _2)
setdiff(2, _3)
setdiff(1, _4)
#undef setdiff

#define setdiff(N, N2) static void set_sif_to##N2() { \
    disbox_x = disbox_x = N; \
    printf("HHHHHA");\
    create_chessboard(); \
}

setdiff(4, _1)
setdiff(3, _2)
setdiff(2, _3)
setdiff(1, _4)
#undef setdiff
