#include <gtk/gtk.h>
#include <smoku/bootcontainer.h>

GtkWidget *disui_window;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    disui_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(disui_window), "消失方块"); // 设置窗口的标题
    gtk_window_set_default_size(GTK_WINDOW(disui_window), 600, 600);
    GError *gerrno;
    gtk_window_set_default_icon_from_file("./resource/disbox.ico", &gerrno);
    g_signal_connect(G_OBJECT(disui_window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *main_panel = gtk_vbox_new(FALSE, 2);
    GtkWidget *chessboard = create_chessboard();
    GtkWidget *menubar = create_menubar();

    gtk_box_pack_start(GTK_BOX(main_panel), menubar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(main_panel), chessboard);
    gtk_container_add(GTK_CONTAINER(disui_window), main_panel); // 容器加入窗口

    gtk_widget_show_all(disui_window);	/* 显示窗口和所有控件 */


    gtk_main();
    return 0;
}
