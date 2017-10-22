/*
 * Barnacle.h
 *
 *  Created on: Oct 18, 2017
 *      Author: stefanth
 */

#ifndef BARNACLETA_H_
#define BARNACLETA_H_

#include "RIoT.h"
#include "RiotCrypt.h"
#include "RiotDerEnc.h"
#include "RiotX509Bldr.h"

#define NUMELEM(a) (sizeof(a) / sizeof(*a))

#define BARNACLEMAGIC               (0x6d6f6854)
#define BARNACLEVERSION             (0x00010000)
#define BARNACLETIMESTAMP           (0x59e7bd55)
#define AGENTHDRSIZE                (0x800)

typedef struct
{
    struct
    {
        struct
        {
            uint32_t magic;
            uint32_t version;
        } hdr;
        struct
        {
            uint32_t offset;
            uint32_t size;
            uint32_t version;
            uint32_t issued;
            char name[16];
            uint8_t digest[SHA256_DIGEST_LENGTH];
        } agent;
    } sign;
    struct
    {
        uint8_t r[SHA256_DIGEST_LENGTH];
        uint8_t s[SHA256_DIGEST_LENGTH];
    } signature;
} BARNACLE_AGENT_HDR, *PBARNACLE_AGENT_HDR;

typedef struct
{
    uint16_t start;
    uint16_t size;
} BARNACLE_CERT_INDEX, *PBARNACLE_CERT_INDEX;

typedef struct
{
    uint32_t magic;
    BARNACLE_CERT_INDEX certTable[7];
    uint8_t certBag[0x1000 - (sizeof(uint32_t) + sizeof(BARNACLE_CERT_INDEX) * 7)];
} BARNACLE_CERTSTORE, *PBARNACLE_CERTSTORE;

typedef struct
{
    uint32_t magic;
    RIOT_ECC_PUBLIC pubKey;
    RIOT_ECC_PRIVATE privKey;
    uint8_t unused[0x800 - sizeof(uint32_t) - sizeof(RIOT_ECC_PUBLIC) - sizeof(RIOT_ECC_PRIVATE)];
} BARNACLE_IDENTITY_PRIVATE, *PBARNACLE_IDENTITY_PRIVATE;

extern BARNACLE_IDENTITY_PRIVATE CompoundId;
extern BARNACLE_CERTSTORE CertStore;
extern const BARNACLE_AGENT_HDR AgentHdr;
extern const uint8_t* AgentCode;

bool BarnacleFlashPages(void* dest, void* src, uint32_t size);
void BarnacleGetRandom(void* dest, uint32_t size);
bool BarnacleNullCheck(void* dataPtr, uint32_t dataSize);
char* BarnacleCertChain();

#endif /* BARNACLETA_H_ */