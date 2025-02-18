#include <cstdint>
#include <iostream>
#include <iomanip>
#include <array>

/**
 * @brief Constantes del ChaCha20
 */
const uint32_t CONSTANTS[] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574};

/**
 * @brief Rota un entero de 32 bits
 * 
 * @param value El valor a rotar
 * @param shift La cantidad de bits a rotar
 * @return uint32_t El valor rotado
 */
inline uint32_t rotl(uint32_t value, int shift) {
    return (value << shift) | (value >> (32 - shift));
}

/**
 * @brief Operación básica del ChaCha20 (QR: Quarter Round)
 * 
 * @param a Referencia al primer entero de 32 bits
 * @param b Referencia al segundo entero de 32 bits
 * @param c Referencia al tercer entero de 32 bits
 * @param d Referencia al cuarto entero de 32 bits
 */
void quarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
    a += b; d ^= a; d = rotl(d, 16);
    c += d; b ^= c; b = rotl(b, 12);
    a += b; d ^= a; d = rotl(d, 8);
    c += d; b ^= c; b = rotl(b, 7);
}

/**
 * @brief Realiza las 20 rondas del algoritmo ChaCha20
 * 
 * @param state El estado inicial del algoritmo
 */
void chacha20Block(std::array<uint32_t, 16>& state) {
    std::array<uint32_t, 16> workingState = state;

    for (int i = 0; i < 10; ++i) {
        // Column rounds
        quarterRound(workingState[0], workingState[4], workingState[8], workingState[12]);
        quarterRound(workingState[1], workingState[5], workingState[9], workingState[13]);
        quarterRound(workingState[2], workingState[6], workingState[10], workingState[14]);
        quarterRound(workingState[3], workingState[7], workingState[11], workingState[15]);

        // Diagonal rounds
        quarterRound(workingState[0], workingState[5], workingState[10], workingState[15]);
        quarterRound(workingState[1], workingState[6], workingState[11], workingState[12]);
        quarterRound(workingState[2], workingState[7], workingState[8], workingState[13]);
        quarterRound(workingState[3], workingState[4], workingState[9], workingState[14]);
    }

    for (int i = 0; i < 16; ++i) {
        state[i] += workingState[i];
    }
}

/**
 * @brief Imprime el estado en hexadecimal
 * 
 * @param state El estado a imprimir
 */
void printState(const std::array<uint32_t, 16>& state) {
    for (int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << state[i] << " ";
        if ((i + 1) % 4 == 0) std::cout << "\n";
    }
}

/**
 * @brief Convierte palabras de 32 bits en little endian
 * 
 * @param word La palabra a convertir
 * @return uint32_t La palabra convertida
 */
uint32_t littleEndian(uint32_t word){
    return ((word & 0x000000ff) << 24) | ((word & 0x0000ff00) << 8) | ((word & 0x00ff0000) >> 8) | ((word & 0xff000000) >> 24);
}

/*
 * @brief Genera una clave, nonce y contador aleatorios
 * 
 * @return std::array<uint32_t, 16> El estado generado aleatoriamente
 */
std::array<uint32_t, 16> randomState(){
    std::array<uint32_t, 16> state;
    for (int i = 0; i < 4; ++i) {
        state[i] = CONSTANTS[i];
    }
    for (int i = 4; i < 16; ++i) {
        if (i == 12) state[i] = 0x01000000; // Contador
        else
        state[i] = rand();
    }
    return state;
}


int main() {
    
    std::array<uint32_t, 16> state = {
        CONSTANTS[0], CONSTANTS[1], CONSTANTS[2], CONSTANTS[3], // Constantes
        0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f,         // Clave
        0x10111213, 0x14151617, 0x18191a1b, 0x1c1d1e1f,         // Clave
        0x01000000, 0x00000009, 0x0000004a, 0x00000000          // Contador y nonce
    };
    

    //std::array<uint32_t, 16> state = randomState();

    // Convertir a little endian sin modificar las constantes
    for (int i = 4; i < 16; ++i) {
        state[i] = littleEndian(state[i]);
    }

    std::cout << "Estado inicial:\n";
    printState(state);

    chacha20Block(state);

    std::cout << "\nEstado de salida del generador:\n";
    printState(state);

    return 0;
}
