CXXFLAGS=-O3 -Wall -Iinclude -march=native
SRC_FILES=$(wildcard src/*.cpp)
INCLUDE_FILES=$(wildcard include/*.hpp)
OBJ_FILES=$(patsubst src/%.cpp,build/%.o,$(SRC_FILES))

.PHONY: all format clean

all: build/play-tracer format

format:
	echo $(SRC_FILES) $(HEADERS) | xargs clang-format -style=file -fallback-style=llvm -i

clean:
	rm -rf build

build/play-tracer: $(OBJ_FILES)
	@mkdir -p build
	g++ $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp $(INCLUDE_FILES)
	@mkdir -p build
	g++ $(CXXFLAGS) -c $< -o $@
