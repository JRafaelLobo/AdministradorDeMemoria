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
void AdminMemoria::construirSecuenciaReferencias()
{
    if (referenciasCargadas)
        return;

    for (auto &proceso : procesos)
    {
        proceso->abrirArchivo();
        while (proceso->leerLinea())
        {
            const Instruccion *instruccion = proceso->getInstruccionActual();
            int idproceso = proceso->getIdProceso();
            uint32_t idPagina = instruccion->getPaginaId(tam_paginas);
            std::string direccion = std::to_string(idproceso) + "-" + std::to_string(idPagina);
            secuenciaReferencias.push_back(direccion);
        }
        proceso->cerrarArchivo();
        proceso->abrirArchivo();
    }
    referenciasCargadas = true;
}

void AdminMemoria::ciclo()
{
    if (!referenciasCargadas)
        construirSecuenciaReferencias();

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

    if (p->finArchivo())
    {
        procesos.erase(procesos.begin() + numProcesoEjecutar);
        p->cerrarArchivo();
        return;
    }
    int idproceso = p->getIdProceso();
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

        uint32_t idPagina = instruccion->getPaginaId(tam_paginas);
        std::string direccion = std::to_string(idproceso) + "-" + std::to_string(idPagina);
        if (memoriaPrincipal.find(direccion) != memoriaPrincipal.end())
        {
            if (algoritmoDeReemplazo == AlgoritmoDeReemplazo::LRU ||
                algoritmoDeReemplazo == AlgoritmoDeReemplazo::CLOCK)
            {
                auto it = memoriaPrincipal.find(direccion);
                ordenPaginas.erase(it->second.second);
                ordenPaginas.push_back(direccion);
                it->second.second = std::prev(ordenPaginas.end());

                if (algoritmoDeReemplazo == AlgoritmoDeReemplazo::CLOCK)
                {
                    it->second.first->usada = true;
                }
            }
            continue;
        }

        NumPageFaults++;

        auto it = almacenamientoExterno.find(direccion);
        if (it != almacenamientoExterno.end())
        {
            // std::cout << "✅ Página encontrada en almacenamiento" << std::endl;
            paginaUsadaActualmente = it->second;
        }
        else
        {
            // std::cout << "❌ Página NO encontrada en almacenamiento" << std::endl;
            paginaUsadaActualmente = std::make_shared<Page>(idproceso, idPagina);
            almacenamientoExterno[paginaUsadaActualmente->getId()] = paginaUsadaActualmente;
            // std::cout << paginaUsadaActualmente->getId() << std::endl;
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
            remplazoOPT();
            break;
        case AlgoritmoDeReemplazo::CLOCK:
            remplazoReloj();
            break;
        default:
            std::cout << "No hay un algoritmo seleccionado" << std::endl;
            break;
        }
        posActual++;
    }
}

void AdminMemoria::remplazoFIFO()
{

    if (memoriaPrincipal.size() >= frames)
    {
        std::string paginaReemplazada = ordenPaginas.front();
        ordenPaginas.pop_front();
        memoriaPrincipal.erase(paginaReemplazada);
    }

    ordenPaginas.push_back(paginaUsadaActualmente->getId());

    memoriaPrincipal[paginaUsadaActualmente->getId()] = {
        paginaUsadaActualmente, std::prev(ordenPaginas.end())};
}

void AdminMemoria::remplazoLRU()
{
    std::string id = paginaUsadaActualmente->getId();

    auto it = memoriaPrincipal.find(id);

    if (it != memoriaPrincipal.end())
    {
        ordenPaginas.erase(it->second.second);
        ordenPaginas.push_back(id);
        it->second.second = std::prev(ordenPaginas.end());
    }
    else
    {
        if (memoriaPrincipal.size() >= frames)
        {
            std::string paginaReemplazada = ordenPaginas.front();
            ordenPaginas.pop_front();
            memoriaPrincipal.erase(paginaReemplazada);
        }
        ordenPaginas.push_back(id);

        memoriaPrincipal[id] = {
            paginaUsadaActualmente,
            std::prev(ordenPaginas.end())};
    }
}

void AdminMemoria::remplazoReloj()
{
    std::string id = paginaUsadaActualmente->getId();

    auto it = memoriaPrincipal.find(id);

    if (it != memoriaPrincipal.end())
    {
        it->second.first->usada = true;
        ordenPaginas.erase(it->second.second);
        ordenPaginas.push_back(id);
        it->second.second = std::prev(ordenPaginas.end());
    }
    else
    {
        if (memoriaPrincipal.size() >= frames)
        {
            std::string paginaReemplazada = ordenPaginas.front();
            auto itReemplazo = memoriaPrincipal.find(paginaReemplazada);

            if (itReemplazo != memoriaPrincipal.end() && itReemplazo->second.first->sucia)
            {
                std::cout << "Guardando página sucia: " << paginaReemplazada << std::endl;
            }

            ordenPaginas.pop_front();
            memoriaPrincipal.erase(paginaReemplazada);
        }

        ordenPaginas.push_back(id);

        if (procesos.at(numProcesoEjecutar)->getInstruccionActual()->getOperacion() == 'R')
        {
            paginaUsadaActualmente->usada = true;
            paginaUsadaActualmente->sucia = false;
        }
        else
        {
            paginaUsadaActualmente->usada = true;
            paginaUsadaActualmente->sucia = true;
        }

        memoriaPrincipal[id] = {
            paginaUsadaActualmente,
            std::prev(ordenPaginas.end())};
    }
}

void AdminMemoria::remplazoOPT()
{
    std::string idNueva = paginaUsadaActualmente->getId();

    if (memoriaPrincipal.size() < frames)
    {
        ordenPaginas.push_back(idNueva);
        memoriaPrincipal[idNueva] = {paginaUsadaActualmente, std::prev(ordenPaginas.end())};
        return;
    }

    std::string paginaARemover;
    size_t maxDistancia = 0;

    for (const auto &[idMemoria, _] : memoriaPrincipal)
    {
        size_t distancia = 0;
        bool encontrada = false;

        for (size_t i = posActual + 1; i < secuenciaReferencias.size(); ++i)
        {
            if (secuenciaReferencias[i] == idMemoria)
            {
                distancia = i - posActual;
                encontrada = true;
                break;
            }
        }

        if (!encontrada)
        {
            paginaARemover = idMemoria;
            break;
        }

        if (distancia > maxDistancia)
        {
            maxDistancia = distancia;
            paginaARemover = idMemoria;
        }
    }

    if (memoriaPrincipal.find(paginaARemover) != memoriaPrincipal.end())
    {
        ordenPaginas.erase(memoriaPrincipal[paginaARemover].second);
        memoriaPrincipal.erase(paginaARemover);
    }

    ordenPaginas.push_back(idNueva);
    memoriaPrincipal[idNueva] = {paginaUsadaActualmente, std::prev(ordenPaginas.end())};
}

int AdminMemoria::getPageFaults()
{
    return NumPageFaults;
}