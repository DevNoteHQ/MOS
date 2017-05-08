#ifndef TYPES_H
#define TYPES_H

/* Garantiert, dass ein Typ nicht gepaddet wird und somit exakt die Größe seiner Member hat */
#define PACKED __attribute__((packed))

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#endif