SRC_FILES = ${wildcard ${SRC_DIR}/*.cc} $(wildcard ${SRC_DIR}/**/*.cc)
OBJ_FILES = $(patsubst %.cc, $(BIN_DIR)/%.o, $(notdir ${SRC_FILES}))

SRC_DIR = src
BIN_DIR = bin
OUT_DIR = debug
FILENAME = program

CC = g++ -g
CFLAGS = -c -Wall
CFLAGS += -Isrc -Ilib/glad/include -Ilib/glfw/include -Ilib/freetype/include

LDFLAGS = -lm lib/glad/src/glad.o lib/freetype/build/libfreetype.a

ifeq ($(OS),Windows_NT)
LDFLAGS += lib/glfw/lib/libglfw3dll.a
else
LDFLAGS += lib/glfw/src/libglfw3.a
endif

all: clean ${OUT_DIR}/${FILENAME}

build: libs dirs clean ${OUT_DIR}/${FILENAME}

dirs:
	mkdir -p ${BIN_DIR} ${OUT_DIR}

ifneq ($(OS),Windows_NT)
libs:
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	cd lib/glfw && cmake . && make
	mkdir -p lib/freetype/build
	cd lib/freetype/build && cmake .. && make
else
libs:
	mkdir -p lib/freetype/build
	cd lib/freetype/build && cmake .. -G "MinGW Makefiles" && make
endif

${OUT_DIR}/${FILENAME}: $(OBJ_FILES) 
	${CC} -o $@ $^ ${LDFLAGS}

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cc
	${CC} -o $@ $< $(CFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/*/%.cc
	${CC} -o $@ $< $(CFLAGS)

run:
	./${OUT_DIR}/${FILENAME}

clean:
	rm -rf ${BIN_DIR}/* ${OUT_DIR}/program.exe