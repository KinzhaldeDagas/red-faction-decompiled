// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CF69 crt_parse_string_to_binary32_locale
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl(output,text,locale). Construct local LocaleUpdate607051; call618F47 __strgtold12_l(local12byteValue,&localEnd,text,0,0,0,0,&localeUpdate), save raw
// parser flags. ALWAYS next call0061FAD6 conversion(local12byteValue,output), even when parser flags already indicate range condition; destination writes precede status decision. If
// parserFlags&3 nonzero: bit1(value1) takes precedence and returns4, otherwise bit2(value2) returns3; converter status ignored on those paths. With neither parser bit, converter1
// ->3,converter2 ->4,other ->0. Thus3 overflow/4 underflow per verified converter statuses; no separate invalid-syntax/end-consumption test. On EACH normal status-return path, if
// localeUpdate BYTE+12 nonzero clear mask0x2 of thread state DWORD+112; explicit supplied locale never sets that cleanup flag. Stack cookie validated via605EE4 while preserving
// status EAX. No output/text NULL or size guard, bounded string length, public endptr output, errno assignment or explicit SEH cleanup if delegates throw.
int __cdecl crt_parse_string_to_binary32_locale(unsigned int *a1, char *a2, struct localeinfo_struct *a3)
{
  int v3; // eax
  char *v6; // [esp+Ch] [ebp-28h] BYREF
  _BYTE v7[8]; // [esp+10h] [ebp-24h] BYREF
  int v8; // [esp+18h] [ebp-1Ch]
  char v9; // [esp+1Ch] [ebp-18h]
  int v10; // [esp+20h] [ebp-14h]
  unsigned __int8 v11[12]; // [esp+24h] [ebp-10h] BYREF

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v7, a3);
  v10 = __strgtold12_l(v11, &v6, a2, 0, 0, 0, 0, (_LocaleUpdate *)v7);
  v3 = crt_ld12_to_binary32(v11, a1);
  if ( (v10 & 3) != 0 )
  {
    if ( (v10 & 1) != 0 )
      goto LABEL_8;
    if ( (v10 & 2) != 0 )
      goto LABEL_3;
  }
  else
  {
    if ( v3 == 1 )
    {
LABEL_3:
      if ( v9 )
        *(_DWORD *)(v8 + 112) &= ~2u;
      return 3;
    }
    if ( v3 == 2 )
    {
LABEL_8:
      if ( v9 )
        *(_DWORD *)(v8 + 112) &= ~2u;
      return 4;
    }
  }
  if ( v9 )
    *(_DWORD *)(v8 + 112) &= ~2u;
  return 0;
}

