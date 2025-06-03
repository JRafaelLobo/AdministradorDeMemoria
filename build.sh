#!/bin/bash

SRC_DIR="src"
INCLUDE_DIR="include"
BIN_DIR="bin"
OUTPUT="$BIN_DIR/app"

mkdir -p $BIN_DIR

echo "Comando realizado: -std=c++17" "-Wall" "-I" $INCLUDE_DIR $SRC_DIR/*.cpp "-o" $OUTPUT
echo "-------------------------------------"
g++ -std=c++17 -Wall -I$INCLUDE_DIR $SRC_DIR/*.cpp -o $OUTPUT

if [ $? -eq 0 ]; then
    echo "✅ Compilado con éxito. Ejecutando..."
    echo "-------------------------------------"
    ./$OUTPUT
else
    echo "❌ Error en la compilación."
fi