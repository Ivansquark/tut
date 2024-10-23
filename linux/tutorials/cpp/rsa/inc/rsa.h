#ifndef RSA_H
#define RSA_H

#include <stdint.h>

void mpi_powm65537(uint16_t* m, const uint16_t* n);
// MPI single-precision number size, in 16-bit words
#define MPI_NUMBER_SIZE 128


#endif // RSA_H
