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
