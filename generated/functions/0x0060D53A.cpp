// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D53A __cftoa_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): LocaleUpdate607051 is constructed before own
// validation; normal return clears thread DWORD+112 mask2 iff its cleanup BYTE+12 is set. Decimal separator uses ONLY first byte of localeInfo+188 -> lconv -> decimal_point. No own
// SEH/finally for exceptions escaping helpers. Cdecl(binary64Pointer,output,unsigned capacity,int precision,int uppercase,locale), hex float formatter. Clamp negative precision to0.
// NULL output/capacity0 -> errno22 + invalid_parameter(5zeros),22. Valid output cleared BEFORE require unsigned capacity>precision+11 modulo32; failure errno34/invalid34. No
// sum-overflow/input-pointer guard. Input exponent7FF -> call NON-locale cftoe wrapper(output+2,capacity-2 or FFFFFFFF,precision,uppercase0), so supplied locale NOT forwarded on
// special path; status failure clears original output/returns status. Success prepend sign iff delegated string starts '-', then 0x/0X; find LAST lowercase e in remaining text,
// change to p/P and truncate at e-position+3 (sign and ONE exponent digit). No found-e means no such rewrite. Finite path uses raw sign bit (preserves negative zero), prefix0x/X,
// leading1 for normal,0 for subnormal/zero. Binary exponent = encodedExponent minus1023 normal, minus1022 nonzero subnormal, minus0 zero. Decimal separator first byte only when
// precision>0, otherwise write zero marker and later overwrite it with p/P. Emit up to13 high-to-low fraction nibbles as chosen-case hex; pad extra precision with '0'. If undisplayed
// next nibble >8, round carry backward over f/F (write0); '9' becomes a/A; reaching separator increments leading digit. EXACT8 does NOT round and no sticky/tie-to-even test or
// exponent renormalization. Rounding is native integer logic, no x87/MXCSR rounding-mode consult. Append p/P, explicit +/- and shortest decimal exponent (one to four digits), NUL;
// return0. No own exception catch, errno on success, special-value classification string policy beyond delegated cftoe, or trailing fractional-zero trimming.
int __cdecl _cftoa_l(double *a1, _BYTE *a2, unsigned int a3, int Size, int a5, struct localeinfo_struct *a6)
{
  _BYTE *v6; // esi
  int *v7; // eax
  int v8; // esi
  int result; // eax
  unsigned int v10; // eax
  bool v11; // zf
  _BYTE *v12; // esi
  char *v13; // eax
  _BYTE *v14; // esi
  _BYTE *v15; // esi
  _BYTE *v16; // esi
  _BYTE *v17; // eax
  _BYTE *v18; // esi
  int v19; // eax
  unsigned __int16 v20; // ax
  unsigned int v21; // ecx
  _BYTE *i; // eax
  _BYTE *v23; // esi
  __int64 v24; // rax
  __int64 v25; // rcx
  _BYTE *v26; // esi
  _BYTE *v27; // edi
  __int64 v28; // rax
  __int64 v29; // rcx
  __int64 v30; // rax
  __int64 v31; // rcx
  __int64 v32; // rcx
  __int64 v33; // [esp-Ch] [ebp-38h]
  int v34; // [esp-4h] [ebp-30h]
  int v35; // [esp+8h] [ebp-24h] BYREF
  int v36; // [esp+10h] [ebp-1Ch]
  char v37; // [esp+14h] [ebp-18h]
  int v38; // [esp+18h] [ebp-14h]
  int v39; // [esp+1Ch] [ebp-10h]
  unsigned __int64 v40; // [esp+20h] [ebp-Ch]
  int v41; // [esp+28h] [ebp-4h]
  _BYTE *v42; // [esp+38h] [ebp+Ch]

  v38 = 1023;
  v41 = 48;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v35, a6);
  if ( Size < 0 )
    Size = 0;
  v6 = a2;
  if ( !a2 || !a3 )
  {
    v7 = _errno();
    v34 = 22;
LABEL_5:
    v8 = v34;
    *v7 = v34;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v37 )
      *(_DWORD *)(v36 + 112) &= ~2u;
    return v8;
  }
  *a2 = 0;
  if ( a3 <= Size + 11 )
  {
    v7 = _errno();
    v34 = 34;
    goto LABEL_5;
  }
  LODWORD(v40) = *(_DWORD *)a1;
  if ( ((*((_DWORD *)a1 + 1) >> 20) & 0x7FF) == 0x7FF )
  {
    v10 = a3;
    if ( a3 != -1 )
      v10 = a3 - 2;
    result = _cftoe(a1, a2 + 2, v10, Size, 0);
    if ( result )
    {
      v11 = v37 == 0;
      *a2 = 0;
      if ( !v11 )
        *(_DWORD *)(v36 + 112) &= ~2u;
      return result;
    }
    if ( a2[2] == 45 )
    {
      *a2 = 45;
      v6 = a2 + 1;
    }
    *v6 = 48;
    v12 = v6 + 1;
    *v12 = a5 == 0 ? 120 : 88;
    v13 = strrchr(v12 + 1, 101);
    if ( v13 )
    {
      *v13 = a5 == 0 ? 112 : 80;
      v13[3] = 0;
    }
  }
  else
  {
    if ( (*((_DWORD *)a1 + 1) & 0x80000000) != 0 )
    {
      *a2 = 45;
      v6 = a2 + 1;
    }
    *v6 = 48;
    v14 = v6 + 1;
    *v14 = a5 == 0 ? 120 : 88;
    v15 = v14 + 1;
    if ( (*((_DWORD *)a1 + 1) & 0x7FF00000) != 0 )
    {
      *v15 = 49;
      v16 = v15 + 1;
    }
    else
    {
      *v15 = 48;
      v16 = v15 + 1;
      if ( *((_DWORD *)a1 + 1) & 0xFFFFF | *(_DWORD *)a1 )
        v38 = 1022;
      else
        v38 = 0;
    }
    v17 = v16;
    v18 = v16 + 1;
    v42 = v17;
    if ( Size )
      *v17 = ***(_BYTE ***)(v35 + 188);
    else
      *v17 = 0;
    v19 = *(_DWORD *)a1;
    HIDWORD(v40) = *((_DWORD *)a1 + 1) & 0xFFFFF;
    if ( HIDWORD(v40) || v19 )
    {
      v40 = 0xF000000000000LL;
      do
      {
        if ( Size <= 0 )
          break;
        v20 = ((v40 & *(_QWORD *)a1 & 0xFFFFFFFFFFFFFLL) >> v41) + 48;
        if ( v20 > 0x39u )
          LOBYTE(v20) = (a5 != 0 ? 7 : 39) + v20;
        v21 = HIDWORD(v40);
        v41 -= 4;
        *v18++ = v20;
        --Size;
        v40 = __PAIR64__(v21, v40) >> 4;
      }
      while ( (v41 & 0x8000u) == 0 );
      if ( (v41 & 0x8000u) == 0 && (unsigned __int16)((v40 & *(_QWORD *)a1 & 0xFFFFFFFFFFFFFLL) >> v41) > 8u )
      {
        for ( i = v18 - 1; *i == 102 || *i == 70; --i )
          *i = 48;
        if ( i == v42 )
        {
          ++*(i - 1);
        }
        else if ( *i == 57 )
        {
          *i = a5 != 0 ? 65 : 97;
        }
        else
        {
          ++*i;
        }
      }
    }
    if ( Size > 0 )
    {
      memset(v18, 48, Size);
      v18 += Size;
    }
    if ( !*v42 )
      v18 = v42;
    *v18 = a5 == 0 ? 112 : 80;
    v23 = v18 + 1;
    HIDWORD(v25) = 0;
    v24 = ((*(_QWORD *)a1 >> 52) & 0x7FFLL) - (unsigned int)v38;
    if ( v24 < 0 )
    {
      *v23 = 45;
      v26 = v23 + 1;
      v24 = -v24;
    }
    else
    {
      *v23 = 43;
      v26 = v23 + 1;
    }
    v27 = v26;
    *v26 = 48;
    if ( v24 >= 0 )
    {
      LODWORD(v25) = 1000;
      if ( v24 >= 1000 )
      {
        v33 = v25;
        v29 = v24 % v25;
        v28 = v24 / v33;
        *v26++ = v28 + 48;
        v39 = HIDWORD(v28);
        v24 = v29;
        if ( v26 != v27 )
          goto LABEL_60;
      }
    }
    if ( v24 >= 100 )
    {
LABEL_60:
      v31 = v24 % 100;
      v30 = v24 / 100;
      *v26 = v30 + 48;
      v39 = HIDWORD(v30);
      ++v26;
      v24 = v31;
    }
    if ( v26 != v27 || v24 >= 10 )
    {
      v32 = v24 % 10;
      *v26++ = v24 / 10 + 48;
      LOBYTE(v24) = v24 % 10;
      v39 = HIDWORD(v32);
    }
    *v26 = v24 + 48;
    v26[1] = 0;
  }
  if ( v37 )
    *(_DWORD *)(v36 + 112) &= ~2u;
  return 0;
}

