# copen - run command associated with a extension
# See LICENSE file for copyright and license details.

include config.mk

SRC = copen.c

all: options copen

options:
	@echo copen build options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "CC       = $(CC)"

config.h:
	cp config.def.h $@

mhkd: config.h config.mk
	$(CC) $(CFLAGS) $(SRC) -o ./$@ $(LDFLAGS)

clean:
	rm -f ./copen $(OBJ) copen-$(VERSION).tar.gz

dist: clean
	mkdir -p copen-$(VERSION)
	cp LICENSE Makefile README.md config.def.h config.mk copen.1 $(SRC) copen-$(VERSION)
	tar -cf copen-$(VERSION).tar copen-$(VERSION)
	gzip copen-$(VERSION).tar
	rm -rf copen-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f ./copen $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/copen
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < copen.1 > $(DESTDIR)$(MANPREFIX)/man1/copen.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/copen.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/copen $(DESTDIR)$(MANPREFIX)/man1/copen.1

.PHONY: all options clean dist install uninstall

