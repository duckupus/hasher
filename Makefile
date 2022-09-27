DEST := hasher

DESTDIR = build

CC := gcc

SRC_PATH = src

CFLAGS = -O3 -Wall -Wextra

CDFLAGS = -O3 -Wall -Wextra -g -D DEBUG

SRC := $(wildcard $(SRC_PATH)/*.c)
OBJS := $(SRC:%.c=$(DESTDIR)/%.o)


install: $(DESTDIR) $(OBJS)
	@echo "Compiling source files..."
	$(CC) $(CFLAGS) $(OBJS) -o $(DESTDIR)/$(DEST)
	@echo "Done!"

debug: $(DESTDIR) $(OBJS)
	@echo "Compiling source files..."
	$(CC) $(CDFLAGS) $(OBJS) -o $(DESTDIR)/$(DEST)
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
