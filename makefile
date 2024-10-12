CC = gcc
CFLAGS = -Wall -ansi -pedantic -fno-stack-protector
OBJS = main.o game.o display.o terminal.o random.o newSleep.o
TARGET = treasure

# Conditional compilation for DARK mode
ifdef DARK
CFLAGS += -DDARK
endif

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.c game.h display.h terminal.h random.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h random.h display.h game_utils.h
	$(CC) $(CFLAGS) -c game.c

display.o: display.c display.h game.h game_utils.h
	$(CC) $(CFLAGS) -c display.c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

newSleep.o: newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

clean:
	rm -f $(TARGET) $(OBJS)