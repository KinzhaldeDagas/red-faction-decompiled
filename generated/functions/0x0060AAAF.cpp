// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060AAAF _asctime
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(tmPtr), borrowed char*/NULL. Start with global
// fallback26byte buffer2021384. getptd_noexit NULL ->usefallback; existingPTD+60 char* reused. If slotNULL calloc_crt(26,1), publish slot immediately; allocationNULL also uses
// SAMEglobalfallback rather than failing directly. Call asctime_s(chosen,26,tm);status0 returnschosen,nonzeroNULL. No own tm validation, synchronization of shared fallback or
// caller-owned allocation. PTD buffer reused nextcall; allocator/PTD errno effects can survive successful formatting.
char *__cdecl asctime(const struct tm *Tm)
{
  char *v1; // edi
  DWORD *v2; // eax
  DWORD *v3; // esi
  int v4; // eax

  v1 = unk_2021384;
  v2 = _getptd_noexit();
  v3 = v2;
  if ( v2 )
  {
    if ( v2[15] || (v4 = _calloc_crt(0x1Au, 1), (v3[15] = v4) != 0) )
      v1 = (char *)v3[15];
  }
  return asctime_s(v1, 0x1Au, Tm) == 0 ? v1 : nullptr;
}

