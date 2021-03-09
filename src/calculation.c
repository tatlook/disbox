#include <smoku/bootcontainer.h>
#include <smoku/gomoku.h>
#include <smoku/debug.h>

gomoku_status_t gomoku_map[GOMOKU_X][GOMOKU_Y];
gomoku_status_t *gomoku_mapp = (gomoku_status_t *) &gomoku_map;
GtkWidget *gomoku_pieces[GOMOKU_S];
enum gomoku_own_t gomoku_own = GOOWN_USER;

void calculation() {
    /*gomoku_own = GOOWN_USER;*/
}
