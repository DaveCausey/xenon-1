.PHONY: tags 

all:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && cd .. && make -C build -j12

debug:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && cd .. && make -C build -j12

serial:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make VERBOSE=1 && cd ..

clean:
	rm -f include/ict/xddl.h
	rm -rf o
	test -d build && make -C build clean
	test -d build && rm -rf build

test:
	make TEST_OUTPUT_ON_FAILURE=1 -C build test

tags:
	mkdir -p o
	@echo Making tags...
	/usr/bin/find . -name '*.c' -o -name '*.cpp' -o -name '*.h' | grep -v "moc_" | grep -v "ui_" | grep -v "/o/"> o/flist && \
	ctags --file-tags=yes --language-force=C++ -L o/flist
	@echo tags complete.

# tags on mac
mtags:
	mkdir -p o
	@echo Making tags...
	/usr/bin/find . -name '*.c' -o -name '*.cpp' -o -name '*.h' | grep -v "moc_" | grep -v "ui_" | grep -v "/o/"> o/flist && \
	/usr/local/bin/ctags --file-tags=yes --language-force=C++ -L o/flist
	@echo tags complete.

