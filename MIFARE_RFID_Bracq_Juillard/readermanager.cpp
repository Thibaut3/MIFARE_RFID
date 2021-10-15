#include "readermanager.h"
#include <cstdint>

int ReaderManager::getStatus() const
{
    return status;
}

void ReaderManager::setStatus(int value)
{
    status = value;
}

ReaderManager::ReaderManager()
 :  bench(TRUE),status(MI_OK)
{

    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;

    memset(data, 0x00, 240);
}

int ReaderManager::PriseContact()
{
    status = OpenCOM(&MonLecteur);
    if (status != MI_OK){
        printf("Reader not found\n");
        Done();

    }
    else{
        switch(MonLecteur.Type)
        {
            case ReaderTCP:
                sprintf(s_buffer, "IP : %s", MonLecteur.IPReader);
            break;
            case ReaderCDC:
                sprintf(s_buffer, "COM%d", MonLecteur.device);
            break;

        }
        printf("Reader found on %s\n", s_buffer);

    }

    status = Version(&MonLecteur);
    if (status == MI_OK){
        printf("Reader firwmare is %s\n", MonLecteur.version);
        printf("Reader serial is %02X%02X%02X%02X\n", MonLecteur.serial[0], MonLecteur.serial[1], MonLecteur.serial[2], MonLecteur.serial[3]);
        printf("Reader stack is %s\n", MonLecteur.stack);
    }

    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);
    if (status != MI_OK){
        printf("LED [FAILED]\n");
        Close();
    }

    key_index = 0;
    status = Mf_Classic_LoadKey(&MonLecteur, Auth_KeyA, key_ff, key_index);
    if (status != MI_OK){
        printf("Load Key [FAILED]\n");
        Close();
    }

    status = Mf_Classic_LoadKey(&MonLecteur, Auth_KeyB, key_ff, key_index);
    if (status != MI_OK){
        printf("Load Key [FAILED]\n");
        Close();
    }

    // RF field ON
    RF_Power_Control(&MonLecteur, TRUE, 0);

    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    if (status != MI_OK){
        printf("No available tag in RF field\n");
        Close();
    }

    printf("Tag found: UID=");
    for (i = 0; i < uid_len; i++)
        printf("%02X", uid[i]);
    printf(" ATQ=%02X%02X SAK=%02X\n", atq[1], atq[0], sak[0]);


    if ((atq[1] != 0x00) || ((atq[0] != 0x02) && (atq[0] != 0x04) && (atq[0] != 0x18))){
        printf("This is not a Mifare classic tag\n");
        Tag_halt();
    }

    if ((sak[0] & 0x1F) == 0x08){
        // Mifare classic 1k : 16 sectors, 3+1 blocks in each sector
        printf("Tag appears to be a Mifare classic 1k\n");
        sect_count = 16;
    } else if ((sak[0] & 0x1F) == 0x18){
        // Mifare classic 4k : 40 sectors, 3+1 blocks in 32-first sectors, 15+1 blocks in the 8-last sectors
        printf("Tag appears to be a Mifare classic 4k\n");
        sect_count = 40;
    }


    //sect_count = 16;
    status = card_read(sect_count);

    Tag_halt();
}

void ReaderManager::Done()
{
    // Display last error
    if (status == MI_OK)
    {
      printf("Done\n");
    } else
    {
      printf("%s (%d)\n", GetErrorMessage(status), status);
    }
}

void ReaderManager::Close()
{
    // Close the reader

      RF_Power_Control(&MonLecteur, FALSE, 0);


      CloseCOM(&MonLecteur);
}

void ReaderManager::Tag_halt()
{
    // Halt the tag
    status = ISO14443_3_A_Halt(&MonLecteur);
    if (status != MI_OK){
        printf("Failed to halt the tag\n");
    }
    Close();
}

int ReaderManager::card_read(BYTE sect_count)
{

    clock_t t0, t1;
    uint8_t bloc_count, bloc, sect;
    uint8_t offset;


    if (bench){
        printf("Reading %d sectors...\n", sect_count);
        t0 = clock();
    }
    bloc = 0;
    for (sect = 0; sect < sect_count; sect++){
        if (!bench)
        printf("Reading sector %02d : ", sect);

        status = Mf_Classic_Read_Sector(&MonLecteur, TRUE, sect, data, Auth_KeyA, 0);

        if (status != MI_OK){
            if (bench)
                printf("Read sector %02d ", sect);
            printf("[Failed]\n");
            printf("  %s (%d)\n", GetErrorMessage(status), status);
            status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
            if (status != MI_OK){
                printf("No available tag in RF field\n");
                //goto close;
            }
        }
        else{
            if (!bench){
                printf("[OK]\n");
                // Display sector's data
                if (sect < 32)
                    bloc_count = 3;
                else
                    bloc_count = 15;
                for (bloc = 0; bloc < bloc_count; bloc++){
                    printf("%02d : ", bloc);
                    // Each blocks is 16-bytes wide
                    for (offset = 0; offset < 16; offset++){
                        printf("%02X ", data[16 * bloc + offset]);
                    }
                    for (offset = 0; offset < 16; offset++){
                        if (data[16 * bloc + offset] >= ' '){
                            printf("%c", data[16 * bloc + offset]);
                        } else
                            printf(".");

                    }
                    printf("\n");
                }
            }
        }
    }

    if (bench){
        t1 = clock();
        printf("Time elapsed: %ldms\n", (t1 - t0) / (CLOCKS_PER_SEC/1000));
    }
    return MI_OK;
}


ReaderName ReaderManager::getMonLecteur() const
{
    return MonLecteur;
}


void ReaderManager::setMonLecteur(const ReaderName &value)
{
    MonLecteur = value;
}

WINBOOL ReaderManager::getBench() const
{
    return bench;
}

void ReaderManager::setBench(const WINBOOL &value)
{
    bench = value;
}
