# copen version
VERSION = 1.0

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# OpenBSD (uncomment)
#MANPREFIX = ${PREFIX}/man

# flags
CFLAGS   = -std=c99 -pedantic -Wall -Wextra -Os $(INCS) -DVERSION=\"$(VERSION)\"
LDFLAGS  =

# compiler and linker
CC = cc

