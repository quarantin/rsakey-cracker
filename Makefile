
TARGET=rsakey-cracker

SOURCE=$(TARGET).c

CFLAGS=-Wall -Wextra

LIBS=-lssl -lcrypto

all:
	$(CC) $(CFLAGS) $(SOURCE) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
