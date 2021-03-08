# src目录下的源文件
OBJS := $(wildcard src/*.c)
# 转扩展名
OBJS := $(patsubst %.c,%.o,$(OBJS))

INCLUDE = include

CFLAGS-CONFIG = `pkg-config --cflags gtk+-2.0`
LIBS-CONFIG = `pkg-config --libs gtk+-2.0`
HEADER_RELY = include/dbx/*.h

default : disbox.exe

disbox.exe : $(OBJS)
	gcc -o $@ $(OBJS) $(LIBS-CONFIG)

%.o : %.c $(HEADER_RELY)
	gcc -c -I $(INCLUDE) $*.c -o $*.o $(CFLAGS-CONFIG)

# 仅用于调试
%.i : %.c $(HEADER_RELY)
	gcc -E -I $(INCLUDE) $*.c -o $*.i $(CFLAGS-CONFIG)

# 仅用于调试
%.s : %.c $(HEADER_RELY)
	gcc -S -I $(INCLUDE) $*.c -o $*.s $(CFLAGS-CONFIG)

run : disbox.exe
	./disbox

clean :
	$(RM) src/*.o
	$(RM) disbox.exe
