// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C229 __strlwr_s_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): U=stackLocaleUpdate(inputLocale); on every normal
// return AFTERconstruction, clearPTD+112bit2 ONLYif U.cleanupBYTE12nonzero. No own unwind-finally pinrelease. Cdecl(buffer,unsignedcapacity,locale),errno-stylehelperresult.
// ConstructUfirst,callstrlwr_s_l_stat(buffer,capacity,&U),saveEAXthroughnormalpinrelease,returnit. Noownstring/capacityvalidation,allocationorcaseconversion; noSEH cleanup.
errno_t __cdecl _strlwr_s_l(char *String, size_t Size, _locale_t Locale)
{
  errno_t result; // eax
  _BYTE v4[8]; // [esp+0h] [ebp-10h] BYREF
  int v5; // [esp+8h] [ebp-8h]
  char v6; // [esp+Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v4, (struct localeinfo_struct *)Locale);
  result = _strlwr_s_l_stat(String, Size, (struct localeinfo_struct *)v4);
  if ( v6 )
    *(_DWORD *)(v5 + 112) &= ~2u;
  return result;
}

