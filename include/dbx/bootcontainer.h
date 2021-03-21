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

#if !defined(_SMOKU_BCOC_H)
#define _SMOKU_BCOC_H

#include <gtk/gtkwindow.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkvbox.h>
#include <gtk/gtkhbox.h>
#include <gtk/gtkmain.h>
#include <glib-object.h>

GtkWidget *create_chessboard();
GtkWidget *create_menubar();
void init_chessboard();

extern GtkWidget *disui_window;
extern GtkWidget *disui_main_panel;
extern GtkWidget *disui_tm_lable;

#define CHESSBOARD_LINE_SPACING 16
#define CHESSBOARD_LINE_WIDTH 2.0

#define DISUI_ICON "./resource/disbox.ico"

#endif // _SMOKU_BCOC_H
