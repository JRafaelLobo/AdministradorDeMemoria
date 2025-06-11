#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Page
{
private:
    int IdProceso;
    int IdPagina;
    std::string id;

public:
    bool usada, sucia;
    Page(int IdProceso, int IdPagina);
    ~Page();

    std::string getId();
};
