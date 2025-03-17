
.PHONY: all clean

all:
	cmake --toolchain=cmake/toolchain.cmake -S . -B build && $(MAKE) -C build

clean:
	rm -r build || true

clean-build:
	rm -r build || true
	cmake --toolchain=cmake/toolchain.cmake -S . -B build && $(MAKE) -C build