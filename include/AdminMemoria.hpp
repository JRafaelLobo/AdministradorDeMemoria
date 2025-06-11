#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <memory>
#include "Proceso.hpp"
#include "Tipos.hpp"
#include "Page.hpp"

class AdminMemoria
{
private:
    size_t frames;             // 10 recomendado
    uint32_t tam_paginas;      // 4096 recomendado
    int promedioBytesPorLinea; // 11 recomendado
    int tamCiclos;             // 1000 recomendado
    std::vector<std::unique_ptr<Proceso>> procesos;
    std::list<std::string> ordenPaginas;

    std::vector<std::string> secuenciaReferencias;
    bool referenciasCargadas = false;
    size_t posActual = 0;

    std::unordered_map<std::string, std::pair<std::shared_ptr<Page>, std::list<std::string>::iterator>> memoriaPrincipal;
    std::unordered_map<std::string, std::shared_ptr<Page>> almacenamientoExterno;
    std::shared_ptr<Page> paginaUsadaActualmente;

    AlgoritmoDeReemplazo algoritmoDeReemplazo = AlgoritmoDeReemplazo::FIFO;
    Planificador planificacion = Planificador::FCFS;

    int ultimoProcesoEjecutado = -1;
    int numProcesoEjecutar = -1;
    int NumPageFaults = 0;
    int numRegistroProcesos = 0;

    void busquedaPagina();
    void remplazoFIFO();
    void remplazoLRU();
    void remplazoReloj();
    void remplazoOPT();
    void construirSecuenciaReferencias();

public:
    AdminMemoria(int frames, int tam_paginas, int promedioBytesPorLinea, int tamCiclos);
    ~AdminMemoria();
    bool addProceso(std::string ruta);
    void ciclo();
    int getPageFaults();
};
