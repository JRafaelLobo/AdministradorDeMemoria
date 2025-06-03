#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include "Tipos.hpp"

class Instruccion
{
private:
    std::string entrada;
    std::string direccionString;
    char operacion;
    void procesarEntrada();

public:
    Instruccion(const std::string &linea);
    ~Instruccion();
    uint32_t getDireccion() const;
    char getOperacion() const;
    void setEntrada(const std::string &nuevaEntrada);
    void mostrar() const;
    uint32_t getPaginaId(uint32_t tam_paginas) const;
};
