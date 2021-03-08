#include <dbx/bootcontainer.h>
#include <dbx/gomoku.h>

static void show_rule();
static void show_license();
static void set_colorful(GtkWidget *widget, GdkEvent *event, int *n);
static void set_big(GtkWidget *widget, GdkEvent *event, int *n);

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
#if 0
    static const char *colorful_ss[4] = {
        "艰巨", "困难", "中等", "简单"
    };
    GtkWidget *colorful_mis[4];
    colorful_mis[0] = gtk_radio_menu_item_new_with_label(NULL, colorful_ss[0]);
    for (int i = 1; i < 4; i++) {
        colorful_mis[i] = gtk_radio_menu_item_new_with_label(
            gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(&colorful_mis[0])),
            colorful_ss[i]);
    }
    static const char *big_ss[4] = {
        "巨大", "较大", "中等", "小"
    };
    GtkWidget *big_mis[4];
    big_mis[0] = gtk_radio_menu_item_new_with_label(NULL, big_ss[0]);
    for (int i = 1; i < 4; i++) {
        big_mis[i] = gtk_radio_menu_item_new_with_label(
            gtk_radio_menu_item_group(GTK_RADIO_MENU_ITEM(&big_mis[0])),
            big_ss[i]);
    }
#else
    
#endif
    GtkWidget *rule_mi = gtk_menu_item_new_with_label("查看规则");
    GtkWidget *license_mi = gtk_menu_item_new_with_label("版权信息");


    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_ml), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(game_ml), game_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_ml), help_menu);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), restart_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), gtk_separator_menu_item_new());
    for (int i = 0; i < 4; i++)  {
        gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), colorful_mis[i]);
    }
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), gtk_separator_menu_item_new());
    for (int i = 0; i < 4; i++)  {
        gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), big_mis[i]);
    }

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

    g_signal_connect(G_OBJECT(license_mi), "activate",
        G_CALLBACK(show_license), NULL);

//    for (int i = 0; i < 4; i++)  {
 //       static int n[4] = {1, 2, 3, 4};
 //       g_signal_connect(G_OBJECT(colorful_mis[i]), "activate",
  //          G_CALLBACK(set_colorful), n + i);
   //     g_signal_connect(G_OBJECT(big_mis[i]), "activate",
   //         G_CALLBACK(set_big), n + i);
   // }

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

static void show_license() {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(disui_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Tatlook disbox [版本 1.0.0]\n"
        "版权所有 (c) 2021 Tatlook. 保留所有权利。"
    );
    gtk_widget_show_all(dialog);	/* 显示对话框和所有控件 */
}

static void set_colorful(GtkWidget *widget, GdkEvent *event, int *n) {
    color_number = (*n) * 2;
    init_chessboard();
}

static void set_big(GtkWidget *widget, GdkEvent *event, int *n) {
    disbox_x = disbox_x = *n;
    printf("HHHHHA");
    create_chessboard();
}
