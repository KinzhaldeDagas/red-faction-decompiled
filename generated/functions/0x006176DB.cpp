// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006176DB _siglookup
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI: EDX=signal, one caller-popped stack
// argument RAW table pointer, EAX=matching ENTRY pointer/NULL, plain RET. Twelve-byte records {exceptionCode,signal,RAW action}; compare signal field+4, stride12, count global665CEC
// (original10). First record read BEFORE count bound, including count0. No pointer/count validation, lock, errno, action decoding or exception-code matching. Caller raise relies on
// table membership and dereferences result without NULL guard.
_DWORD *__usercall siglookup@<eax>(int a1@<edx>, _DWORD *a2)
{
  _DWORD *result; // eax

  result = a2;
  do
  {
    if ( result[1] == a1 )
      break;
    result += 3;
  }
  while ( result < &a2[3 * dword_665CEC[0]] );
  if ( result >= &a2[3 * dword_665CEC[0]] || result[1] != a1 )
    return nullptr;
  return result;
}

