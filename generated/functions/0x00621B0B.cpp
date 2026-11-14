// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621B0B __strnicmp_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid22 means errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated status/cleanup follows only if the handler returns. Cdecl(first,second,unsigned count,optional locale). Count0 returns0 BEFORE locale
// construction or pointer validation, even with NULL strings/invalid locale pointer. Nonzero count constructs LocaleUpdate; NULL pointer or unsigned count>INT_MAX
// ->Invalid22/INT_MAX. Locinfo LCID0 delegates ascii_strnicmp622080, returning normalized -1/0/+1. Nonzero LCID compares zero-extended source bytes via tolower_l(byte,&localLocale)
// for both, advances both, decrements count; stop on count0, firstFolded0 or mismatch and return EXACT firstFolded-secondFolded. Result magnitude can differ between C and
// nonzero-LCID branches. No multibyte decoding, collation, writes or source-capacity validation. All own normal returns after locale construction clear threadData+0x70 mask0x2 only
// if local update-object byte+12 is nonzero; nested supplied-locale objects do not acquire another pin. There is no SEH/finally cleanup in this body if a helper throws.
int __cdecl _strnicmp_l(const char *String1, const char *String2, size_t MaxCount, _locale_t Locale)
{
  int result; // eax
  const char *v5; // edi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  __crt_locale_pointers Localea; // [esp+Ch] [ebp-10h] BYREF
  int v10; // [esp+14h] [ebp-8h]
  char v11; // [esp+18h] [ebp-4h]

  if ( !MaxCount )
    return 0;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Localea, (struct localeinfo_struct *)Locale);
  if ( String1 && (v5 = String2) != nullptr )
  {
    if ( MaxCount <= 0x7FFFFFFF )
    {
      if ( *((_DWORD *)Localea.locinfo + 5) )
      {
        do
        {
          v6 = _tolower_l(*(unsigned __int8 *)String1++, &Localea);
          v7 = v6;
          v8 = _tolower_l(*(unsigned __int8 *)v5++, &Localea);
          --MaxCount;
        }
        while ( MaxCount && v7 && v7 == v8 );
        result = v7 - v8;
      }
      else
      {
        result = __ascii_strnicmp((unsigned __int8 *)String1, (unsigned __int8 *)String2, MaxCount);
      }
      if ( v11 )
        *(_DWORD *)(v10 + 112) &= ~2u;
    }
    else
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      if ( v11 )
        *(_DWORD *)(v10 + 112) &= ~2u;
      return 0x7FFFFFFF;
    }
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v11 )
      *(_DWORD *)(v10 + 112) &= ~2u;
    return 0x7FFFFFFF;
  }
  return result;
}

