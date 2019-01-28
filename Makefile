CC = g++
CCFLAGS = -std=c++11
IPATH = -I./include -I./include/freetype2 -I./headers
LPATH = -L./lib  -L./lib/ttf
SRC_PATH = ./src
FILES = $(SRC_PATH)/main.cpp \
		$(SRC_PATH)/glad.c \
		$(SRC_PATH)/game.cpp \
		$(SRC_PATH)/shader.cpp \
		$(SRC_PATH)/texture.cpp \
		$(SRC_PATH)/resourceManager.cpp \
		$(SRC_PATH)/spriteRenderer.cpp \
		$(SRC_PATH)/gameObject.cpp \
		$(SRC_PATH)/gameLevel.cpp \
		$(SRC_PATH)/ballObject.cpp \
		$(SRC_PATH)/particleGenerator.cpp 
NAME = main
LIBS = -lmingw32 -lopengl32 -lSDL2main -lSDL2 -lSDL2_image -lfreetype

all:
	$(CC) $(CCFLAGS) $(IPATH) $(LPATH) $(FILES) $(LIBS) -o $(NAME)