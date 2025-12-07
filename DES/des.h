#ifndef __DES_H__
#define __DES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef uint64_t DES_STATE_t;


//구현함수
void DES_enc(DES_STATE_t * C, DES_STATE_t P);
void DES_dec(DES_STATE_t * P, DES_STATE_t C);


///////////TEST Vectors
typedef struct {
	DES_STATE_t P;
	DES_STATE_t C;
}DES_TV_t;



static DES_TV_t des_tvs[] = {
	{
		0x0123456789abcdefULL, //P
		0x33E569AA96EA221EULL, //C
	},//0
	{
		0x0000000000000000ULL, //P
		0x1BA3572A94187AF4ULL, //C
	},//1
	{
		0xFFFFFFFFFFFFFFFFULL, //P
		0x904DBC3FE76AE48FULL, //C
	},//2
	{
		0xFEDCBA9876543210ULL, //P
		0xB64E443FE32587E0ULL, //C
	},//3

	{
		0xABCDEFABCDEFABCDULL, //P
		0xD80D5026C28FA7B8ULL, //C
	},//4
	{
		0x1111111111111111ULL, //P
		0xFA26A23299D26413ULL, //C
	},//5
	{
		0x2222222222222222ULL, //P
		0x688C861EF7FBB8E1ULL, //C
	},//6
	{
		0x3333333333333333ULL, //P
		0x198AA48862448B86ULL, //C
	},//7
};

#define NUM_DES_TVS (sizeof(des_tvs)/sizeof(DES_TV_t))

#ifdef __cplusplus
}
#endif /*extern "C"*/
#endif /*__DES_H__*/