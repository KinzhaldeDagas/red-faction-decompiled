// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A87A __mbctoupper_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(unsigned packed Ch,optional locale), multibyte
// uppercase conversion. Construct LocaleUpdate; mbinfo=DWORD[localObject+4]. Ch<=255: BYTE[mbinfo+29+Ch]&0x20 controls unsigned BYTE[mbinfo+285+Ch] mapping, otherwise unchanged.
// Ch>255 uses exactly[B1(Ch),B0(Ch)], no terminator; lead flag BYTE[mbinfo+29+B1]&4 must be set. Call crtLCMapStringA(&localLocale,mbinfo+12
// LCID,0x200,source,2,destination,2,mbinfo+4 codepage,1). Status0 returns full original Ch; ANY nonzero status packs TWO output bytes without length2 verification or prior output
// initialization. Upper16 input bits ignored on mapped result. No own errno/invalid handler or string scan; single-byte and double-byte paths use different map mechanisms. All own
// normal returns after locale construction clear threadData+0x70 mask0x2 only if local update-object byte+12 is nonzero; nested supplied-locale objects do not acquire another pin.
// There is no SEH/finally cleanup in this body if a helper throws.
unsigned int __cdecl _mbctoupper_l(unsigned int Ch, _locale_t Locale)
{
  unsigned int result; // eax
  _BYTE v3[4]; // [esp+4h] [ebp-18h] BYREF
  int v4; // [esp+8h] [ebp-14h]
  int v5; // [esp+Ch] [ebp-10h]
  char v6; // [esp+10h] [ebp-Ch]
  char DestStr[4]; // [esp+14h] [ebp-8h] BYREF
  CHAR MultiByteStr[4]; // [esp+18h] [ebp-4h] BYREF

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v3, (struct localeinfo_struct *)Locale);
  if ( Ch <= 0xFF )
  {
    if ( (*(_BYTE *)(Ch + v4 + 29) & 0x20) != 0 )
      result = *(unsigned __int8 *)(Ch + v4 + 285);
    else
      result = Ch;
LABEL_11:
    if ( v6 )
      *(_DWORD *)(v5 + 112) &= ~2u;
    return result;
  }
  MultiByteStr[0] = BYTE1(Ch);
  MultiByteStr[1] = Ch;
  if ( (*(_BYTE *)(BYTE1(Ch) + v4 + 29) & 4) != 0
    && __crtLCMapStringA(
         (struct localeinfo_struct *)v3,
         *(_DWORD *)(v4 + 12),
         0x200u,
         MultiByteStr,
         2,
         DestStr,
         2,
         *(_DWORD *)(v4 + 4),
         1) )
  {
    result = (unsigned __int8)DestStr[1] + ((unsigned __int8)DestStr[0] << 8);
    goto LABEL_11;
  }
  if ( v6 )
    *(_DWORD *)(v5 + 112) &= ~2u;
  return Ch;
}

