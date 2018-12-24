COMP=gcc

OBJDIR=obj

HEADDIR=include

CFLAGS=-Wall -I$(HEADDIR)

OBJ=$(OBJDIR)/CC.o \
		$(OBJDIR)/caesar.o
vpath %.c src
vpath %.h $(HEADDIR)

all: CC

CC: $(OBJ)
	$(COMP) $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o: %.c %.h
	$(COMP) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/CC.o: CC.c caesar.h
	$(COMP) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm CC obj/*.o