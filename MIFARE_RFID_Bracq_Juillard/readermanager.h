#ifndef READERMANAGER_H
#define READERMANAGER_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdint>
#include "MfErrNo.h"
#include "ODALID.h"

class ReaderManager
{
private:
    BOOL bench;
    ReaderName MonLecteur;
    int status;

    uint8_t  key_ff[6]= { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t  key_a[6]= { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};
    uint8_t  key_b[6]= { 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5};



public:


    int i ;
    char s_buffer[64];
    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[12];
    uint16_t uid_len = 12;
    uint8_t sect_count = 0;
    uint8_t key_index;
    uint8_t data[240];



    ReaderManager();
    int PriseContact();
    void Done();
    void Close();
    void Tag_halt();
    int card_read(BYTE sect_count);


    WINBOOL getBench() const;
    void setBench(const WINBOOL &value);
    ReaderName getMonLecteur() const;
    void setMonLecteur(const ReaderName &value);
    int getStatus() const;
    void setStatus(int value);
};

#endif // READERMANAGER_H

