// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613D76 __isleadbyte_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw int C,optional locale). Construct
// LocaleUpdate; ZERO-EXTEND only low BYTE(C), index WORD[*(locinfo+0xC8)+2*byte] and return value&0x8000 (0 or32768), not Boolean. No mbMax gate and no own errno/invalid handler.
// Negative and >255 inputs are reduced to byte before lookup, distinct from other classifier wrappers. All own normal returns after locale construction clear threadData+0x70 mask0x2
// only if local update-object byte+12 is nonzero; nested supplied-locale objects do not acquire another pin. There is no SEH/finally cleanup in this body if a helper throws.
int __cdecl _isleadbyte_l(int C, _locale_t Locale)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-10h] BYREF
  int v4; // [esp+8h] [ebp-8h]
  char v5; // [esp+Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v3, (struct localeinfo_struct *)Locale);
  result = *(_WORD *)(*(_DWORD *)(v3 + 200) + 2 * (unsigned __int8)C) & 0x8000;
  if ( v5 )
    *(_DWORD *)(v4 + 112) &= ~2u;
  return result;
}

