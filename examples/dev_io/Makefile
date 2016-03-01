PROG = dev_io
SOURCES = $(PROG).c ../../fossa.c
CFLAGS = -W -Wall -I../.. $(CFLAGS_EXTRA) -DNS_DEV_IO

all: $(PROG)

$(PROG): $(SOURCES)
	$(CC) $(SOURCES) -o $@ $(CFLAGS)

$(PROG).exe: $(SOURCES)
	cl $(SOURCES) /I../.. /MD /Fe$@

clean:
	rm -rf *.gc* *.dSYM *.exe *.obj *.o a.out $(PROG)
