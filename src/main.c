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
#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *disui_window;
GtkWidget *disui_main_panel;

int main(int argc, char *argv[])
{
    /* 初始化随机数发生器 */
    {
        time_t t;
        srand((unsigned) time(&t));
    }

    gtk_init(&argc, &argv);

    disui_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(disui_window), "消失方块"); // 设置窗口的标题
    gtk_window_set_default_size(GTK_WINDOW(disui_window), 600, 600);
    GError *gerrno;
    gtk_window_set_default_icon_from_file(DISUI_ICON, &gerrno);
    g_signal_connect(G_OBJECT(disui_window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *main_panel = disui_main_panel = gtk_vbox_new(FALSE, 2);
    GtkWidget *chessboard = create_chessboard();
    GtkWidget *menubar = create_menubar();

    gtk_box_pack_start(GTK_BOX(main_panel), menubar, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(main_panel), chessboard);
    gtk_container_add(GTK_CONTAINER(disui_window), main_panel); // 容器加入窗口

    gtk_widget_show_all(disui_window);	/* 显示窗口和所有控件 */


    gtk_main();
    return 0;
}
