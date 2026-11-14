// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B058 __atof_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(const text*,locale), returns binary64 in x87
// ST0. Construct LocaleUpdate before text validation. NULL text -> errno22, invalid_parameter5zeros; if handler returns, normal locale cleanup then FLDZ(+0). NonNULL skip
// locale-classified whitespace: unsigned inputBYTE, mask8; if locinfo+172<=1 use WORD ctype table locinfo+200, else isctype_l(byte,8,&localLocaleInfo). No own bounds/terminator
// special case while classifier says whitespace. Call strlen(remainder), pass resulting raw length to fltin2(local24byteRecord,remainder,length,0,0,&LocaleUpdate); verified fltin2
// NEVER READS that length, so it is not a parser bound. Load raw binary64 at returned record+16 with FLD QWORD, IGNORE record status and consumed count. On each normal exit clear PTD
// DWORD+112 mask2 iff LocaleUpdate cleanup flag set; no own ERANGE mapping, endptr/full-consumption validation, allocation, try/finally, cookie or restoration if helper throws. FP
// effects of FLD result and parser/converter behavior delegated.
double __cdecl _atof_l(const char *String, _locale_t Locale)
{
  char *v2; // esi
  double result; // st7
  size_t v5; // eax
  _DWORD v6[6]; // [esp+8h] [ebp-28h] BYREF
  __crt_locale_pointers v7; // [esp+20h] [ebp-10h] BYREF
  int v8; // [esp+28h] [ebp-8h]
  char v9; // [esp+2Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v7, (struct localeinfo_struct *)Locale);
  v2 = (char *)String;
  if ( String )
  {
    while ( *((int *)v7.locinfo + 43) <= 1
          ? *(_WORD *)(*((_DWORD *)v7.locinfo + 50) + 2 * (unsigned __int8)*v2) & 8
          : _isctype_l((unsigned __int8)*v2, 8, &v7) )
      ++v2;
    v5 = strlen(v2);
    result = *((double *)_fltin2(v6, v2, v5, 0, 0, (_LocaleUpdate *)&v7) + 2);
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
    return 0.0;
  }
  return result;
}

