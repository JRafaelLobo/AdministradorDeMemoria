#include "Page.hpp"

Page::Page(int IdProceso, int IdPagina) : IdProceso(IdProceso), IdPagina(IdPagina)
{
    id = std::to_string(IdProceso) + "-" + std::to_string(IdPagina);
}

Page::~Page() {}

std::string Page::getId()
{
    return id;
}
