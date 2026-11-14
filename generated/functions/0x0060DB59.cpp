// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DB59 __cfltcvt_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(binary64Pointer,output,unsigned capacity,int
// formatCode,int precision,int uppercase,locale), pure dispatcher; capacity/precision types corrected. EXACT lowercase e OR uppercase E -> cftoe_l; EXACT lowercase f ONLY -> cftof_l
// (uppercase flag not passed); lowercase a OR uppercase A -> cftoa_l. EVERY OTHER full32-bit format value, including uppercase F and g/G/unknown values, -> cftog_l. uppercase
// parameter forwarded independently, not derived from format letter. Preserve selected helper status; cdecl reclaim20 or24 forwarded bytes. No own validation, locale snapshot,
// formatting, allocation, special-case handling or error mapping.
int __cdecl _cfltcvt_l(_DWORD *a1, char *a2, unsigned int a3, int a4, int Size, int a6, struct localeinfo_struct *a7)
{
  switch ( a4 )
  {
    case 'e':
    case 'E':
      return _cftoe_l((double *)a1, a2, a3, Size, a6, a7);
    case 'f':
      return _cftof_l(a1, a2, a3, Size, a7);
    case 'a':
    case 'A':
      return _cftoa_l((double *)a1, a2, a3, Size, a6, a7);
  }
  return _cftog_l(a1, a2, a3, Size, a6, a7);
}

