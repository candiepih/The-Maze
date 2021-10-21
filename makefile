#OBJS specifies which files to compile as part of the project
OBJS = src/*.c

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -ISDL2\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LSDL2\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Wall -Werror -Wextra -pedantic

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
LINUX_LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = maze

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

#Linux SDL compiling
linux : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINUX_LINKER_FLAGS) -DLINUX -o $(OBJ_NAME)

#Linux SDL installation
linux_install : 
	sudo apt-get install libsdl2-dev

#MAC SDL compiling
mac : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINUX_LINKER_FLAGS) -DMAC -o $(OBJ_NAME)
