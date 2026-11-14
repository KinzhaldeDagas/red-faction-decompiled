// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006090A6 __islower_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw int C, optional locale), lower-case
// classification; raw mask0x2. Construct stack LocaleUpdate via607051. If signed locinfo+0xAC<=1 read WORD[*(locinfo+0xC8)+2*C] directly and AND mask; otherwise call
// isctype_l(C,mask,&localLocale), preserve its result. Full32-bit C used as direct table index without byte cast or range validation, unlike isleadbyte_l. Return masked bits, not
// normalized Boolean; no own errno/invalid-handler, allocation or string access. All own normal returns after locale construction clear threadData+0x70 mask0x2 only if local
// update-object byte+12 is nonzero; nested supplied-locale objects do not acquire another pin. There is no SEH/finally cleanup in this body if a helper throws.
int __cdecl _islower_l(int C, _locale_t Locale)
{
  int result; // eax
  __crt_locale_pointers v3; // [esp+0h] [ebp-10h] BYREF
  int v4; // [esp+8h] [ebp-8h]
  char v5; // [esp+Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v3, (struct localeinfo_struct *)Locale);
  if ( *((int *)v3.locinfo + 43) <= 1 )
    result = *(_WORD *)(*((_DWORD *)v3.locinfo + 50) + 2 * C) & 2;
  else
    result = _isctype_l(C, 2, &v3);
  if ( v5 )
    *(_DWORD *)(v4 + 112) &= ~2u;
  return result;
}

