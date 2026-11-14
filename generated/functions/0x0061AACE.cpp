// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061AACE ___lock_fhandle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(rawfd), returns canonical1 after entering record CS or0 when THIS invocation failed initialization. No fd/range/open/blockNULL guard. Compute record,localresult1; if
// initDWORD+8==0,lockglobal10/armSEH,recheck. Still0: crtInitCritSecAndSpinCount(record+12,4000); APIhelper0 sets result0, but ALWAYS increment record+8, INCLUDING failure.
// Finallyunlockglobal10 onnormal/unwind. If localresultnonzero re-fetch record andEnterCriticalSection; otherwise skipEnter,return0. Subsequent calls seeing nonzero init field
// assumeinitialized and canEnter even after priorcreationfailure. No errno/invalid callback, allocation or rollback; outer wrappers commonly ignore this BOOL. EH4 scope65EF40
// verified, handler61AB60 restoresregisters thenunlocks10.
BOOL __cdecl __lock_fhandle(int a1)
{
  int v1; // esi
  BOOL inited; // [esp+10h] [ebp-1Ch]

  v1 = unk_2021E40[a1 >> 5] + ((a1 & 0x1F) << 6);
  inited = 1;
  if ( !*(_DWORD *)(v1 + 8) )
  {
    _lock(10);
    if ( !*(_DWORD *)(v1 + 8) )
    {
      inited = __crtInitCritSecAndSpinCount((LPCRITICAL_SECTION)(v1 + 12), 0xFA0u);
      ++*(_DWORD *)(v1 + 8);
    }
    _unlock(10);
  }
  if ( inited )
    EnterCriticalSection((LPCRITICAL_SECTION)(unk_2021E40[a1 >> 5] + ((a1 & 0x1F) << 6) + 12));
  return inited;
}

