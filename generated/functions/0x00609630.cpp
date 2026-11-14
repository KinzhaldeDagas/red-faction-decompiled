// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609630 __time64
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(optional time64Out), signed64 result EDX:EAX.
// GetSystemTimeAsFileTime into stack; subtract epoch offset116444736000000000 modulo64, UNSIGNED divide by IMMEDIATE10000000 (offset98967F+1 is numeric constant, NOT a memory read).
// Signed high/unsigned low comparison rejects quotient>0x793406FFF ->-1LL. Under ordinary FILETIME range this also rejects pre1970 subtraction underflow. If out!=NULL store both
// halves, including-1; return same pair. No own errno/doserrno update, invalid callback, allocation or timezone adjustment.
__time64_t __cdecl _time64(__time64_t *Time)
{
  __time64_t result; // rax
  struct _FILETIME SystemTimeAsFileTime; // [esp+0h] [ebp-8h] BYREF

  GetSystemTimeAsFileTime(&SystemTimeAsFileTime);
  result = (*(_QWORD *)&SystemTimeAsFileTime - 116444736000000000LL) / (unsigned __int64)(unsigned int)&byte_98967F[1];
  if ( result > 0x793406FFFLL )
    result = -1;
  if ( Time )
    *Time = result;
  return result;
}

