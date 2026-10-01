# Assignment 2

## How to compile 

> Note: Clang 17 or newer is needed for this or any other compiler that supports c++23

### Task 1:
compile each file
```bash
clang++ -std=c++23 -c main.cpp -o main.o
clang++ -std=c++23 -c fibonacci.cpp -o fibonacci.o
```

link
```bash
clang++ -std=c++23 main.o fibonacci.o -o fib.out
```

run
```bash
./fib.out
```

### Task 2:
#### Step 1 | Preprocess
```bash
clang++ -std=c++23 -E fibonacci.cpp -o fibonacci.ii
```

#### Step 2 | Compile
```bash
clang++ -std=c++23 -S fibonacci.ii -o fibonacci.s
```

#### Step 3 | Assemble
```bash
clang++ -std=c++23 -c fibonacci.s -o fibonacci_from_asm.o
```

#### Step 4 | Link
```bash
clang++ -std=c++23 main.o fibonacci_from_asm.o -o fib.out
```

#### Step 5 | Run
```bash
./fib.out
```

#### Task 3 | Explanation:
1. What do the .ii, .s, object, and executable files contain? Which are text files,
which are binary files, and which build stage produces each one?
```
.ii is preprocessed c++, it is the text one, it contains exapnded headers that was added with #include and also the original code. 
.s is assembler code, it is also the text file< which contains assembler instructions
.o (object) is a binary one, it compiles assembler to the binary instructions (machine code), which can be readed by proccessor
.out / .exe (executable) also a binary one, it links objects and gives arranges order (byte location) for instructions from object files
```

2. Why can main.cpp compile when it sees a function declaration but not the
function body? Why does linking still need the definition?
```
beacuse, it just checks that the declaration exists, but actual connection to the definition happens only on the linking stage
```

3. What does the include guard prevent? If both .cpp files include the same header,
does the guard stop the second source file from seeing its contents?

```
no, it just create one place of the header with its location, which both .cpp can read
```
4. Which object files must be rebuilt after changing only a function body in
fibonacci.cpp? What changes if you edit a declaration in the shared header?

```
if only definition is cahgned - then it is only fibonacci.cpp + relink
if both definition and declaration - then it is fibonacci.cpp and all the *.cpp which includes it + relink
```

#### Task 4.1:


ERROR:
```cpp
main.cpp:5:24: error: use of undeclared identifier 'fibonacci_recursive'
    5 |     std::print("{}\n", fibonacci_recursive(2));
      |                        ^~~~~~~~~~~~~~~~~~~
main.cpp:6:24: error: use of undeclared identifier 'fibonacci_recursive'
    6 |     std::print("{}\n", fibonacci_recursive(10));
      |                        ^~~~~~~~~~~~~~~~~~~
main.cpp:8:24: error: use of undeclared identifier 'fibonacci_iterative'
    8 |     std::print("{}\n", fibonacci_iterative(2));
      |                        ^~~~~~~~~~~~~~~~~~~
main.cpp:9:24: error: use of undeclared identifier 'fibonacci_iterative'
    9 |     std::print("{}\n", fibonacci_iterative(10));
      |                        ^~~~~~~~~~~~~~~~~~~
4 errors generated.
```

**Explanation:**
```
declaration of function used in the main() function are neeeded. At least, declaration, which are in header needed to compile main.cp to object. Resolving and placing actual symbols (linking to the declaration) will happen on the linking stage
```


#### Task 4.2:

ERROR:
```cpp
Undefined symbols for architecture arm64:
  "fibonacci_iterative(int)", referenced from:
      _main in main.o
      _main in main.o
  "fibonacci_recursive(int)", referenced from:
      _main in main.o
      _main in main.o
ld: symbol(s) not found for architecture arm64
```

**Explanation:**
```
now, definition (symbols) were not found on the linking stage, so function can not be executed in any way.
```