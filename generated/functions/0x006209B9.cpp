// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006209B9 __strnicoll_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. U=stackLocaleUpdate(inputLocale); on every normal return AFTERconstruction, clearPTD+112bit2 ONLYif
// U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. Cdecl(left,right,unsignedBYTEcount,locale),intcollation. ConstructUfirst,count0returns0beforepointer/rangechecks.
// NonzeroNULLinputs ORcount>INT_MAX invalid22/INT_MAX. Root=U.firstpointer;rootDWORD+16isLC_COLLATE LCID (notMBLCID). LCID0 delegatesstrnicmp_l(left,right,count,&U).
// NonzeroLCIDcrtCompareStringA(&U,LCID,1001h,left,count,right,count,rootDWORD+8collateCP),nonzero->result-2;zero->errno22/INT_MAXWITHOUTinvalidcallback.
// UnlikeMBmbsnbicoll_l,COMPAREfailureexplicitlysetserrno22. Noownallocation,fullencodingvalidationorrollback.
int __cdecl _strnicoll_l(const char *String1, const char *String2, size_t MaxCount, _locale_t Locale)
{
  int result; // eax
  LCID v5; // ecx
  int v6; // eax
  __crt_locale_pointers v7; // [esp+4h] [ebp-10h] BYREF
  int v8; // [esp+Ch] [ebp-8h]
  char v9; // [esp+10h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v7, (struct localeinfo_struct *)Locale);
  if ( !MaxCount )
  {
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
    return 0;
  }
  if ( String1 && String2 )
  {
    if ( MaxCount > 0x7FFFFFFF )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
LABEL_16:
      if ( v9 )
        *(_DWORD *)(v8 + 112) &= ~2u;
      return 0x7FFFFFFF;
    }
    v5 = *((_DWORD *)v7.locinfo + 4);
    if ( v5 )
    {
      v6 = __crtCompareStringA(
             (struct localeinfo_struct *)&v7,
             v5,
             0x1001u,
             String1,
             MaxCount,
             String2,
             MaxCount,
             *((_DWORD *)v7.locinfo + 2));
      if ( !v6 )
      {
        *_errno() = 22;
        goto LABEL_16;
      }
      result = v6 - 2;
    }
    else
    {
      result = _strnicmp_l(String1, String2, MaxCount, &v7);
    }
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  return result;
}

