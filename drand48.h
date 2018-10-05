/*
*返回0-1的随机数
*/
#ifndef _DRAND48_H_
#define MNWZ 0x100000000
#define ANWZ 0x5DEECE66D
#define CNWZ 0xB16
#define INFINITY 0xFFFFFFFFF
static unsigned long long seed = 1;
inline double drand48(void)
{
    seed = (ANWZ * seed + CNWZ) & 0xFFFFFFFFFFFFLL;
    unsigned int x = seed >> 16;
    return ((double)x / (double)MNWZ);
}


inline void srand48(unsigned int i)
{
    seed = (((long long int)i) << 16) | rand();
}


#define _DRAND48_H_
#endif
