import random

def generar_trace_memoria(filename, num_referencias=1_000_000, prob_write=0.1):
    with open(filename, 'w') as f:
        for _ in range(num_referencias):
            direccion = random.randint(0, 0xFFFFFFFF)
            operacion = 'W' if random.random() < prob_write else 'R'
            f.write(f"{direccion:08x} {operacion}\n")

c = 1000000
generar_trace_memoria("memoria.trace", c)
print(f"Archivo memoria.trace generado con {c} referencias.")
