// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006162C5 ___crtLCMapStringA
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl
// NINEraw32bitstackslots(localePtr,LCID,mapFlags,source,sourceCount,destination,destCapacity,codepage,finalFlag),intEAX forwarded.
// Stack_LocaleUpdate16bytesconstructedwithinputlocale;ECX=&updateandEIGHTremainingrawstackslotsforwardedunchangedto__crtLCMapStringA_stat615F20.
// Aftercalleereturn,cleanupflagupdate+12nonzero ->clearPTD(update+8)+112bit2;otherwiseleavepin. Noownvalidation,conversion,allocation,capacitycheckorerrortranslation;
// mapping/sizingdelegated. NoEHregistration/exception-finallypinrelease,sothrowdoesnotexecuteownnormalcleanup.
// Signature refined below from the native stat helper.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Signature refinement:
// Cdecl(localeinfo*,LCID,flags,constchar*source,SIGNEDbyteCount,char*destination,SIGNEDbyteCapacity,UINTCP,intfinalFlag). All9stackDWORDs/forwardingunchanged;
// sourceCount/destCapacity are integer lengths and output ismultibyteBYTEstorage,verifiedagainst stathelper615F20andWideCharToMultiByte/LCMapStringAbranches.
// Earlierpointer-likecount/wide-outputlabelsreplaced; normalpincleanupunchanged.
int __cdecl __crtLCMapStringA(
        struct localeinfo_struct *a1,
        LCID Locale,
        DWORD dwMapFlags,
        const char *lpMultiByteStr,
        int cbMultiByte,
        char *lpDestStr,
        int cchDest,
        UINT CodePage,
        int a9)
{
  int result; // eax
  _BYTE v10[8]; // [esp+0h] [ebp-10h] BYREF
  int v11; // [esp+8h] [ebp-8h]
  char v12; // [esp+Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v10, a1);
  result = __crtLCMapStringA_stat(
             (struct localeinfo_struct *)v10,
             Locale,
             dwMapFlags,
             lpMultiByteStr,
             cbMultiByte,
             lpDestStr,
             cchDest,
             CodePage,
             a9);
  if ( v12 )
    *(_DWORD *)(v11 + 112) &= ~2u;
  return result;
}

