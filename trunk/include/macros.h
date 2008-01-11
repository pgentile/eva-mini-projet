#ifndef MACROS_H
#define MACROS_H

#define RANDOM_NUMBER(inf,sup) ((float)inf + (int) ((float)sup * (rand() / (RAND_MAX + 1.0f))))
#define EPSILON (0.9)

#ifndef MIN
#define MIN(a,b) ((a<=b?a:b))
#endif

#endif
