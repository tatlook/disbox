#include <smoku/bootcontainer.h>

GtkWidget *create_menubar() {
    GtkWidget *menubar = gtk_menu_bar_new();

    GtkWidget *file_menu = gtk_menu_new();
    GtkWidget *game_menu = gtk_menu_new();

    GtkWidget *file_ml = gtk_menu_item_new_with_label("文件");
    GtkWidget *game_ml = gtk_menu_item_new_with_label("游戏");

    GtkWidget *save_mi = gtk_menu_item_new_with_label("保存棋谱");
    GtkWidget *quit_mi = gtk_menu_item_new_with_label("退出");

    GtkWidget *regret_mi = gtk_menu_item_new_with_label("悔棋");
    GtkWidget *restart_mi = gtk_menu_item_new_with_label("重新开始");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_ml), file_menu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(game_ml), game_menu);

    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), quit_mi);

    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), regret_mi);
    gtk_menu_shell_append(GTK_MENU_SHELL(game_menu), restart_mi);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_ml);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), game_ml);

    g_signal_connect(G_OBJECT(quit_mi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

    return menubar;
}
