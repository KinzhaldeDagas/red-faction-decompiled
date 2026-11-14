// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E1FC ___crtGetStringTypeA
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl
// EIGHTraw32bitstackslots(localePtr,infoType,source,sourceCount,typeOutput,codepage,LCID,finalFlag),intEAX forwarded.
// Constructstack_LocaleUpdate16byteswithinputlocale;ECX=&updateandSEVENremainingrawstackslotsforwardedunchangedto__crtGetStringTypeA_stat61E042.
// Normalreturnifcleanupflagupdate+12nonzero,clearPTD(update+8)+112bit2,elsepinunchanged. Noownpointer/countvalidation,classification,allocation,errno
// translationoroutputwriteoutsidecallee. NoEHregistrationorunwindfinally;delegateexceptionbypassesnormalpinrelease.
// Signature refined below from the native stat helper.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Signature refinement:
// Cdecl(localeinfo*,DWORDinfo,constchar*source,SIGNEDbyteCount,WORD*types,UINTCP,LCID,intfinalFlag). EightstackDWORDs/forwardingunchanged;
// actualintegerbytecountandWORDoutputverifiedagainst stathelper61E042andGetStringTypeA/Wcalls. Previouspointer-likecountlabelreplaced; normalpincleanupunchanged.
int __cdecl __crtGetStringTypeA(
        struct localeinfo_struct *a1,
        DWORD dwInfoType,
        const char *lpMultiByteStr,
        int cbMultiByte,
        WORD *lpCharType,
        UINT CodePage,
        LCID Locale,
        int a8)
{
  int result; // eax
  _BYTE v9[8]; // [esp+0h] [ebp-10h] BYREF
  int v10; // [esp+8h] [ebp-8h]
  char v11; // [esp+Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v9, a1);
  result = __crtGetStringTypeA_stat(
             (struct localeinfo_struct *)v9,
             dwInfoType,
             lpMultiByteStr,
             cbMultiByte,
             lpCharType,
             CodePage,
             Locale,
             a8);
  if ( v11 )
    *(_DWORD *)(v10 + 112) &= ~2u;
  return result;
}

