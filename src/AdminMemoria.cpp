#include "AdminMemoria.hpp"

AdminMemoria::AdminMemoria(int frames, int tam_paginas, int promedioBytesPorLinea)
    : frames(frames), tam_paginas(tam_paginas), promedioBytesPorLinea(promedioBytesPorLinea) {}

AdminMemoria::~AdminMemoria() {}

bool AdminMemoria::addProceso(std::string ruta)
{
    procesos.push_back(std::make_unique<Proceso>(ruta, numRegistroProcesos, promedioBytesPorLinea));
    return false;
}

void AdminMemoria::ciclo()
{

    switch (planificacion)
    {
    case Planificador::FCFS:
        for (size_t i = 0; i < procesos.size(); i++)
        {
            /* code */
        }

        /* code */
        break;
    case Planificador::SJF:
        /* code */
        break;
    case Planificador::SRTN:
        /* code */
        break;
    default:
        std::cerr << "Error:No hay Planificacion de Memoria" << std::endl;
        break;
    }

    switch (algoritmoDeReemplazo)
    {
    case AlgoritmoDeReemplazo::FIFO:
        /* code */
        break;
    case AlgoritmoDeReemplazo::LRU:
        /* code */
        break;
    case AlgoritmoDeReemplazo::OPT:
        /* code */
        break;
    default:
        std::cerr << "Error:No hay metodo de administracion de Memoria" << std::endl;
        break;
    }
}

void AdminMemoria::cicloFIFO()
{
}

void AdminMemoria::cicloLRU()
{
}

void AdminMemoria::cicloOPT()
{
}

int AdminMemoria::getPageFaults()
{
    return 0;
}