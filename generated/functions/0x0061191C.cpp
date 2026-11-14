// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061191C __mtinitlocks
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, initialize lock table665280:36 records
// of(pointerDWORD,kindDWORD),stride8. For kind EXACT1, assign next static24-byte CS from2021700, advance static cursor, callcrtInitCritSecAndSpinCount(pointer,4000). APIhelperFALSE
// clears only CURRENT table pointer andreturns0 immediately; earlier initialized locks remain installed for caller teardown. Non-kind1 entries untouched, including existing pointers.
// All36 processed ->1. OriginalPE kinds1 atindices[0,1,3,4,6,7,8,10,12,13,14,16,17,18], so14 static structures; lock10 is preinitialized before lazy allocation paths use it. No own
// lock, malloc, kind mutation, retry or previous-state rollback.
int _mtinitlocks()
{
  int v0; // esi
  struct _RTL_CRITICAL_SECTION *v1; // edi

  v0 = 0;
  v1 = (struct _RTL_CRITICAL_SECTION *)&unk_2021700;
  while ( 1 )
  {
    if ( dword_665284[2 * v0] == 1 )
    {
      *(&lpCriticalSection + 2 * v0) = v1++;
      if ( !__crtInitCritSecAndSpinCount(*(&lpCriticalSection + 2 * v0), 0xFA0u) )
        break;
    }
    if ( ++v0 >= 36 )
      return 1;
  }
  *(&lpCriticalSection + 2 * v0) = nullptr;
  return 0;
}

