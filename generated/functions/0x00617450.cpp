// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617450 __FindPESection
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(imageBase,unsigned RVA),returns matching
// sectionHEADERpointer orNULL. No ValidateImageBase call inthisbody. NT=base+DWORD[base+0x3C]; count=WORD[NT+6],firstsection=NT+24+WORD[NT+20]. Forcount entriesstride40, first with
// unsignedRVA>=section.VirtualAddress(+12) ANDRVA<wrapped(VirtualAddress+VirtualSize(+8)) wins. Uses VirtualSize, NOT SizeOfRawData, and no max(raw,virtual) expansion. Count0/miss
// ->NULL. No range, malformed-end-overflow, pointer or header-signature checks ofitsown; neither maps RVA tofileoffset norreads targetRVA contents.
int __cdecl _FindPESection(int a1, unsigned int a2)
{
  int v2; // ecx
  unsigned int v3; // esi
  unsigned int v4; // edx
  int result; // eax
  unsigned int v6; // ecx

  v2 = a1 + *(_DWORD *)(a1 + 60);
  v3 = *(unsigned __int16 *)(v2 + 6);
  v4 = 0;
  result = *(unsigned __int16 *)(v2 + 20) + v2 + 24;
  if ( !*(_WORD *)(v2 + 6) )
    return 0;
  while ( 1 )
  {
    v6 = *(_DWORD *)(result + 12);
    if ( a2 >= v6 && a2 < v6 + *(_DWORD *)(result + 8) )
      break;
    ++v4;
    result += 40;
    if ( v4 >= v3 )
      return 0;
  }
  return result;
}

