#include "grasshopper.h"
#include <iostream>

vect_t temp; // Итерационные константы C
round_keys_t temp_keys;

int main(int argc, char **argv) {
    std::cout << "Hello" << std::endl;
    std::cout << argc << argv[0] << std::endl;

   // uint8_t phrase[16] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00,
   //                       0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88};
    uint8_t phrase[16] = {0x00, 0x00, 0x00, 0x0, 0x0, 0x0, 0x0, 0x00,
                          0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    uint8_t phraseEncript[16] = {0};
    uint8_t phraseDecript[16] = {0};
    uint8_t key[32] = {0x11, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                       0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};

    GOST_Kuz_set_key(key, &temp_keys);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 16; j++) {
            std::cout <<  (int)(temp_keys.keys[i].b[j]) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    GOST_Kuz_encrypt_block(&temp_keys, (const vect_t *)phrase, (vect_t *)phrase);
    for (int i = 0; i < 16; i++) {
        std::cout << (int)phrase[i] << "\t";
    }
    std::cout << std::endl << std::endl << std::endl;

    GOST_Kuz_decrypt_block(&temp_keys, (const vect_t *)phrase, (vect_t *)phrase);
    for (int i = 0; i < 16; i++) {
        std::cout << (int)phrase[i] << "\t";
    }
    char str[] = "112233445566778811223344556677881";
    int size = sizeof(str);
    std::cout << std::endl << "str" << " = " << str << " sizeof(str) = "<< size << std::endl;
    uint8_t tempArr[0xFFFF] = {0};
    encriptArray(&temp_keys, (uint8_t*)str, tempArr, size);
    for (int i=0; i < 17; i++) {
        std::cout << (int)tempArr[i] << " ";
    }
    std::cout <<std::endl;
    int fullDecriptedSize = ((size%16) ? (size + (16 - (size%16))) : size);
    std::cout << "fullDecriptedSize = " << fullDecriptedSize << std::endl;
    decriptArray(&temp_keys, tempArr, tempArr, fullDecriptedSize);
    for (int i=0; i < fullDecriptedSize; i++) {
        std::cout << (int)tempArr[i] << " ";
    }
    return 0;
}
