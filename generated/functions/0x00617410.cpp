// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617410 __ValidateImageBase
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(imageBase),canonicalBOOL.
// DereferenceWORD[base]==0x5A4D; ifmatch use wrappedbase+DWORD[base+0x3C],requireDWORD signature0x4550 andWORDoptionalheaderMagic atNT+24==0x10B. Return1 onlyallthree,else0. No own
// exceptionhandler, buffer/offset/sectioncount/optionalheadersize/PE32+ validation; malformed pointer mayfault ratherthanFALSE. This is header-signature checking, not a
// memory-protection query.
BOOL __cdecl _ValidateImageBase(int a1)
{
  int v2; // eax

  if ( *(_WORD *)a1 == 23117 && (v2 = a1 + *(_DWORD *)(a1 + 60), *(_DWORD *)v2 == 17744) )
    return *(_WORD *)(v2 + 24) == 267;
  else
    return 0;
}

