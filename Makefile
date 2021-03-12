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

CFLAGS-CONFIG = `pkg-config --cflags gtk+-2.0`
LIBS-CONFIG = `pkg-config --libs gtk+-2.0`
HEADER_RELY = include/dbx/*.h

ifeq ($(LANG),)
RM ?= rm -f
else
RM ?= -del
endif

default : disbox.exe

# TODO: rely += resource/disbox.ico.o
disbox.exe : $(OBJS)
	gcc $^ -o $@ $(LIBS-CONFIG)

resource/disbox.ico.o : resource/disbox.ico.rc resource/disbox.ico
	windres -i $< -o $@

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

# TODO
.PHONY : install
install :
	$(MAKE) $(OBJS)
	gcc $^ -o disbox.exe $(LIBS-CONFIG)
ifeq ($(LANG),)
	cp disbox.exe /usr/bin
	mkdir /usr/share/doc/disbox
	cp LICENSE /usr/share/doc/disbox
else
	mkdir %ProgramFiles\disbox
	copy disbox.exe %ProgramFiles%\disbox\ 
	copy LICENSE %ProgramFiles%\disbox\ 
endif

.PHONY : clean
clean :
	$(RM) src/*.o
	$(RM) disbox.exe
