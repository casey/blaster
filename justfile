run: build
	./tmp/main --resolution=1800p --route=blaster --left=10

build:
	make tmp/main

clean:
	make clean

deps:
	brew install astyle fftw glfw libpng portaudio portmidi yajl
	echo "syphon framework from: http://syphon.v002.info"
	echo "loopback from https://rogueamoeba.com/loopback"

package: build
	cp ./tmp/main ./tmp/rmr
	./bin/icon `./bin/pick ./rsc/icon/*.rsrc` ./tmp/rmr

db:
	lldb -- ./tmp/rmr --resolution=debug --route=blaster --left=10

sloc:
	cat `find -E . ! -name vec.c++ ! -name vec.h -regex '.*[.](c\+\+|cpp|h|glsl)'` | sed '/^\s*$$/d' | wc -l
