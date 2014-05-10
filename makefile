# source and header directories
HDRDIR = -I hdr/
OBJDIR = obj/
SRCDIR = src/
APPDIR = app/

# c compiler and flags
CCompiler = gcc
CFlags = -std=c99 -Wall

# compile any changed source code file
_OBJ = item.o bonus.o const.o mob.o util.o load.o
OBJ = $(patsubst %,$(OBJDIR)%,$(_OBJ))

# compile all applications or projects
all: test4

test: $(APPDIR)test.c $(OBJ)
	$(CCompiler) -o $@ $(CFlags) $^ $(HDRDIR)

test2: $(APPDIR)test2.c $(OBJ)
	$(CCompiler) -o $@ $(CFlags) $^ $(HDRDIR)

test3: $(APPDIR)test3.c $(OBJ)
	$(CCompiler) -o $@ $(CFlags) $^ $(HDRDIR)

test4: $(APPDIR)test4.c $(OBJ)
	$(CCompiler) -o $@ $(CFlags) $^ $(HDRDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CCompiler) -c -o $@ $(CFlags) $^ $(HDRDIR)

# window clean
.PHONY: clean
clean:
	del *.exe
	rmdir obj /s /q
	mkdir obj