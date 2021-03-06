/*
 * umsgpack.h
 *
 *  Created on: Jun 21, 2015
 *      Author: hasegaw
 */

#ifndef UMSGPACK_H_
#define UMSGPACK_H_

#include "stdint.h"

#ifdef __x86_64__
/* Intel EM64T (x86_64)
 *         int    short     long   float     double
 *         32bits ?         32bits 32bits    32bits
 */
#define UMSGPACK_HW_FLOAT_IEEE754COMPLIANT 1
#define UMSGPACK_HW_LITTLE_ENDIAN 1
#endif

#ifdef __i386__
/*
 * Intel x86 32bit
 *
 */
#define UMSGPACK_HW_FLOAT_IEEE754COMPLIANT 1
#define UMSGPACK_HW_LITTLE_ENDIAN 1

#endif

#if defined(__AVR__) && defined(__GNUC__)
/* AVR-GCC
 *         int    short      long   float  double
 *         16bits 16bits 32bits 32bits 32bits
 */
#define UMSGPACK_HW_FLOAT_IEEE754COMPLIANT 1
#define UMSGPACK_HW_LITTLE_ENDIAN 1
#define UMSGPACK_FUNC_INT32 1
#define UMSGPACK_INT_WIDTH_16 1

#endif

#ifdef __18CXX
/* MPLAB C18 Compiler. (8bit MCU)
 *         int    short   short_long  long   float     double
 *         16bits 16bits  24bits      24bits 32bitsMCF 32bitsMCF
 */

#define UMSGPACK_HW_BIG_ENDIAN 1
#endif

/* NXP JN514x/516x Compiler (32bit MCU)
 *
 */
#ifdef __ba__
#define UMSGPACK_HW_BIG_ENDIAN 1
#define UMSGPACK_HW_FLOAT_IEEE754COMPLIANT 1
#undef UMSGPACK_HW_NEGATIVE_INT64
#define UMSGPACK_FUNC_INT64 1
#define UMSGPACK_FUNC_INT32 1
#define UMSGPACK_INT_WIDTH_16 1
#endif

struct umsgpack_packer_buf {
    unsigned int length;
    unsigned int pos;
    unsigned char data[];
};

#define umsgpack_get_length(buf) buf->pos

int umsgpack_pack_array(struct umsgpack_packer_buf *buf, int length);
int umsgpack_pack_uint(struct umsgpack_packer_buf *buf, unsigned int val);
int umsgpack_pack_int(struct umsgpack_packer_buf *buf, int val);
#ifdef UMSGPACK_FUNC_INT32
int umsgpack_pack_uint32(struct umsgpack_packer_buf *buf, uint32_t val);
int umsgpack_pack_int32(struct umsgpack_packer_buf *buf, int32_t val);
#endif
#ifdef UMSGPACK_FUNC_INT64
int umsgpack_pack_uint64(struct umsgpack_packer_buf *buf, uint64_t val);
int umsgpack_pack_int64(struct umsgpack_packer_buf *buf, int64_t val);
#endif

int umsgpack_pack_float(struct umsgpack_packer_buf *buf, float val);
#if 0
int umsgpack_pack_double(struct umsgpack_packer_buf *buf, double val);
#endif
int umsgpack_pack_map(struct umsgpack_packer_buf *buf, int num_objects);
int umsgpack_pack_str(struct umsgpack_packer_buf *buf, char* s, int length);
int umsgpack_pack_bool(struct umsgpack_packer_buf *buf, int val);
void umsgpack_packer_init(struct umsgpack_packer_buf *buf, int size);
struct umsgpack_packer_buf *umsgpack_alloc(int size);
int umsgpack_free(struct umsgpack_packer_buf *buf);

#endif /* UMSGPACK_H_ */
