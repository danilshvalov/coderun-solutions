.PHONY: conan configure build

all: run

conan:
	conan install -if build . -s build_type=Debug --build=missing

configure: conan
	cmake -B build \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake

build: configure
	cmake --build build -j $(nproc)

run: build
	./build/shortest-path-length

run-tests: build
	./build/shortest-path-length-test

clean:
	rm -rf build
