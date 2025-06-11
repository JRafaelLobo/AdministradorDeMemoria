#pragma once

#include <string>
#include <stdexcept>

enum class AlgoritmoDeReemplazo
{
    FIFO, // First In First Out
    LRU,  // Least Recently Used
    OPT,  // Optimal
    CLOCK
};

inline const char *toString(AlgoritmoDeReemplazo alg)
{
    switch (alg)
    {
    case AlgoritmoDeReemplazo::FIFO:
        return "FIFO";
    case AlgoritmoDeReemplazo::LRU:
        return "LRU";
    case AlgoritmoDeReemplazo::OPT:
        return "OPT";
    case AlgoritmoDeReemplazo::CLOCK:
        return "CLOCK";
    default:
        return "Desconocido";
    }
}

inline AlgoritmoDeReemplazo fromStringAlgoritmo(const std::string &s)
{
    if (s == "FIFO")
        return AlgoritmoDeReemplazo::FIFO;
    if (s == "LRU")
        return AlgoritmoDeReemplazo::LRU;
    if (s == "OPT")
        return AlgoritmoDeReemplazo::OPT;
    if (s == "CLOCK")
        return AlgoritmoDeReemplazo::CLOCK;
    throw std::invalid_argument("AlgoritmoDeReemplazo inválido: " + s);
}

inline const char *descripcion(AlgoritmoDeReemplazo alg)
{
    switch (alg)
    {
    case AlgoritmoDeReemplazo::FIFO:
        return "First In First Out";
    case AlgoritmoDeReemplazo::LRU:
        return "Least Recently Used";
    case AlgoritmoDeReemplazo::OPT:
        return "Optimal";
    case AlgoritmoDeReemplazo::CLOCK:
        return "Aproximación a LRU";
    default:
        return "Descripción desconocida";
    }
}
enum class Planificador
{
    FCFS, // First Come First Serve
    SJF,  // Shortest Job First
    SRTN, // Shortest Remaining Time Next
};

inline const char *toString(Planificador p)
{
    switch (p)
    {
    case Planificador::FCFS:
        return "FCFS";
    case Planificador::SJF:
        return "SJF";
    case Planificador::SRTN:
        return "SRTN";
    default:
        return "Desconocido";
    }
}

inline const char *descripcion(Planificador p)
{
    switch (p)
    {
    case Planificador::FCFS:
        return "First Come First Serve";
    case Planificador::SJF:
        return "Shortest Job First";
    case Planificador::SRTN:
        return "Shortest Remaining Time First";
    default:
        return "Descripción desconocida";
    }
}

inline Planificador fromStringPlanificador(const std::string &s)
{
    if (s == "FCFS")
        return Planificador::FCFS;
    if (s == "SJF")
        return Planificador::SJF;
    if (s == "SRTN")
        return Planificador::SRTN;
    throw std::invalid_argument("Planificador inválido: " + s);
}
