# project name (generate executable with this name)
TARGET   = GUI_SDL.exe

CC       = mpicxx
# compiling flags here
CFLAGS   = -I ./Libs/RHPC/include/ -I ./code/include/ -I ./Libs/RHPC/include/relogo/ -I /usr/local/include

LINKER   = mpicxx -o
# linking flags here
LFLAGS   = -L ./Libs/Boost/Boost_1.54/lib/ -L ./Libs/RHPC/lib/ -L /usr/local/lib
LIB = -lrelogo-2.0 -lrepast_hpc-2.0 -lboost_mpi-mt-s -lboost_serialization-mt-s -lboost_system-mt-s -lboost_filesystem-mt-s -lboost_thread-mt-s -lSDL2 -lGL -lGLU -lm

# change these to set the proper directories where each files shoould be
SRCDIR  = code/src
HEADIR  = code/include
OBJDIR   = code/obj
BINDIR   = bin
RESDIR = results
LOGSDIR = logs

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(HEADIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
LOGS	 := $(wildcard $(LOGSDIR)/*.csv)
RESULT	 := $(wildcard $(RESDIR)/*.csv)
rm       = rm -f


all: $(SOURCES) $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) $(LIB)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clear_results
clear_results:
	@$(rm) $(LOGS) $(RESULT)
	@echo "Results and logs Cleaned up !"

.PHONEY: clean
clean: clear_results
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
