STLIBDIR := statlib
SOLIBDIR := solib
OBJDIR := obj
IMAGEDIR := imgs
TESTDIR := test
EXEDIR := bin

INPUTPATH := $(IMAGEDIR)/input.ppm
OUTPUTPATH := $(IMAGEDIR)/output.ppm

USEROUTPATH := $(IMAGEDIR)


EXE := $(EXEDIR)/app
STLIBS := $(addprefix $(STLIBDIR)/, libmatrix.a libmatrixmath.a libppm.a libtransformations.a)
SOLIBS := $(addprefix -l, libmatrix.so libmatrixmath.so libppm.so libtransformations.so)
OBJS := $(addprefix $(OBJDIR), $(patsubst src/%.c, %.o, $(wildcard src/*c)));

vpath %.c src
vpath %.h headers

all:	build

build:	$(EXE)

run:	$(EXE)
	./$(EXE) 0 2 $(INPUTPATH) $(OUTPUTPATH)
	@if [ $(USEROUTPATH) != $(IMAGEDIR) ]; then
	@if [ $(USEROUTPATH) != *".ppm" ]; then
	@convert $(IMAGEDIR)/useroutput.ppm $(USEROUTPATH)
	@else
	@cp $(IMAGEDIR)/useroutput.ppm $(USEROUTPATH)
	@fi
	$(eval INPUTPATH:=$(IMAGEDIR)/input.ppm)
	$(eval OUTPUTPATH:=$(IMAGEDIR)/output.ppm)
	@rm $(IMAGEDIR)/userinput.ppm
	@rm $(IMAGEDIR)/useroutput.ppm
	@fi

prepare:	$(EXE)
	@read -p "Enter input file path" userinputpath;
	@read -p "Enter ouput file path" useroutpath;
	$(eval USEROUTPATH:=$(useroutpath))
	@if [ $(userinputpath) != *".ppm" ]; then
	@convert $(userinputpath) $(IMAGEDIR)/userinput.ppm
	@else
	@cp $(userinputpath) $(IMAGEDIR)/userinput.ppm
	@fi
	$(eval INPUTPATH:=$(IMAGEDIR)/userinput.ppm)
	$(eval OUTPUTPATH:=$(IMAGEDIR)/useroutput.ppm)

$(EXE) : $(OBJDIR)/main.o $(STLIBS) | $(EXEDIR)
	gcc -o $@ -I headers $< -L $(STLIBDIR) -lmatrix -lmatrixmath -ltransformations -lppm


$(STLIBDIR)/libmatrix.a: matrix.o | $(STLIBDIR)
	ar rcs $@ $^
$(STLIBDIR)/libmatrixmath.a: matrix.o matrixmath.o | $(STLIBDIR)
	ar rcs $@ $^
$(STLIBDIR)/libppm.a: matrix.o matrixmath.o ppm.o | $(STLIBDIR)
	ar rcs $@ $^
$(STLIBDIR)/libtransformations.a: matrix.o matrixmath.o transformations.o ppm.o | $(STLIBDIR)
	ar rcs $@ $^

$(OBJDIR)/%.o:	%.c matrix.h matrixmath.h transformations.h ppm.h | $(OBJDIR)
	gcc -o $@ -c -I headers $<

$(EXEDIR):
	mkdir -p $(EXEDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(STLIBDIR):
	mkdir -p $(STLIBDIR)

.PHONY: clean
clean:
	rm -rf $(STLIBDIR) $(SOLIB) $(OBJDIR) $(EXEDIR)

