#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Page
{
private:
    bool usada, sucia;
    int IdProceso;
    int IdPagina;
    std::string id;

public:
    Page(int IdProceso, int IdPagina);
    ~Page();

    std::string getId();
};
