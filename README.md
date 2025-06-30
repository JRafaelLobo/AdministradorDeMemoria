# Administrador de Memoria

Simulador de algoritmos de reemplazo de páginas en memoria, desarrollado en C++ como parte de un proyecto académico en el área de sistemas operativos y estructuras de datos.

## 📌 Descripción

Este programa simula el comportamiento de distintos algoritmos de reemplazo de páginas en memoria, permitiendo comparar su eficiencia con base en métricas como el número de fallos de página y el hit rate. Es una herramienta educativa útil para el análisis y comprensión de la gestión de memoria en sistemas operativos.

## ⚙️ Algoritmos Implementados

- **FIFO (First-In, First-Out)**
- **LRU (Least Recently Used)**
- **OPT (Óptimo)**
- **Clock**

## 🧠 Características

- Permite definir la cantidad de marcos de página (frames)
- Acepta una secuencia de referencias desde un .trace
- Muestra resultados en forma tabular para facilitar la comparación entre algoritmos.
- Cálculo automático de:
  - Número de fallos de página
  - Tasa de aciertos (hit rate)
  - Eficiencia relativa

## 🗂 Estructura del Proyecto

```
.
├── ArchivosParaTrabajar
│   ├── Aleatorio.trace
│   ├── bzip.trace
│   └── gcc.trace
│   └── ...archivos de ejemplo
├── HerramientasdeAyuda
│   ├── Documentacion
│   │   ├── Proyecto OS2.docx
│   │   └── Proyecto OS2.pdf
│   └── Generadordeltrace.py
├── README.md
├── bin
│   └── app
│   └── ...salidas
├── build.sh
├── include
│   ├── AdminMemoria.hpp
│   ├── Instruccion.hpp
│   ├── Page.hpp
│   ├── Proceso.hpp
│   └── Tipos.hpp
└── src
    ├── AdminMemoria.cpp
    ├── Instruccion.cpp
    ├── Page.cpp
    ├── Proceso.cpp
    └── main.cpp
```

## ▶️ Uso

1. Dar los permisos suficientes:

```bash
chmod +x build.sh
```
2. Ejecutar el programa:

```bash
./build.sh
```

## 📄 Formato del Archivo de Referencias

El archivo de referencia tiene que tener una direccion de x32 y R:read o W:write
Un ejemplo de como debe ser
```
38e4549e R
13cdcac4 W
ffe6a3ea R
a97ccd23 W
593004b8 R
98cf6714 R
```

## 📊 Ejemplo de Salida

Resultados obtenidos al ejecutar los algoritmos con distintas cantidades de marcos de página (frames):

| Algoritmo | Frames | Page Faults | Hit Rate (%) | EAT (ns) |
|-----------|--------|-------------|---------------|----------|
| FIFO      | 10     | 40385       | 95.96         | 503.85   |
| LRU       | 10     | 17120       | 98.29         | 271.20   |
| CLOCK     | 10     | 17120       | 98.29         | 271.20   |
| OPT       | 10     | 7608        | 99.24         | 176.08   |
## 📄 Documentacion del Proyecto
El informe de la realizacion de este proyecto se encuentra en este enlace.
 [Documentacion del proyecto (PDF)](./HerramientasdeAyuda/Documentacion/Proyecto%20OS2.pdf)