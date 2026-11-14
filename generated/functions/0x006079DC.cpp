// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006079DC __Strftime_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(output,size_t capacity,const format*,optional
// tm*,optional timeData*,optional localeInfo*), size_t count excluding NUL or0; return/capacity/source/timeData prototype repaired. Construct LocaleUpdate BEFORE validation. NULL
// output OR capacity0 ->errno22,invalid_parameter5zeros,return0; capacity0 does NOT clear nonNULL output. With valid buffer/capacity immediately output[0]=0, then NULL format
// ->EINVAL handler/0. Select explicit timeData if nonNULL, otherwise locinfo DWORD+0D4. No time-data validation/refcount change here; locale snapshot normal exits clear PTD DWORD+112
// mask2 iff cleanup flag set, no SEH/finally on escaping exceptions. Remaining counter initially FULL capacity, unsigned, output cursor initially original. Copy format literals until
// NUL/counter0. isleadbyte_l on SIGNED char handles two-byte source only if remaining>1; require nonNUL trailing byte then copy both; missing trail sets invalid flag. Remaining1
// copies lead alone, reaches0 and ultimately range error. '%' requires tm NONNULL EVEN for '%%' or accepted no-op directives; consume optional SINGLE '#', pass next byte (including
// NUL) to expandtime with alternate0/1, then advance source once. Numeric/locale/timezone rules delegated. No format-length bound, calendar normalization or recursive formatting call
// in this body. With counter>0 and format exhausted: append NUL at CURRENT cursor, return capacity-remaining modulo32 (empty successful format returns0 without clearing prior errno).
// Counter0 is failure even if last emitted byte exactly consumed complete format. Common exhausted/expansion-failed/malformed-literal path FIRST clears original output[0]. If no
// invalid flag and remaining0 ->errno34/return0 WITHOUT invalid handler; otherwise errno22 + invalid_parameter5zeros,0. Expansion failure with remaining>0 sets invalid flag; failure
// with remaining0 classifies as range. An invalid tm field can therefore invoke invalid handler in expandtime AND AGAIN here if both return. SPECIAL direct path: tmNULL encountered
// after a literal prefix jumps straight to errno22/invalid handler WITHOUT common output reset or final terminator. Already written prefix can remain unterminated; no blanket
// empty-buffer-on-all-errors promise. NULL format had only initial clear. Every own normal return performs conditional locale-pin cleanup; no own security cookie, lock, allocation,
// errno reset on success, or preservation of partial output on the common cleared path.
size_t __cdecl _Strftime_l(
        char *a1,
        size_t a2,
        const char *a3,
        const struct tm *a4,
        _DWORD *a5,
        struct localeinfo_struct *a6)
{
  size_t result; // eax
  size_t v7; // edi
  const char *v8; // esi
  struct tm *v9; // eax
  char v10; // al
  char *v11; // esi
  unsigned int v12; // eax
  __crt_locale_pointers Locale; // [esp+4h] [ebp-20h] BYREF
  int v14; // [esp+Ch] [ebp-18h]
  char v15; // [esp+10h] [ebp-14h]
  char *v16; // [esp+14h] [ebp-10h]
  struct tm *v17; // [esp+18h] [ebp-Ch]
  int v18; // [esp+1Ch] [ebp-8h]
  char v19[4]; // [esp+20h] [ebp-4h] BYREF

  v18 = 0;
  v16 = a1;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Locale, a6);
  if ( !a1 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v15 )
      *(_DWORD *)(v14 + 112) &= ~2u;
    return 0;
  }
  v7 = a2;
  if ( !a2 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v15 )
      *(_DWORD *)(v14 + 112) &= ~2u;
    return 0;
  }
  v8 = a3;
  *a1 = 0;
  if ( !v8 )
    goto LABEL_35;
  v9 = (struct tm *)a5;
  if ( !a5 )
    v9 = *((struct tm **)Locale.locinfo + 53);
  v17 = v9;
  *(_DWORD *)v19 = v7;
  if ( !v7 )
  {
LABEL_30:
    *v16 = 0;
    if ( !v18 && !*(_DWORD *)v19 )
    {
      *_errno() = 34;
LABEL_36:
      if ( v15 )
        *(_DWORD *)(v14 + 112) &= ~2u;
      return 0;
    }
LABEL_35:
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    goto LABEL_36;
  }
  do
  {
    v10 = *v8;
    if ( !*v8 )
      break;
    if ( v10 == 37 )
    {
      if ( !a4 )
        goto LABEL_35;
      v11 = (char *)(v8 + 1);
      v12 = 0;
      if ( *v11 == 35 )
      {
        v12 = 1;
        ++v11;
      }
      if ( !_expandtime(*v11, a4, &a1, (struct localeinfo_struct *)&Locale, (unsigned int *)v19, v17, v12) )
      {
        if ( *(_DWORD *)v19 )
          v18 = 1;
        goto LABEL_30;
      }
      v8 = v11 + 1;
    }
    else
    {
      if ( _isleadbyte_l(v10, &Locale) && *(_DWORD *)v19 > 1u )
      {
        if ( !v8[1] )
        {
          v18 = 1;
          goto LABEL_30;
        }
        *a1++ = *v8;
        --*(_DWORD *)v19;
        ++v8;
      }
      *a1++ = *v8++;
      --*(_DWORD *)v19;
    }
  }
  while ( *(_DWORD *)v19 );
  if ( !*(_DWORD *)v19 )
    goto LABEL_30;
  *a1 = 0;
  result = v7 - *(_DWORD *)v19;
  if ( v15 )
    *(_DWORD *)(v14 + 112) &= ~2u;
  return result;
}

