#include "AdminMemoria.hpp"

AdminMemoria::AdminMemoria(int frames, int tam_paginas, int promedioBytesPorLinea, int tamCiclos)
    : frames(frames), tam_paginas(tam_paginas), promedioBytesPorLinea(promedioBytesPorLinea), tamCiclos(tamCiclos) {}

AdminMemoria::~AdminMemoria() {}

bool AdminMemoria::addProceso(std::string ruta)
{
    procesos.push_back(std::make_unique<Proceso>(ruta, numRegistroProcesos, promedioBytesPorLinea));
    numRegistroProcesos++;
    return true;
}

void AdminMemoria::ciclo()
{
    switch (planificacion)
    {
    case Planificador::FCFS:
        if (procesos.size() > 0)
        {
            numProcesoEjecutar = 0;
        }
        else
        {
            numProcesoEjecutar = -1;
        }
        break;
    case Planificador::SJF:
        if (numProcesoEjecutar == -1 && procesos.size() > 0)
        {
            numProcesoEjecutar = 0;
        }
        for (size_t i = 0; i < procesos.size(); i++)
        {
            int procesoTest = procesos.at(i)->getEstimadoInstrucciones();
            if (procesoTest < procesos.at(numProcesoEjecutar)->getEstimadoInstrucciones())
            {
                numProcesoEjecutar = i;
            }
        }
        break;
    case Planificador::SRTN:
        if (numProcesoEjecutar == -1 && procesos.size() > 0)
        {
            numProcesoEjecutar = 0;
        }
        for (size_t i = 0; i < procesos.size(); i++)
        {
            int procesoTest = procesos.at(i)->getInstruccionesRestantes();
            if (procesoTest < procesos.at(numProcesoEjecutar)->getInstruccionesRestantes())
            {
                numProcesoEjecutar = i;
            }
        }
        break;
    default:
        std::cerr << "Error:No hay Planificacion de Memoria" << std::endl;
        break;
    }
    busquedaPagina();
}

void AdminMemoria::busquedaPagina()
{
    if (numProcesoEjecutar == -1)
    {
        ultimoProcesoEjecutado = -1;
        std::cout << "No hay proceso a Ejecutar" << std::endl;
        return;
    }
    Proceso *p = procesos.at(numProcesoEjecutar).get();
    p->abrirArchivo();
    if (p->finArchivo())
    {
        procesos.erase(procesos.begin() + numProcesoEjecutar);
        p->cerrarArchivo();
        return;
    }
    ultimoProcesoEjecutado = numProcesoEjecutar;

    for (int i = 0; i < tamCiclos; i++)
    {
        if (!p->leerLinea())
        {
            std::cout << "NO HAY" << std::endl;
            procesos.erase(procesos.begin() + numProcesoEjecutar);
            ultimoProcesoEjecutado = -1;
            p->cerrarArchivo();
            return;
        }

        const Instruccion *instruccion = nullptr;
        try
        {
            instruccion = p->getInstruccionActual();
        }
        catch (const std::exception &e)
        {
            std::cerr << "❌ Excepción atrapada: " << e.what() << " en ciclo " << i << std::endl;
            break;
        }

        int idproceso = p->getIdProceso();
        uint32_t idPagina = instruccion->getPaginaId(tam_paginas);
        std::string direccion = std::to_string(idproceso) + "-" + std::to_string(idPagina);

        if (memoriaPrincipal.find(direccion) != memoriaPrincipal.end())
        {
            std::cout << "✅ Página encontrada en memoria" << std::endl;
            std::cout << direccion << std::endl;
            continue;
        }

        NumPageFaults++;
        std::cout << "❌ Página NO encontrada en memoria" << std::endl;

        auto it = almacenamientoExterno.find(direccion);
        if (it != almacenamientoExterno.end())
        {
            std::cout << "✅ Página encontrada en almacenamiento" << std::endl;
            paginaUsadaActualmente = it->second;
        }
        else
        {
            std::cout << "❌ Página NO encontrada en almacenamiento" << std::endl;
            paginaUsadaActualmente = std::make_shared<Page>(idproceso, idPagina);
            std::cout << paginaUsadaActualmente->getId() << std::endl;
        }

        switch (algoritmoDeReemplazo)
        {
        case AlgoritmoDeReemplazo::FIFO:
            remplazoFIFO();
            break;
        case AlgoritmoDeReemplazo::LRU:
            remplazoLRU();
            break;
        case AlgoritmoDeReemplazo::OPT:
            cicloOPT();
            break;
        default:
            std::cout << "No hay un algoritmo seleccionado" << std::endl;
            break;
        }
    }

    p->cerrarArchivo();
}

void AdminMemoria::remplazoFIFO()
{
    
}

void AdminMemoria::remplazoLRU()
{
}

void AdminMemoria::cicloOPT()
{
}

int AdminMemoria::getPageFaults()
{
    return NumPageFaults;
}