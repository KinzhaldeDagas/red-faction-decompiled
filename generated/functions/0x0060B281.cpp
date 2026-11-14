// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B281 ?strtoxl@@YAKPAUlocaleinfo_struct@@PBDPAPBDHH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(localeInfo*,const text*,optional
// endPointerSlot*,SIGNED radix,int initialFlags), returns32 raw unsigned bits; radix prototype corrected from unsigned to signed. LocaleUpdate before validation; if endSlot nonNULL
// publish original text BEFORE checking text/radix. NULL text or radix!=0 outside SIGNED2..36 -> errno22,invalid_parameter5zeros, normal cleanup,0. Normal exits clear PTD DWORD+112
// mask2 iff local cleanup flag; no own SEH/finally. Whitespace uses unsigned input bytes and locale ctype mask8 (direct WORD table if locinfo+172<=1; isctype_l otherwise). Optional
// '-' ORs flag2; '+' does not clear preexisting flag2. Radix0 picks10 except leading0 picks8, or0x/X picks16. Explicit radix16 also consumes0x/X WITHOUT checking following valid
// digit; no digits resets end to ORIGINAL text, including sign/whitespace. Radix2 has no binary-prefix special handling. Digit classification from locale WORD table: mask4 -> SIGNED
// byte-'0'; otherwise mask103 -> ASCII lowercase a..z converted by subtract32 then SIGNED byte-'A'+10; accept only unsigned digit<radix. Thus digit mapping is ASCII arithmetic gated
// by locale classification, not general Unicode digit conversion. Sticky flags: bit1 UNSIGNED mode,bit2 negate,bit4 overflow,bit8 sawDigit; initial flags are caller supplied and NOT
// reset. Before multiply, unsigned accumulator compared with FFFFFFFF/radix cutoff and remainder. Successful digit updates accumulator modulo32; overflow digit sets bit4 but is not
// accumulated. With endSlot NULL break immediately on overflow; otherwise continue consuming recognized in-range digits (later arithmetic may still update if cutoff test permits,
// overflow flag stays set). No digits (unless sawDigit preseeded) ->value0,end original text. Otherwise bit4 OR signed-mode magnitude outside [-80000000,+7FFFFFFF] -> errno34,
// saturated MAGNITUDE: unsignedFFFFFFFF; signed negative80000000, signed positive7FFFFFFF. Publish end at first unconverted byte. THEN unconditionally NEGATE magnitude if flag2, even
// after unsigned saturation. Consequently unsigned-mode negative OVERFLOW returns raw1 (FFFFFFFF negated), with errno34; this is exact native order. Signed negative saturation
// remains80000000. Valid conversions do not clear prior errno. Redundant post-whitespace radix guard returns0/end original without its own errno call if reached. No bounded length,
// allocation, output alias validation or separate doserrno mapping.
unsigned int __cdecl strtoxl(struct localeinfo_struct *a1, const char *a2, const char **a3, int a4, int a5)
{
  struct __crt_locale_data *locinfo; // ecx
  unsigned __int8 v7; // bl
  const char *i; // edi
  int v9; // eax
  _BYTE *v10; // edi
  int v11; // esi
  unsigned int v12; // eax
  unsigned int v13; // ecx
  int v14; // ecx
  const char *v15; // edi
  __crt_locale_pointers Locale; // [esp+8h] [ebp-14h] BYREF
  int v17; // [esp+10h] [ebp-Ch]
  char v18; // [esp+14h] [ebp-8h]
  unsigned int v19; // [esp+18h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Locale, a1);
  if ( a3 )
    *a3 = a2;
  if ( !a2 || a4 && (a4 < 2 || a4 > 36) )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v18 )
      *(_DWORD *)(v17 + 112) &= ~2u;
    return 0;
  }
  locinfo = Locale.locinfo;
  v7 = *a2;
  v19 = 0;
  for ( i = a2 + 1; ; ++i )
  {
    if ( *((int *)locinfo + 43) <= 1 )
    {
      v9 = *(_WORD *)(*((_DWORD *)locinfo + 50) + 2 * v7) & 8;
    }
    else
    {
      v9 = _isctype_l(v7, 8, &Locale);
      locinfo = Locale.locinfo;
    }
    if ( !v9 )
      break;
    v7 = *i;
  }
  if ( v7 == 45 )
  {
    a5 |= 2u;
  }
  else if ( v7 != 43 )
  {
    goto LABEL_20;
  }
  v7 = *i++;
LABEL_20:
  if ( a4 )
  {
    if ( a4 != 16 || v7 != 48 )
      goto LABEL_32;
  }
  else
  {
    if ( v7 != 48 )
    {
      a4 = 10;
      goto LABEL_32;
    }
    if ( *i != 120 && *i != 88 )
    {
      a4 = 8;
      goto LABEL_32;
    }
    a4 = 16;
  }
  if ( *i == 120 || *i == 88 )
  {
    v10 = i + 1;
    v7 = *v10;
    i = v10 + 1;
  }
LABEL_32:
  v11 = *((_DWORD *)locinfo + 50);
  v12 = 0xFFFFFFFF / a4;
  while ( 1 )
  {
    if ( (*(_WORD *)(v11 + 2 * v7) & 4) != 0 )
    {
      v13 = (char)v7 - 48;
    }
    else
    {
      if ( (*(_WORD *)(v11 + 2 * v7) & 0x103) == 0 )
        break;
      v14 = (char)v7;
      if ( (unsigned __int8)(v7 - 97) <= 0x19u )
        v14 = (char)v7 - 32;
      v13 = v14 - 55;
    }
    if ( v13 >= a4 )
      break;
    a5 |= 8u;
    if ( v19 < v12 || v19 == v12 && v13 <= 0xFFFFFFFF % a4 )
    {
      v19 = v13 + a4 * v19;
    }
    else
    {
      a5 |= 4u;
      if ( !a3 )
        break;
    }
    v7 = *i++;
  }
  v15 = i - 1;
  if ( (a5 & 8) != 0 )
  {
    if ( (a5 & 4) != 0 || (a5 & 1) == 0 && ((a5 & 2) != 0 && v19 > 0x80000000 || (a5 & 2) == 0 && v19 > 0x7FFFFFFF) )
    {
      *_errno() = 34;
      if ( (a5 & 1) != 0 )
        v19 = -1;
      else
        v19 = ((a5 & 2) != 0) + 0x7FFFFFFF;
    }
  }
  else
  {
    if ( a3 )
      v15 = a2;
    v19 = 0;
  }
  if ( a3 )
    *a3 = v15;
  if ( (a5 & 2) != 0 )
    v19 = -v19;
  if ( v18 )
    *(_DWORD *)(v17 + 112) &= ~2u;
  return v19;
}

