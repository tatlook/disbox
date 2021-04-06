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

#if !defined(_SMOKU_DEBUG_H)
#define _SMOKU_DEBUG_H

#ifndef NDEBUG

#define dbgputs(S) g_print(S)
#define dbgprintf(F...) g_print(F)

#else

#define dbgputs(S)
#define dbgprintf(F...)

#endif

#endif // _SMOKU_DEBUG_H
