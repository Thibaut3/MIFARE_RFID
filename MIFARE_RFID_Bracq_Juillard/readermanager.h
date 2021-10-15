#ifndef READERMANAGER_H
#define READERMANAGER_H

#include <cstdint>
#include "MfErrNo.h"
#include "ODALID.h"

class ReaderManager
{
public:
    ReaderManager();
    void PriseContact();
    uint8_t key_ff[6]= { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t key_a[6]= { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};
    uint8_t key_b[6]= { 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5};
};

#endif // READERMANAGER_H

