#include "Instruccion.hpp"

Instruccion::Instruccion(const std::string &linea) : entrada(linea)
{
    procesarEntrada();
}
Instruccion::~Instruccion() {}

void Instruccion::procesarEntrada()
{
    std::istringstream iss(entrada);
    iss >> direccionString >> operacion;
}

uint32_t Instruccion::getDireccion() const
{
    return std::stoul(direccionString, nullptr, 16);
}

char Instruccion::getOperacion() const
{
    return operacion;
}

void Instruccion::setEntrada(const std::string &nuevaEntrada)
{
    entrada = nuevaEntrada;
    procesarEntrada();
}

void Instruccion::mostrar() const
{
    std::cout << "Direccion: " << direccionString << ", Operacion: " << operacion << std::endl;
}

uint32_t Instruccion::getPaginaId(uint32_t tam_paginas) const
{
    uint32_t idPagina = getDireccion() / tam_paginas;
    return idPagina;
}
