CC = gcc
CFLAGS += -Wall
LDFLAGS = -ljack

BIN_NAME = jack-midi-timestamp

SOURCES += main.c

all:
	$(CC) $(CFLAGS) -o $(BIN_NAME) $(SOURCES) $(LDFLAGS)

clean:
	rm -rf $(BIN_NAME)
