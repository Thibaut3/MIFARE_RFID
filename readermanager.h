#ifndef READERMANAGER_H
#define READERMANAGER_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdint>
#include "MfErrNo.h"
#include "ODALID.h"
#include <QDebug>
#include <QString>
#include <iostream>

class ReaderManager
{
private:
    BOOL bench;
    ReaderName MonLecteur;
    int status;

    uint8_t  key_ff[6]= { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    uint8_t  key_a2[6]= { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}; //LECTURE ID
    uint8_t  key_b2[6]= { 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5}; //ECRITURE ID
    uint8_t  key_a3[6]= { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5}; //LECTURE Compteur
    uint8_t  key_b3[6]= { 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5}; //ECRITURE Compteur

    QString prenom;
    QString nom;
    int unite;

    char newPrenom[16];

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

    void LectureBlock2();
    void LectureBlock3();
    void ReadID();

    QString getPrenom();
    QString getNom();
    int getUnite();

    void setNewPrenom(char newPrenom[16]);

    WINBOOL getBench() const;
    void setBench(const WINBOOL &value);
    ReaderName getMonLecteur() const;
    void setMonLecteur(const ReaderName &value);
    int getStatus() const;
    void setStatus(int value);
};

#endif // READERMANAGER_H

