#if !defined(_SMOKU_DEBUG_H)
#define _SMOKU_DEBUG_H

#ifndef NDEBUG

#define dbgputs(S) puts(S)
#define dbgprintf(F...) printf(F)

#else

#define dbgputs(S)
#define dbgprintf(F...)

#endif

#endif // _SMOKU_DEBUG_H
