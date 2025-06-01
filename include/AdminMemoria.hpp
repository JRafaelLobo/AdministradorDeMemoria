#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Proceso.hpp"
#include "Tipos.hpp"
#include "Page.hpp"

class AdminMemoria
{
private:
    int frames;                // 10 recomendado
    int tam_paginas;           // 4096 recomendado
    int promedioBytesPorLinea; // 11 recomendado
    std::vector<std::unique_ptr<Proceso>> procesos;
    std::unordered_map<std::string, Page> memoriaPrincipal;
    std::unordered_map<std::string, Page> almacenamientoExterno;
    AlgoritmoDeReemplazo algoritmoDeReemplazo = AlgoritmoDeReemplazo::FIFO;
    Planificador planificacion = Planificador::FCFS;

    int ultimoProcesoEjecutado = -1;
    int numProcesoEjecutar = -1;
    int NumPageFaults = 0;
    int numRegistroProcesos = 0;

    void cicloFIFO();
    void cicloLRU();
    void cicloOPT();

public:
    AdminMemoria(int frames, int tam_paginas, int promedioBytesPorLinea);
    ~AdminMemoria();
    bool addProceso(std::string ruta);
    void ciclo();
    int getPageFaults();
};
