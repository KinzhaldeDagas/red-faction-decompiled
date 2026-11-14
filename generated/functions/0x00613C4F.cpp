// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613C4F __stricmp_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid22 means errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated status/cleanup follows only if the handler returns. Cdecl(first string,second string,optional locale). Construct LocaleUpdate BEFORE
// either pointer validation. NULL first/second ->Invalid22/INT_MAX. Valid pointers: locinfo+0x14 LCID0 calls ascii_stricmp613C16, returning exact unsigned folded byte difference (not
// normalized). Nonzero LCID loops: zero-extend each source byte, tolower_l(byte,&localLocale) for BOTH strings, advance each cursor, continue only if first folded value nonzero and
// both equal; return firstFolded-secondFolded. This compares individual encoded bytes, not a decoded multibyte/Unicode stream. No count bound, collation weights, writes or
// allocation. All own normal returns after locale construction clear threadData+0x70 mask0x2 only if local update-object byte+12 is nonzero; nested supplied-locale objects do not
// acquire another pin. There is no SEH/finally cleanup in this body if a helper throws.
int __cdecl _stricmp_l(const char *String1, const char *String2, _locale_t Locale)
{
  int result; // eax
  const char *v4; // edi
  int v5; // eax
  int v6; // esi
  int v7; // eax
  __crt_locale_pointers Localea; // [esp+4h] [ebp-10h] BYREF
  int v9; // [esp+Ch] [ebp-8h]
  char v10; // [esp+10h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Localea, (struct localeinfo_struct *)Locale);
  if ( String1 )
  {
    v4 = String2;
    if ( String2 )
    {
      if ( *((_DWORD *)Localea.locinfo + 5) )
      {
        do
        {
          v5 = _tolower_l(*(unsigned __int8 *)String1++, &Localea);
          v6 = v5;
          v7 = _tolower_l(*(unsigned __int8 *)v4++, &Localea);
        }
        while ( v6 && v6 == v7 );
        result = v6 - v7;
      }
      else
      {
        result = __ascii_stricmp((unsigned __int8 *)String1, (unsigned __int8 *)String2);
      }
      if ( v10 )
        *(_DWORD *)(v9 + 112) &= ~2u;
    }
    else
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      if ( v10 )
        *(_DWORD *)(v9 + 112) &= ~2u;
      return 0x7FFFFFFF;
    }
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v10 )
      *(_DWORD *)(v9 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  return result;
}

