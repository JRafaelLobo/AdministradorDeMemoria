#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "Instruccion.hpp"

class Proceso
{
private:
    std::string ruta, linea;
    int idProceso;
    int promedioBytesPorLinea;
    std::unique_ptr<std::ifstream> archivo;
    std::unique_ptr<Instruccion> instruccionActual;
    std::streamsize tamano;
    int estimadoInstrucciones, instruccionesLeidas;
    bool CalcularTamano();

public:
    Proceso(std::string ruta, int idProceso, int promedioBytesPorLinea);
    bool abrirArchivo();
    bool cerrarArchivo();
    bool leerLinea();
    bool estaAbierto();
    bool finArchivo();
    int getIdProceso() const;
    int getInstruccionesRestantes() const;
    int getEstimadoInstrucciones() const;
    const Instruccion *getInstruccionActual() const;
    std::string getLinea() const;
};
