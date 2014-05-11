# c compiler and flags
CCompiler = gcc
CFlags = -std=c99

# eadb library variables
HDRDIR = -I hdr/
OBJDIR = obj/
SRCDIR = src/
_OBJ = item.o bonus.o const.o mob.o skill.o merc.o produce.o util.o pet.o load.o
OBJ = $(patsubst %,$(OBJDIR)%,$(_OBJ))

# eadb compiler variables
EADB_HDRDIR = -I app/eAdb.Compiler/hdr/
EADB_OBJDIR = app/eAdb.Compiler/obj/
EADB_SRCDIR = app/eAdb.Compiler/src/
_EADB_COMPILER_OBJ = block.o func.o
EADB_COMPILER_OBJ = $(patsubst %,$(EADB_OBJDIR)%,$(_EADB_COMPILER_OBJ))

# compile all applications or projects
all: reader

reader: $(EADB_SRCDIR)reader.c $(OBJ) $(EADB_COMPILER_OBJ)
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