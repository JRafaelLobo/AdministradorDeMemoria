# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC_DIR = src
BIN_DIR = bin
TARGET = $(BIN_DIR)/app

# Encuentra todos los archivos fuente .cpp dentro de src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Cambia extensión de .cpp a .o y mueve a obj/
OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Crear directorio obj para objetos .o
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

# Regla principal: compilar y linkear
all: $(TARGET)

# Linkear el ejecutable con todos los objetos
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar cada archivo fuente a objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
