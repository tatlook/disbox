#include <smoku/bootcontainer.h>

static void show_rule();

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

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_ml), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(game_ml), game_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_ml), help_menu);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), restart_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), rule_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), license_mi);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_ml);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), game_ml);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help_ml);

    g_signal_connect(G_OBJECT(quit_mi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(rule_mi), "activate",
        G_CALLBACK(show_rule), NULL);


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
