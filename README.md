# SO_Lab4
Laboratorio 4 Sistemas Operativos 2025

## Archivos

- `queue.c`: Cola segura usando mutex y condition variables.
- `producer_consumer.c`: Productor-consumidor con semáforos.
- `dining_philosophers.c`: Filósofos comensales evitando interbloqueo.

## Compilación

- gcc queue.c -o queue -pthread
- gcc producer_consumer.c -o producer_consumer -pthread
- gcc dining_philosophers.c -o dining_philosophers -pthread


## Ejecución

- ./queue
- ./producer_consumer
- ./dining_philosophers


## Resultados esperados

- queue: Se observa que productor y consumidor insertan y retiran elementos de la cola de forma ordenada.

- producer_consumer: Los mensajes muestran cómo se produce y consume sin desbordar ni vaciar el buffer.

- dining_philosophers: Los filósofos piensan y comen sin quedarse bloqueados gracias al semáforo room.
