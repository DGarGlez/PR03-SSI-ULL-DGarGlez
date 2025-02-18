# Documentación del Proyecto

## Descripción
Este proyecto implementa el algoritmo de cifrado ChaCha20 en C++. El archivo principal `main.cc` contiene la implementación de las funciones necesarias para realizar el cifrado y la generación de estados aleatorios.

## Archivos
- `main.cc`: Contiene la implementación del algoritmo ChaCha20 y funciones auxiliares.

## Funciones

### `rotl`
```cpp
inline uint32_t rotl(uint32_t value, int shift);
```
Rota un entero de 32 bits a la izquierda.

### `quarterRound`
```cpp
void quarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d);
```
Realiza una operación básica del ChaCha20 (Quarter Round).

### `chacha20Block`
```cpp
void chacha20Block(std::array<uint32_t, 16>& state);
```
Realiza las 20 rondas del algoritmo ChaCha20.

### `printState`
```cpp
void printState(const std::array<uint32_t, 16>& state);
```
Imprime el estado en formato hexadecimal.

### `littleEndian`
```cpp
uint32_t littleEndian(uint32_t word);
```
Convierte una palabra de 32 bits a formato little endian.

### `randomState`
```cpp
std::array<uint32_t, 16> randomState();
```
Genera un estado aleatorio con clave, nonce y contador.

## Ejecución
Para compilar y ejecutar el programa, use los siguientes comandos:
```sh
g++ -o chacha20 main.cc
./chacha20
```

## Ejemplo de Salida
```
Estado inicial:
61707865 3320646e 79622d32 6b206574 
03020100 07060504 0b0a0908 0f0e0d0c 
13121110 17161514 1b1a1918 1f1e1d1c 
00000001 09000000 4a000000 00000000 

Estado de salida del generador:
e4e7f110 15593bd1 1fdd0f50 c47120a3 
c7f4d1c7 0368c033 9aaa2204 4e6cd4c3 
466482d2 09aa9f07 05d7c214 a2028bd9 
d19c12b5 b94e16de e883d0cb 4e3c50a2
```

## Referencias
- [RFC 8439: ChaCha20 and Poly1305 for IETF Protocols](https://datatracker.ietf.org/doc/html/rfc8439)
- [PracticaChaCha20.pdf](./PracticaChaCha20.pdf)