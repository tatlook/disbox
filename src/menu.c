#include <dbx/bootcontainer.h>
#include <dbx/gomoku.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>

static void show_rule();
static void show_license();
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
    disbox_x = N * 5; \
    disbox_y = N * 5; \
    printf("HHHHHA%d$$", N * 5);\
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

    GtkWidget *quit_mi = gtk_menu_item_new_with_mnemonic("退出\t\t(_E)");

    GtkWidget *restart_mi = gtk_menu_item_new_with_mnemonic("重新开始\t(_R)");

    GtkWidget *rule_mi = gtk_menu_item_new_with_mnemonic("查看规则\t(_R)");
    GtkWidget *about_mi = gtk_menu_item_new_with_mnemonic("关于\t\t(_A)");

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
    GtkWidget *big_3_mi = gtk_radio_menu_item_new_with_label(NULL, "中等");
    GtkWidget *big_1_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(big_3_mi)), "巨大");
    GtkWidget *big_2_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(big_3_mi)),
        "较大");
    GtkWidget *big_4_mi = gtk_radio_menu_item_new_with_label(
        gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(big_3_mi)),
        "小");

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

static void show_rule() {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(disui_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_CLOSE,
        "每次鼠标进入方格区域后，方格的颜色会改变一次。"
        "当所有方格的颜色都是白色时，游戏结束。"
    );
//    GtkWidget *d = gtk_dialog_new_with_buttons(
  ////      "游戏规则",
    //    GTK_WINDOW(disui_window),
    ///    NULL,
     //   "关闭"
    //);
    gtk_widget_show_all(dialog);	/* 显示对话框和所有控件 */
}


static void show_license() {
    GtkWidget *dialog = gtk_about_dialog_new();
    
    static const gchar *authors[] = {
        "Tatlook"
    };
    gchar *dislice;
    {
        struct stat st;
        stat("LICENSE", &st);
        dislice = malloc(st.st_size);
        FILE *f = fopen("LICENSE", "r");
        fread(dislice, st.st_size, 1, f);
        fclose(f);
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
