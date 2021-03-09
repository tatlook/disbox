#if !defined(_SMOKU_BCOC_H)
#define _SMOKU_BCOC_H

#include <gtk/gtk.h>

GtkWidget *create_chessboard();
GtkWidget *create_menubar();

extern GtkWidget *gomoku_piece_black_image; /* 黑子的图片 */
extern GtkWidget *gomoku_piece_write_image; /* 白子的图片 */

#define CHESSBOARD_LINE_SPACING 16
#define CHESSBOARD_LINE_WIDTH 2.0

#endif // _SMOKU_BCOC_H
