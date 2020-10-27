# IoT Context Application: NOAA related

The purpose of this application is to explore and demonstrate the ZeroMQ library.

## Dependencies

LibZMQ, CPPZMQ

## Compiling

### Wavesensor

> g++ -Wall src/wavesensor.cpp -lzmq -o bin/wavesensor

### Watcher
> g++ -Wall src/watcher.cpp -lzmq -o bin/watcher

### Broker

> g++ -Wall src/broker.cpp -lzmq -o bin/broker

### Execution

There's no mandatory order of execution.

The suggested one is:

> ./bin/broker
> ./bin/wavesensor <id>
> ./bin/watcher <id>

## Authors
Israel Efraim de Oliveira
José Carlos Zancanaro
Josué Gabriel dos Santos