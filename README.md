# testing-mission2

## Project structure

- `lib/` - shared lib between 2 programs
- `programm1/` — first programm (multithread, stdio, client).
- `programm2/` — second programm (server, stdout).

## Requirements

- CMake >= 3.15
- Gcc compiler

## Building project

Go to project root directory and type to build:
``` bash
mkdir build && cd build
cmake ..
cmake --build .
```
Then you can run programs:
``` bash
./programm1/programm1
./programm2/programm2 
```
