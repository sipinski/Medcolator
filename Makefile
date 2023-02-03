source_files = $(shell find . -type f -iname '*.cpp' | sed 's/^\.\.\/src\///')
obj_files = $(subst .cpp,.o,$(source_files))

CXXFLAGS = -O3 -g -lvlc -lm -lserial `sdl-config --cflags --libs` -lSDL -lSDLmain -D__STDC_CONSTANT_MACROS -Wno-deprecated-declarations
CFLAGS = $(CXXFLAGS)
LDFLAGS = $(CXXFLAGS)
#CXX = clang++
CXX = g++

vpath %.cpp .

all: medcolator

medcolator: $(obj_files)
	$(CXX) $^ -o $@ $(CXXFLAGS)
	mkdir -p build/ && cp $@ build/ && cp config.ini build/

%.o: %.c
	-mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -c -o $@

.PHONY: all clean

clean:
	rm -rf $(obj_files) medcolator
