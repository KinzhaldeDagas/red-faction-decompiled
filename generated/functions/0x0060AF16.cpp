// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060AF16 __toupper_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw int C,optional locale), uppercase
// conversion. Construct LocaleUpdate. For unsigned C<256: test class mask0x2 via direct locinfo+0xC8 WORD table when signed mbMax+0xAC<=1, otherwise isctype_l(C,mask,&localLocale).
// Matching class returns unsigned BYTE[*(locinfo+0xD0)+C]; nonmatch returns ORIGINAL int unchanged. Unsigned C>=256 (including negative ints/EOF) takes packed-character path: only if
// signed mbMax>1 AND isleadbyte_l((C>>8)&255,&localLocale) nonzero build bytes[B1(C),B0(C),0],length2; otherwise set errno42, build[lowByte(C),0],length1 and STILL attempt mapping.
// Call crtLCMapStringA(&localLocale,locinfo+0x14 LCID,0x200,source,length,destination,capacity3,locinfo+4 codepage,1). Zero status returns ORIGINAL int; status1 returns destination
// unsigned byte0; ANY other nonzero status returns (byte0<<8)|byte1. Upper16 input bits are not mapped; no separate EOF passthrough or valid-Unicode-scalar check. Own errno42 is not
// cleared by later mapping success. All own normal returns after locale construction clear threadData+0x70 mask0x2 only if local update-object byte+12 is nonzero; nested
// supplied-locale objects do not acquire another pin. There is no SEH/finally cleanup in this body if a helper throws.
int __cdecl _toupper_l(int C, _locale_t Locale)
{
  struct __crt_locale_data *locinfo; // ecx
  int v4; // eax
  int result; // eax
  int v6; // ecx
  int v7; // eax
  bool v8; // zf
  __crt_locale_pointers v9; // [esp+4h] [ebp-18h] BYREF
  int v10; // [esp+Ch] [ebp-10h]
  char v11; // [esp+10h] [ebp-Ch]
  char DestStr[4]; // [esp+14h] [ebp-8h] BYREF
  CHAR MultiByteStr; // [esp+18h] [ebp-4h] BYREF
  char v14; // [esp+19h] [ebp-3h]
  char v15; // [esp+1Ah] [ebp-2h]
  int Ca; // [esp+24h] [ebp+8h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v9, (struct localeinfo_struct *)Locale);
  if ( (unsigned int)C >= 0x100 )
  {
    if ( *((int *)v9.locinfo + 43) > 1 && (Ca = C >> 8, _isleadbyte_l(BYTE1(C), &v9)) )
    {
      MultiByteStr = Ca;
      v14 = C;
      v15 = 0;
      v6 = 2;
    }
    else
    {
      *_errno() = 42;
      MultiByteStr = C;
      v14 = 0;
      v6 = 1;
    }
    v7 = __crtLCMapStringA(
           (struct localeinfo_struct *)&v9,
           *((_DWORD *)v9.locinfo + 5),
           0x200u,
           &MultiByteStr,
           v6,
           DestStr,
           3,
           *((_DWORD *)v9.locinfo + 1),
           1);
    if ( v7 )
    {
      v8 = v7 == 1;
      result = (unsigned __int8)DestStr[0];
      if ( !v8 )
        result = (unsigned __int8)DestStr[1] | ((unsigned __int8)DestStr[0] << 8);
      goto LABEL_17;
    }
  }
  else
  {
    locinfo = v9.locinfo;
    if ( *((int *)v9.locinfo + 43) <= 1 )
    {
      v4 = *(_WORD *)(*((_DWORD *)v9.locinfo + 50) + 2 * C) & 2;
    }
    else
    {
      v4 = _isctype_l(C, 2, &v9);
      locinfo = v9.locinfo;
    }
    if ( v4 )
    {
      result = *(unsigned __int8 *)(*((_DWORD *)locinfo + 52) + C);
LABEL_17:
      if ( v11 )
        *(_DWORD *)(v10 + 112) &= ~2u;
      return result;
    }
  }
  if ( v11 )
    *(_DWORD *)(v10 + 112) &= ~2u;
  return C;
}

