#ifndef _NPY_NPY_CONFIG_H_
#define _NPY_NPY_CONFIG_H_

#include "config.h"
#include "numpy/numpyconfig.h"
#include "numpy/npy_cpu.h"

/*
 * largest alignment the copy loops might require
 * required as string, void and complex types might get copied using larger
 * instructions than required to operate on them. E.g. complex float is copied
 * in 8 byte moves but arithmetic on them only loads in 4 byte moves.
 * the sparc platform may need that alignment for long doubles.
 * amd64 is not harmed much by the bloat as the system provides 16 byte
 * alignment by default.
 */
#if (defined NPY_CPU_X86 || defined _WIN32)
#define NPY_MAX_COPY_ALIGNMENT 8
#else
#define NPY_MAX_COPY_ALIGNMENT 16
#endif

/* blacklist */

/* Disable broken Sun Workshop Pro math functions */
#ifdef __SUNPRO_C

#undef HAVE_ATAN2
#undef HAVE_ATAN2F
#undef HAVE_ATAN2L

#endif

/* Disable broken MS math functions */
#if (defined(_MSC_VER) && (_MSC_VER < 1900)) || defined(__MINGW32_VERSION)

#undef HAVE_ATAN2
#undef HAVE_ATAN2F
#undef HAVE_ATAN2L

#undef HAVE_HYPOT
#undef HAVE_HYPOTF
#undef HAVE_HYPOTL

#endif

#if defined(_MSC_VER) && (_MSC_VER == 1900)

#undef HAVE_CASIN
#undef HAVE_CASINF
#undef HAVE_CASINL
#undef HAVE_CASINH
#undef HAVE_CASINHF
#undef HAVE_CASINHL
#undef HAVE_CATAN
#undef HAVE_CATANF
#undef HAVE_CATANL
#undef HAVE_CATANH
#undef HAVE_CATANHF
#undef HAVE_CATANHL

#endif


/* Intel C for Windows uses POW for 64 bits longdouble*/
#if defined(_MSC_VER) && defined(__INTEL_COMPILER)
#if defined(HAVE_POWL) && (NPY_SIZEOF_LONGDOUBLE == 8)
#undef HAVE_POWL
#endif
#endif /* defined(_MSC_VER) && defined(__INTEL_COMPILER) */


/* Disable broken gnu trig functions on linux */
#if defined(__linux__) && defined(__GNUC__)

#if defined(HAVE_FEATURES_H)
#include <features.h>
#define TRIG_OK __GLIBC_PREREQ(2, 16)
#else
#define TRIG_OK 0
#endif

#if !TRIG_OK
#undef HAVE_CASIN
#undef HAVE_CASINF
#undef HAVE_CASINL
#undef HAVE_CASINH
#undef HAVE_CASINHF
#undef HAVE_CASINHL
#undef HAVE_CATAN
#undef HAVE_CATANF
#undef HAVE_CATANL
#undef HAVE_CATANH
#undef HAVE_CATANHF
#undef HAVE_CATANHL
#undef HAVE_CACOS
#undef HAVE_CACOSF
#undef HAVE_CACOSL
#undef HAVE_CACOSH
#undef HAVE_CACOSHF
#undef HAVE_CACOSHL
#endif
#undef TRIG_OK

#endif /* defined(__linux__) && defined(__GNUC__) */

#endif
