DEST := hasher

DESTDIR = build

CC := gcc

SRC_PATH = src

CFLAGS = -Wall -Wextra

CDFLAGS = -Wall -Wextra -g -D DEBUG

LIB := crypto ssl

LIBS := $(LIB:%=-l%)

SRC := $(wildcard $(SRC_PATH)/*.c)
OBJS := $(SRC:%.c=$(DESTDIR)/%.o)


install: $(DESTDIR) $(OBJS)
	@echo "Compiling source files..."
	$(CC) $(CFLAGS) $(OBJS) -o $(DESTDIR)/$(DEST) $(LIBS)
	@echo "Done!"

debug: $(DESTDIR) $(OBJS)
	@echo "Compiling source files..."
	$(CC) $(CDFLAGS) $(OBJS) -o $(DESTDIR)/$(DEST) $(LIBS)
	@echo "Done!"

$(DESTDIR):
	@echo "making dir"
	mkdir -p $(DESTDIR)
	mkdir -p $(DESTDIR)/src
clean:
	@echo "Cleaning..."
	rm -rf $(DESTDIR)
	@echo "clean complete!"

$(DESTDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: install debug clean help
