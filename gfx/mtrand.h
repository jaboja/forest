#pragma once

#define MT_RAND_MAX 0xffffffffUL

void mt_srand (unsigned long s);
/* generates a random number on the interval [0,0xffffffff] */
unsigned long mt_rand (void);


#ifndef MT_RAND_NO_INLINES

inline void mt_seed(void)
{
  mt_srand (5489UL);  /* Default seed */
}

/* generates a random number on the interval [0,1]. */
inline float
mt_rand_1 (void)
{
  return ((float) mt_rand () / (float) MT_RAND_MAX);
}

/* generates a random number on the interval [0,1). */
inline float
mt_rand_lt1 (void)
{
  /* MT_RAND_MAX must be a float before adding one to it! */
  return ((float) mt_rand () / ((float) MT_RAND_MAX + 1.0f));
}

#endif
