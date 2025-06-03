#include "Proceso.hpp"

Proceso::Proceso(std::string ruta, int idProceso, int promedioBytesPorLinea)
    : ruta(ruta), idProceso(idProceso), promedioBytesPorLinea(promedioBytesPorLinea), archivo(std::make_unique<std::ifstream>(ruta)) {}

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
        return false;
    }

    archivo->close();
    return true;
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

int Proceso::getIdProceso() const
{
    return idProceso;
}

int Proceso::getInstruccionesRestantes() const
{
    int instruccionesRestantes = estimadoInstrucciones - instruccionesLeidas;
    return instruccionesRestantes;
}

int Proceso::getEstimadoInstrucciones() const
{
    return estimadoInstrucciones;
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
