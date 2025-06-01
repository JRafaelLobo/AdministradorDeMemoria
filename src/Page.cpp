#include "Page.hpp"

Page::Page(int IdProceso, int IdPagina) : IdProceso(IdProceso), IdPagina(IdPagina)
{
    id = IdPagina + "-" + IdProceso;
}

Page::~Page() {}

std::string Page::getId()
{
    return id;
}
