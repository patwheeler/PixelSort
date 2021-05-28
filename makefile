CC = g++
CFLAGS = -O2
LIBS = -lm -lpthread -lX11
LDFLAGS = -L/usr/X11R6/lib

default:
	$(CC) -o pixelsort *.cpp $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -f pixelsort
