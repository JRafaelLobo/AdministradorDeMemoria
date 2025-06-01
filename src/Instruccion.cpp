#include "Instruccion.hpp"

Instruccion::Instruccion(const std::string &linea) : entrada(linea)
{
    procesarEntrada();
}
Instruccion::~Instruccion() {}

void Instruccion::procesarEntrada()
{
    std::istringstream iss(entrada);
    iss >> direccion >> operacion;
}

std::string Instruccion::getDireccion() const
{
    return direccion;
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
    std::cout << "Direccion: " << direccion << ", Operacion: " << operacion << std::endl;
}
