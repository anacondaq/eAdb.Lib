# c compiler and flags
CCompiler = gcc
CFlags = -std=c89 -ansi -pedantic -Wall

# eadb library variables
HDRDIR = -I hdr/
OBJDIR = obj/
SRCDIR = src/
_OBJ = load.o util.o skill.o produce.o pet.o mob.o merc.o const.o bonus.o item.o
OBJ = $(patsubst %,$(OBJDIR)%,$(_OBJ))

# eadb compiler variables
EADB_HDRDIR = -I app/eAdb.Compiler/hdr/
EADB_OBJDIR = app/eAdb.Compiler/obj/
EADB_SRCDIR = app/eAdb.Compiler/src/
_EADB_COMPILER_OBJ = table.o status.o var.o block.o script.o
EADB_COMPILER_OBJ = $(patsubst %,$(EADB_OBJDIR)%,$(_EADB_COMPILER_OBJ))

# compile all applications or projects
all: tester
	tester

tester: proj/tester.c $(OBJ)
	$(CCompiler) -o $@ $(CFlags) $^ $(HDRDIR)

reader: app/eAdb.Compiler/reader.c $(OBJ) $(EADB_COMPILER_OBJ)
	$(CCompiler) -o $@ $(CFlags) $^ $(HDRDIR) $(EADB_HDRDIR)

$(EADB_OBJDIR)%.o: $(EADB_SRCDIR)%.c
	$(CCompiler) -c -o $@ $(CFlags) $^ $(HDRDIR) $(EADB_HDRDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CCompiler) -c -o $@ $(CFlags) $^ $(HDRDIR)

# window clean
.PHONY: clean
clean:
	del *.exe
	rmdir obj /s /q
	mkdir obj
	rmdir "app/eAdb.Compiler/obj/" /s /q
	mkdir "app/eAdb.Compiler/obj/"