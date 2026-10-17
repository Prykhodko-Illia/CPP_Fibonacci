# Assignment 3

## Task 1

### Layout
```
├── CMakeLists.txt
└── source
    ├── CMakeLists.txt
    ├── application
    │   ├── CMakeLists.txt
    │   ├── include
    │   └── src
    │       └── main.cpp
    └── libraries
        ├── CMakeLists.txt
        └── fibonacci
            ├── CMakeLists.txt
            ├── include
            │   └── fibonacci.hpp
            └── src
                └── fibonacci.cpp
```

### Explanation 'link target' vs 'add_subdirectory'

`add_subdirectory()` command only tells where another `CMakeLists.txt` can be found and read to gather configurations from there
The command itself has no effect on the target, and files that are in this subdirectory are not linked to the target yet.

To provide sources `target_sources()` should be used with the list of source files, for the libraries or header files:
`target_link_libraries()` and `target_include_directories()` has to be used correspondingly

## Task 3

### Explanation `why the include path is PUBLIC while implementation sources and language are PRIVATE.`

Everything that only the target needs is PRIVATE: sources, languages, properties - it is the rule of good approach.

In `fibonacci_lib` target there is PUBLIC on `target_include_directories()`, as later this header `fibonacci.hpp` is used by the `fibonacci_app` target

## Task 4

### How to build

#### Debug
```bash
cmake -S . -B build/debug -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug --verbose
./build/debug/source/application/fibonacci_app
```

#### Release
```bash
cmake -S . -B build/debug -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --verbose
./build/release/source/application/fibonacci_app
```

## Task 5

### After change from `PUBLIC` to `PRIVATE`

```bash
Run Build Command(s): /opt/homebrew/bin/ninja -v
FAILED: [code=1] source/application/CMakeFiles/fibonacci_app.dir/src/main.cpp.o
/usr/bin/clang++   -g -std=c++2b -arch arm64 -MD -MT source/application/CMakeFiles/fibonacci_app.dir/src/main.cpp.o -MF source/application/CMakeFiles/fibonacci_app.dir/src/main.cpp.o.d -o source/application/CMakeFiles/fibonacci_app.dir/src/main.cpp.o -c /Users/illaprykhodko/Study/cpp-dev/assignment-1/source/application/src/main.cpp
/Users/illaprykhodko/Study/cpp-dev/assignment-1/source/application/src/main.cpp:3:10: fatal error: 'fibonacci.hpp' file not found
3 | #include "fibonacci.hpp"
|          ^~~~~~~~~~~~~~~
1 error generated.
ninja: build stopped: subcommand failed.
```

### Explanation

Now target `fibonacci_app` that has `main.cpp` in it, which requires `fibonacci.hpp` header fails.

`fibonacci_app` target still has `fibonacci_lib` library linked to it. However, it can not use anything from it, as sources, and headers (which is needed) are PRIVATE 