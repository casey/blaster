CXX := /usr/bin/clang++

DEBUG := y

ifeq ($(DEBUG),y)
CXXFLAGS += -O0
CXXFLAGS += -g
else
CXXFLAGS += -O3
CXXFLAGS += -emit-llvm
endif

CXXFLAGS += -D GL_SILENCE_DEPRECATION
CXXFLAGS += -D __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=0
CXXFLAGS += -F frameworks
CXXFLAGS += -I /opt/homebrew/include
CXXFLAGS += -Wall
# CXXFLAGS += -Werror
CXXFLAGS += -Wextra
CXXFLAGS += -Wfatal-errors
CXXFLAGS += -Winvalid-pch
CXXFLAGS += -Wno-bitwise-op-parentheses
CXXFLAGS += -Wno-deprecated-register
CXXFLAGS += -Wno-dollar-in-identifier-extension
CXXFLAGS += -Wno-import-preprocessor-directive-pedantic
CXXFLAGS += -Wno-missing-braces
CXXFLAGS += -Wno-null-pointer-arithmetic
CXXFLAGS += -Wno-sign-compare
CXXFLAGS += -Wno-unused-comparison
CXXFLAGS += -Wno-unused-function
CXXFLAGS += -Wno-unused-parameter
CXXFLAGS += -Wno-unused-private-field
CXXFLAGS += -Wno-unused-value
CXXFLAGS += -Wno-unused-variable
CXXFLAGS += -Wno-variadic-macros
CXXFLAGS += -Wno-vla-extension
CXXFLAGS += -pedantic
CXXFLAGS += -std=c++17
CXXFLAGS += -stdlib=libc++

LINKFLAGS += -F frameworks
LINKFLAGS += -L /opt/homebrew/lib
LINKFLAGS += -Wl,-rpath,@executable_path/../frameworks
LINKFLAGS += -framework Foundation
LINKFLAGS += -framework OpenGL
LINKFLAGS += -framework Syphon
LINKFLAGS += -lfftw3
LINKFLAGS += -lglfw
LINKFLAGS += -lobjc
LINKFLAGS += -lpng
LINKFLAGS += -lportaudiocpp
LINKFLAGS += -lportmidi
LINKFLAGS += -lyajl
LINKFLAGS += -rdynamic
LINKFLAGS += -std=c++17
LINKFLAGS += -stdlib=libc++

SOURCES  := $(wildcard *.c++)
OBJECTS  := $(patsubst %.c++,tmp/%.o,$(SOURCES))

tmp/main: $(OBJECTS)
	$(CXX) $(LINKFLAGS) $(OBJECTS) -o $@

tmp:
	mkdir -p tmp

tmp/common.h.gch: common.h | tmp
	$(CXX) $(CXXFLAGS) -x objective-c++-header $< -c -o $@

tmp/%.o: %.c++ vec.h vec_test.h tmp/common.h.gch | tmp
	$(CXX) $(CXXFLAGS) -x objective-c++ -include-pch tmp/common.h.gch -c $< -o $@

.PHONY: clean
clean:
	rm -rf tmp
