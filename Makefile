CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=gnu11
LDLIBS ?= -pthread

.PHONY: all clean

all: mesa crupier elimina

mesa: juego/partida.c control/control.h
	$(CC) $(CFLAGS) -o $@ juego/partida.c $(LDLIBS)

elimina: control/elimina.c control/control.h 
	$(CC) $(CFLAGS) -o $@ control/elimina.c $(LDLIBS)

crupier: control/crupier.c control/control.h
	$(CC) $(CFLAGS) -o $@ control/crupier.c $(LDLIBS)

clean:
	rm -f mesa crupier
