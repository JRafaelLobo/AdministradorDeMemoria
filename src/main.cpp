#include "Proceso.hpp"
#include "AdminMemoria.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    AdminMemoria a(100, 4096, 11, 1000000);
    // a.addProceso("ArchivosParaTrabajar/gcc.trace");
    // a.addProceso("ArchivosParaTrabajar/bzip.trace");
    // a.addProceso("ArchivosParaTrabajar/programaAleatorio1.trace");
    // a.addProceso("ArchivosParaTrabajar/bzip.trace");
    a.addProceso("ArchivosParaTrabajar/bzip.trace");

    for (size_t i = 0; i < 5; i++)
    {
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " ----------------------------" << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        a.ciclo();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " ----------------------------" << std::endl;
    }
    std::cout << a.getPageFaults() << std::endl;
    return 0;
}
