#include "Proceso.hpp"

Proceso::Proceso(std::string ruta, int numProceso, int promedioBytesPorLinea)
    : ruta(ruta), numProceso(numProceso), promedioBytesPorLinea(promedioBytesPorLinea), archivo(std::make_unique<std::ifstream>(ruta)) {}

bool Proceso::CalcularTamano()
{
    std::ifstream archivoTamano(ruta, std::ios::binary | std::ios::ate);
    if (!archivoTamano.is_open())
    {
        std::cerr << "Error: no se pudo abrir el archivo para calcular tamaño: " << ruta << std::endl;
        return false;
    }
    tamano = archivoTamano.tellg();
    estimadoInstrucciones = tamano / promedioBytesPorLinea;
    archivoTamano.close();
    return true;
}

bool Proceso::abrirArchivo()
{
    if (!archivo || !archivo->is_open())
    {
        std::cerr << "Error abriendo archivo " << ruta << std::endl;
        return false;
    }
    if (!CalcularTamano())
    {
        std::cerr << "Error calculando Tamaño" << ruta << std::endl;
        return false;
    }
    return true;
}

bool Proceso::cerrarArchivo()
{
    if (!archivo || !archivo->is_open())
    {
        archivo->close();
        return true;
    }
    return false;
}

bool Proceso::leerLinea()
{
    if (!archivo || !archivo->is_open() || archivo->eof())
        return false;
    if (std::getline(*archivo, linea))
    {
        instruccionActual = std::make_unique<Instruccion>(linea);
        return true;
    }
    return false;
}

bool Proceso::estaAbierto()
{
    return archivo->is_open();
}

bool Proceso::finArchivo()
{
    return archivo->eof();
}

std::string Proceso::getLinea() const
{
    return linea;
}
const Instruccion *Proceso::getInstruccionActual() const
{
    if (!instruccionActual)
        throw std::runtime_error("Instrucción no inicializada");
    return instruccionActual.get();
}
