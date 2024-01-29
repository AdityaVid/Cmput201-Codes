CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Target for fast I/O
fastio: CFLAGS += -DFASTIO
fastio: fastunionfind

# Target for easy I/O
easyio: CFLAGS += -DEASYIO
easyio: easyunionfind

fastunionfind: ex13q1.c
	$(CC) $(CFLAGS) ex13q1.c -o fastio


easyunionfind: ex13q1.c
	$(CC) $(CFLAGS) ex13q1.c -o easyio

clean:
	rm -f unionfind
