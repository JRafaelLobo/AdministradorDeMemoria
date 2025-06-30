#include "Proceso.hpp"
#include "AdminMemoria.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

int RealizarAnalisis(std::string ruta)
{
    size_t nAlgoritmos = 4;
    AlgoritmoDeReemplazo A[nAlgoritmos] = {
        AlgoritmoDeReemplazo::FIFO,
        AlgoritmoDeReemplazo::LRU,
        AlgoritmoDeReemplazo::CLOCK,
        AlgoritmoDeReemplazo::OPT
    };

    std::cout << "\nAnalisis de archivo: " << ruta << "\n";
    std::cout << std::left
              << std::setw(10) << "Algoritmo"
              << std::setw(8)  << "Frames"
              << std::setw(12) << "PageFaults"
              << std::setw(12) << "HitRate (%)"
              << std::setw(10) << "EAT (ns)"
              << "\n";

    std::cout << std::string(58, '-') << "\n";

    for (size_t i = 0; i < nAlgoritmos; i++)
    {
        int frames[] = {10, 50, 100};
        for (int f : frames)
        {
            AdminMemoria a(f, 4096, 11, 100000000);
            a.addProceso(ruta);
            a.setAlgoritmo(A[i]);
            a.ciclo();

            double hitrate = a.getHitRate() * 100.0;
            double eat = a.getEATS(100, 10000);

            std::cout << std::left
                      << std::setw(10) << toString(A[i])
                      << std::setw(8)  << f
                      << std::setw(12) << a.getPageFaults()
                      << std::fixed << std::setprecision(2)
                      << std::setw(12) << hitrate
                      << std::setw(10) << eat
                      << "\n";
        }
    }
    return 1;
}


int main()
{
    RealizarAnalisis("ArchivosParaTrabajar/bzip.trace");
    RealizarAnalisis("ArchivosParaTrabajar/gcc.trace");
    //RealizarAnalisis("ArchivosParaTrabajar/Aleatorio.trace");
    return 0;
}
