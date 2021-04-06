# Disbox - The Disable Box Game.
# Copyright (C) 2021 Tatlook
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# src目录下的源文件
OBJS := $(wildcard src/*.c)
# 转扩展名
OBJS := $(patsubst %.c,%.o,$(OBJS))

INCLUDE = include

CFLAGS-CONFIG = `pkg-config --cflags gtk+-2.0` $(CFLAG)
LIBS-CONFIG = `pkg-config --libs gtk+-2.0`
HEADER_RELY = include/dbx/*.h

default : disbox.exe

disbox.exe : $(OBJS)
	gcc $^ -o $@ $(LIBS-CONFIG)

%.o : %.c $(HEADER_RELY)
	gcc -c -I $(INCLUDE) $*.c -o $*.o $(CFLAGS-CONFIG)

# 仅用于调试
%.i : %.c $(HEADER_RELY)
	gcc -E -I $(INCLUDE) $*.c -o $*.i $(CFLAGS-CONFIG)

# 仅用于调试
%.s : %.c $(HEADER_RELY)
	gcc -S -I $(INCLUDE) $*.c -o $*.s $(CFLAGS-CONFIG)

.PHONY : run
run : disbox.exe
	./disbox

.PHONY : release
release : LIBPATH = $(shell expr substr $(shell pkg-config --libs-only-L gtk+-2.0) 3 250)
release : clean
	"$(MAKE)" disbox.exe CFLAG:="-DNDEBUG=1"
# 事先准备好目录
	@if [ ! -d release ]; then \
		echo mkdir release; \
		mkdir release; \
	fi
	@if [ ! -d release/lib ]; then \
		echo mkdir release/lib; \
		mkdir release/lib; \
	fi
	@if [ ! -d release/share ]; then \
		echo mkdir release/share; \
		mkdir release/share; \
	fi
# 所有依赖的Gtk零件拷贝过来
	cp $(LIBPATH)/../bin/*.dll release
	cp -r $(LIBPATH)/gtk-* release/lib/
	cp -r $(LIBPATH)/../etc release
	cp -r $(LIBPATH)/../share/themes release/share
	cp -r $(LIBPATH)/../share/locale release/share
# 本程序的文件拷贝过去
	cp disbox.exe release
	cp -r resource release
	cp LICENSE release

.PHONY : clean
clean :
	$(RM) src/*.o
	$(RM) disbox.exe
