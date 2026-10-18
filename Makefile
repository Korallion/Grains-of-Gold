#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp \
	   	src/initialize.cpp \
	   	src/render/*.cpp \
	   	src/objects/*.cpp

#CC specifies which compiler we're using
COMP = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Isrc add /src as a base for include statments
COMP_FLAGS = -w -Isrc

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_Name specifies the name of our executable
OBJ_NAME = grains

#This is the target that compiles our executable
all : $(OBJS)
	$(COMP) $(OBJS) $(COMP_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
