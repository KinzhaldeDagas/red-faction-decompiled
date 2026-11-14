// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00620977 ___crtCompareStringA
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): U=stackLocaleUpdate(inputLocale); on every normal
// return AFTERconstruction, clearPTD+112bit2 ONLYif U.cleanupBYTE12nonzero. No own unwind-finally pinrelease.
// Cdecl(localeinfo*,LCID,DWORDflags,constchar*left,SIGNEDleftCount,constchar*right,SIGNEDrightCount,UINTCP),rawcompareintEAX; correctedpointer-likeLCID/CP,unsignedleftcount.
// ConstructUfromfirstarg;ECX=&U,EDX=left,SIXstackargsLCID/flags/leftCount/right/rightCount/CP,callCompareStringA_stat;ADD24callerreclaimsstack,forwardEAXthroughnormalpinrelease.
// Noownconversion,validation,allocation,errortranslationorSEH/unwind-finally.
int __cdecl __crtCompareStringA(
        struct localeinfo_struct *a1,
        LCID a2,
        DWORD a3,
        const char *a4,
        int a5,
        const char *a6,
        int a7,
        UINT a8)
{
  int result; // eax
  _BYTE v9[8]; // [esp+0h] [ebp-10h] BYREF
  int v10; // [esp+8h] [ebp-8h]
  char v11; // [esp+Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v9, a1);
  result = __crtCompareStringA_stat((struct localeinfo_struct *)v9, a4, a2, a3, a5, a6, a7, a8);
  if ( v11 )
    *(_DWORD *)(v10 + 112) &= ~2u;
  return result;
}

