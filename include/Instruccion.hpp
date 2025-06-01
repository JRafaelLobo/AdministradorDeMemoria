#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "Tipos.hpp"

class Instruccion
{
private:
    std::string entrada;
    std::string direccion;
    char operacion;
    void procesarEntrada();

public:
    Instruccion(const std::string &linea);
    ~Instruccion();
    std::string getDireccion() const;
    char getOperacion() const;
    void setEntrada(const std::string &nuevaEntrada);
    void mostrar() const;
};
