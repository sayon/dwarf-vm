# ---------------------------------------------------------------------------
#
#                 Dwarf, an educational stack virtual machine
#
#
#  See README.md for additional information.
# 
#                                (c) Igor Zhirkov, igorjirkov [at] gmail.com
# ---------------------------------------------------------------------------

CC			= gcc
BUILDDIR	= build
OBJDIR		= obj
SRCDIR		= src
TESTDIR     = tests


INCLUDEDIR	= include
CFLAGS		= -c -std=c99 -I$(INCLUDEDIR) -ggdb -Wno-attributes
LDFLAGS		=

#SOURCES     = bc_reloc.c bc_visitor.c code_printer.c const_pool.c debug.c function.c interpreter.c launcher.c linker.c loader.c util.c vm.c
SOURCES     = $(wildcard $(SRCDIR)/*.c)
OBJECTS     = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TESTS       = $(wildcard $(TESTDIR)/*.dw)
TESTTARGETS = $(TESTS:%.dw=%.dwc)

TARGET      = vm


ASM         = nasm
ASMFLAGS    = -fbin -I$(TESTDIR)/

all: $(BUILDDIR) $(OBJDIR) $(BUILDDIR)/$(TARGET) $(OBJECTS) $(TESTS) $(TESTTARGETS)
 
$(BUILDDIR)/$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $@
$(OBJDIR):
	mkdir -p $@ 

$(TESTTARGETS): $(TESTS) 
	$(ASM) $(ASMFLAGS) -o $@ $(@:%.dwc=%.dw)

docs:
	doxygen Doxyfile

clean:
	rm -rf $(BUILDDIR) $(OBJDIR)
	rm -f $(TESTTARGETS)

.PHONEY: dirs clean docs
