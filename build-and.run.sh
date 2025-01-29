#!/bin/bash

# Create necessary directories if they don't exist
mkdir -p bin/shared

# Compile main.cpp
echo "Compiling main.cpp..."
g++ -c src/main.cpp -o bin/main.o

# Compile card.cpp, game.cpp, and player.cpp as position-independent code (PIC)
echo "Compiling card.cpp..."
g++ -c -fPIC src/bingo_library/card.cpp -o bin/shared/card.o

echo "Compiling game.cpp..."
g++ -c -fPIC src/bingo_library/game.cpp -o bin/shared/game.o

echo "Compiling player.cpp..."
g++ -c -fPIC src/bingo_library/player.cpp -o bin/shared/player.o

# Create shared library
echo "Linking shared library libbingo_library.so..."
g++ -shared bin/shared/card.o bin/shared/game.o bin/shared/player.o -o bin/shared/libbingo_library.so

# Link main object with the shared library
echo "Linking use-shared-library executable..."
g++ bin/main.o -Lbin/shared -lbingo_library -o bin/use-shared-library

# Compile dynamic library loader
echo "Compiling dynamic-library-loader.cpp..."
g++ src/dynamic-library-loader.cpp -ldl -o bin/dynamic-library-loader

# Execute the dynamic library loader
echo "Running dynamic-library-loader..."
bin/dynamic-library-loader

