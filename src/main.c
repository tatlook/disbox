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
#include <stdlib.h>
#include <unistd.h>

#ifdef NDEBUG
#include <windows.h>
#endif

GtkWidget *disui_window;
GtkWidget *disui_main_panel;
GtkWidget *disui_tm_lable;
GtkWidget *disui_menubar;
int disbox_tm_count = 0;


static void menubar_size_allocate(GtkWidget *box,
                GdkRectangle *allocation,
                gpointer      user_data) {
    /* 菜单应占用更多空间 */
    gtk_widget_set_size_request(disui_menubar, allocation->width - 35, -1);
}

int main(int argc, char *argv[])
{
    /* 初始化随机数发生器 */
    {
        time_t t;
        srand((unsigned) time(&t));
    }
    /* release版本时隐藏控制台 */
#ifdef NDEBUG
    {
        HWND hwnd;
        hwnd = FindWindow("ConsoleWindowClass", NULL);	//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
        if (hwnd) {
            ShowWindow(hwnd, SW_HIDE);				//设置指定窗口的显示状态
        }
    }
#endif

    gtk_init(&argc, &argv);

    GError *gerrno;

    disui_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(disui_window), "消失方块");
    gtk_window_set_default_size(GTK_WINDOW(disui_window), 600, 600);
    gtk_window_set_default_icon_from_file(DISUI_ICON, &gerrno);
    g_signal_connect(disui_window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    disui_tm_lable = gtk_label_new("--");
    GtkWidget *main_panel = disui_main_panel = gtk_vbox_new(FALSE, 2);
    GtkWidget *chessboard = create_chessboard();
    GtkWidget *menubar_box = gtk_hbox_new(FALSE, 1);
    GtkWidget *menubar = disui_menubar = create_menubar();
    g_signal_connect(menubar_box, "size-allocate",
       G_CALLBACK(menubar_size_allocate), NULL);

    gtk_box_pack_start(GTK_BOX(menubar_box), menubar, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(menubar_box), disui_tm_lable, FALSE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(main_panel), menubar_box, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(main_panel), chessboard);
    gtk_container_add(GTK_CONTAINER(disui_window), main_panel); // 容器加入窗口

    gtk_widget_show_all(disui_window);	/* 显示窗口和所有控件 */
    gtk_main();
    return 0;
}

