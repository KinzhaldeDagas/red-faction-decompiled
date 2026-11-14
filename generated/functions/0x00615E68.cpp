// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00615E68 __isctype_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw int C,int mask,optional locale). Construct
// LocaleUpdate; unsigned(C+1)<=256 includes exactly C=-1..255, directly read WORD at classTable+2*C (C=-1 indexes preceding WORD), return class&mask. Other ints: use high BYTE1(C)
// lead-byte classification, build source[B1,B0,0] length2 when lead, else[B0,0] length1, ignoring other input bits. Call
// crtGetStringTypeA(&localLocale,1,source,length,&WORDtype,locinfo+4 codepage,locinfo+0x14 LCID,1). Status0 returns0; any nonzero status returns unsigned WORDtype&FULL32-bit mask. No
// own errno or invalid-handler call, no rejection of out-of-range packed values, no Boolean normalization. All own normal returns after locale construction clear threadData+0x70
// mask0x2 only if local update-object byte+12 is nonzero; nested supplied-locale objects do not acquire another pin. There is no SEH/finally cleanup in this body if a helper throws.
int __cdecl _isctype_l(int C, int Type, _locale_t Locale)
{
  __int16 v3; // bx
  int v4; // eax
  int v5; // ecx
  int result; // eax
  __crt_locale_pointers Localea; // [esp+4h] [ebp-18h] BYREF
  int v8; // [esp+Ch] [ebp-10h]
  char v9; // [esp+10h] [ebp-Ch]
  CHAR MultiByteStr; // [esp+14h] [ebp-8h] BYREF
  char v11; // [esp+15h] [ebp-7h]
  char v12; // [esp+16h] [ebp-6h]
  WORD CharType; // [esp+18h] [ebp-4h] BYREF
  int Ca; // [esp+24h] [ebp+8h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Localea, (struct localeinfo_struct *)Locale);
  v3 = C;
  if ( (unsigned int)(C + 1) <= 0x100 )
  {
    v4 = *(unsigned __int16 *)(*((_DWORD *)Localea.locinfo + 50) + 2 * C);
    goto LABEL_11;
  }
  Ca = C >> 8;
  if ( _isleadbyte_l(HIBYTE(v3), &Localea) )
  {
    MultiByteStr = Ca;
    v11 = v3;
    v12 = 0;
    v5 = 2;
  }
  else
  {
    MultiByteStr = v3;
    v11 = 0;
    v5 = 1;
  }
  if ( __crtGetStringTypeA(
         (struct localeinfo_struct *)&Localea,
         1u,
         &MultiByteStr,
         v5,
         &CharType,
         *((_DWORD *)Localea.locinfo + 1),
         *((_DWORD *)Localea.locinfo + 5),
         1) )
  {
    v4 = CharType;
LABEL_11:
    result = Type & v4;
    if ( v9 )
      *(_DWORD *)(v8 + 112) &= ~2u;
    return result;
  }
  if ( v9 )
    *(_DWORD *)(v8 + 112) &= ~2u;
  return 0;
}

