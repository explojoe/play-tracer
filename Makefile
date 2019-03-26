CXXFLAGS=-Wall -Iinclude -Iinclude/contrib -march=native
SRC_FILES=$(wildcard src/*.cpp)
INCLUDE_FILES=$(wildcard include/*.hpp)
OBJ_FILES=$(patsubst src/%.cpp,build/%.o,$(SRC_FILES))
OBJ_FILES_OPTIMIZED=$(patsubst src/%.cpp,build/optimized/%.o,$(SRC_FILES))

.PHONY: all test format clean run

all: | format test build/play-tracer

test: build/tests
	build/tests

format:
	echo $(SRC_FILES) $(HEADERS) | xargs clang-format -style=file -fallback-style=llvm -i

clean: 
	rm -rf build

run: build/play-tracer
	build/play-tracer out.png
	feh -Z out.png

build/play-tracer: $(filter-out build/optimized/tests.o,$(OBJ_FILES_OPTIMIZED))
	@mkdir -p build
	g++ $(CXXFLAGS) $^ -o $@

build/tests: $(filter-out build/main.o,$(OBJ_FILES))
	@mkdir -p build
	g++ $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp $(INCLUDE_FILES)
	@mkdir -p build
	g++ $(CXXFLAGS) -c $< -o $@

build/optimized/%.o: src/%.cpp $(INCLUDE_FILES)
	@mkdir -p build/optimized
	g++ $(CXXFLAGS) -O3 -DCATCH_CONFIG_FAST_COMPILE=1 -DCATCH_CONFIG_DISABLE=1 -c $< -o $@
