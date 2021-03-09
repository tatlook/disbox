#include <gtk/gtk.h>
#include <smoku/bootcontainer.h>

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    gomoku_piece_black_image = gtk_image_new_from_file("./resource/piece_black.png");
    gomoku_piece_write_image = gtk_image_new_from_file("./resource/piece_write.png");

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "五子棋"); // 设置窗口的标题
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);
    GError *gerrno;
    gtk_window_set_default_icon_from_file("./resource/smoku.ico", &gerrno);
    g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *main_panel = gtk_vbox_new(FALSE, 2);
    GtkWidget *chessboard = create_chessboard();
    GtkWidget *menubar = create_menubar();

    gtk_box_pack_start(GTK_BOX(main_panel), menubar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(main_panel), chessboard);
    gtk_container_add(GTK_CONTAINER(window), main_panel); // 容器加入窗口

    gtk_widget_show_all(window);	/* 显示窗口和所有控件 */


    gtk_main();
    return 0;
}
