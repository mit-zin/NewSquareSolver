#ifndef COLORTEXT_H
#define COLORTEXT_H

#define PRINTF_USUAL(...)     printf("\033[0m" __VA_ARGS__)
#define PRINTF_GREEN(...)     printf("\033[0;32m" __VA_ARGS__)
#define PRINTF_RED(...)       printf("\033[0;31m" __VA_ARGS__)
#define PRINTF_ORAN_FORE(...) printf("\033[0;38;5;208m" __VA_ARGS__)
#define PRINTF_ITALICS(...)   printf("\033[0;3m" __VA_ARGS__)
#define PRINTF_RED_ITAL(...)  printf("\033[0;3;31m" __VA_ARGS__)
#define PRINTF_ORANGE(...)    printf("\033[0;38;5;208m" __VA_ARGS__)

#endif
