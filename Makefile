.ONESHELL:
SHELL = /bin/bash

#static library directory
STLIBDIR := statlib
#dynamic library directory
SOLIBDIR := solib
#static library objects directory
STOBJDIR := stobj
#dynamic library objects directory
SOOBJDIR := soobj
#default image directory
IMAGEDIR := imgs
#test images directory
TESTDIR := test
#executable directory
EXEDIR := bin
#main object directory
MAINOBJDIR := mainobj

#executable file generated from static libraries
STEXE := $(EXEDIR)/stapp
#executable file generated using dynamic libraries
SOEXE := $(EXEDIR)/soapp
#static libraries
STLIBS := $(addprefix $(STLIBDIR)/lib, matrix.a matrixmath.a ppm.a transformations.a)
#dynamic libraries
SOLIBS := $(addprefix -$(SOLIBDIR)/lib, matrix.so matrixmath.so ppm.so transformations.so)
#static library object files for archiving
STOBJS := $(addprefix $(STOBJDIR)/, ppm.o transformations.o matrixmath.o matrix.o);
#names of libraries to be used when compiling in correct linking order
LIBS := $(addprefix -l, ppm transformations matrixmath matrix)
#header files for dependency checking
HEADERS := $(patsubst headers/%,%,$(wildcard headers/*.h))
#HEADERS := transformations.h ppm.h matrix.h matrixmath.h

vpath %.c src
vpath %.h headers

all:	build

build:	$(STEXE)

run:	$(STEXE)
	@if [ -f $(IMAGEDIR)/tmp/userinput.ppm ]; then
	@useroutpath=`cat imgs/tmp/useroutpath.txt`
	@./$(STEXE) 0 2 $(IMAGEDIR)/tmp/userinput.ppm $(IMAGEDIR)/tmp/useroutput.ppm
	@if [ $${useroutpath##*.} != ppm ]; then
	@convert $(IMAGEDIR)/useroutput.ppm $$useroutpath
	@else
	@cp $(IMAGEDIR)/tmp/useroutput.ppm $$useroutpath
	@fi
	@else
	@./$(STEXE) 0 2 $(IMAGEDIR)/input.ppm $(IMAGEDIR)/output.ppm
	@fi

prepare:
	@read -p "Enter input file path " userinputpath
	@read -p "Enter output file path " useroutpath
	@if [ -f $$userinputpath -a -d "$${useroutpath%/*}" ]; then
	@mkdir $(IMAGEDIR)/tmp
	@echo $$useroutpath > $(IMAGEDIR)/tmp/useroutpath.txt
	@if [ "$${userinputpath##*.}" != "ppm" ]; then
	@convert $$userinputpath $(IMAGEDIR)/userinput.ppm
	@else
	@cp $$userinputpath $(IMAGEDIR)/tmp/userinput.ppm
	@fi
	@fi

liba: $(STLIBS)

$(STEXE) : $(MAINOBJDIR)/main.o $(STLIBS) | $(EXEDIR)
	gcc -o $@ -I headers $< -L $(STLIBDIR) $(LIBS)

$(STLIBDIR)/lib%.a: $(STOBJDIR)/%.o | $(STLIBDIR)
	ar rcs $@ $^

$(STOBJDIR)/%.o: %.c $(HEADERS) | $(STOBJDIR)
	gcc -o $@ -c -I headers $<

$(MAINOBJDIR)/%.o: %.c $(HEADERS) | $(MAINOBJDIR)
	gcc -o $@ -c -I headers $<

$(MAINOBJDIR):
	mkdir -p $@
$(EXEDIR):
	mkdir -p $@
$(STOBJDIR):
	mkdir -p $@
$(STLIBDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(STLIBDIR) $(SOLIB) $(MAINOBJDIR) $(STOBJDIR) $(SOLIBDIR) $(EXEDIR)
	rm -rf $(IMAGEDIR)/output.ppm $(IMAGEDIR)/tmp

#Don't delete intermediate object files used for creating static libraries
.SECONDARY: $(STOBJS)

