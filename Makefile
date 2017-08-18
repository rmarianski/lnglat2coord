P=lnglat2coord
OBJECTS=$(P).o
CFLAGS = -g -Wall -std=gnu11 -pedantic -O3 `pkg-config --cflags futile`
LDLIBS = `pkg-config --libs futile` -lm

$(P): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(P)

install: $(P)
	cp -f $(P) $(HOME)/opt/bin/$(P)
