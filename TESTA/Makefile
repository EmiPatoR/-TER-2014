# project name (generate executable with this name)
TARGET   = GUI_SDL.exe

CC       = /home/emip/Desktop/Cours/TER/Libs/decompresse/RHPC_2.0/ext/MPICH/bin/mpicxx
# compiling flags here
CFLAGS   = -I /home/emip/Desktop/Cours/TER/Libs/decompresse/RHPC_2.0/include/ -I ./include/ -I /home/emip/Desktop/Cours/TER/Libs/decompresse/RHPC_2.0/include/relogo/ -I /usr/local/include

LINKER   = /home/emip/Desktop/Cours/TER/Libs/decompresse/RHPC_2.0/ext/MPICH/bin/mpicxx -o
# linking flags here
LFLAGS   = -L /home/emip/Desktop/Cours/TER/Libs/decompresse/RHPC_2.0/ext/Boost/Boost_1.54/lib/ -L /home/emip/Desktop/Cours/TER/Libs/decompresse/RHPC_2.0/lib/ -L /usr/local/lib
LIB = -lrelogo-2.0 -lrepast_hpc-2.0 -lboost_mpi-mt-s -lboost_serialization-mt-s -lboost_system-mt-s -lboost_filesystem-mt-s -lboost_thread-mt-s -lSDL2

# change these to set the proper directories where each files shoould be
SRCDIR  = src
HEADIR  = include
OBJDIR   = obj
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
