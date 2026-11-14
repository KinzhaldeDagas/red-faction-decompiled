// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D19C __cropzeros_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): LocaleUpdate607051 is constructed before own
// validation; normal return clears thread DWORD+112 mask2 iff its cleanup BYTE+12 is set. Decimal separator uses ONLY first byte of localeInfo+188 -> lconv -> decimal_point. No own
// SEH/finally for exceptions escaping helpers. Cdecl(mutableString,locale). Find first byte equal to locale decimal separator or NUL. No separator -> no string writes (pointer
// advanced once past NUL internally). With separator, scan following bytes until NUL or lowercase/uppercase e, then scan BACKWARD over ASCII '0'. If resulting byte is separator, step
// back once; copy saved e/E suffix or NUL forward to the next destination byte, including terminator. Removes trailing fractional zeros and an empty decimal separator; recognizes e/E
// but not p/P as suffix delimiters. No numeric validation, sign processing, allocation, bounds/NULL guard or own errno. EAX cursor/thread-pointer return incidental, not stable
// original-string contract.
char *__cdecl _cropzeros_l(char *a1, struct localeinfo_struct *a2)
{
  char *v2; // eax
  char i; // cl
  char v4; // cl
  char *result; // eax
  char v6; // cl
  char *v7; // edx
  char v8; // cl
  int v9; // [esp+4h] [ebp-10h] BYREF
  int v10; // [esp+Ch] [ebp-8h]
  char v11; // [esp+10h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v9, a2);
  v2 = a1;
  for ( i = *a1; *v2; i = *++v2 )
  {
    if ( i == ***(_BYTE ***)(v9 + 188) )
      break;
  }
  v4 = *v2;
  result = v2 + 1;
  if ( v4 )
  {
    while ( 1 )
    {
      v6 = *result;
      if ( !*result || v6 == 101 || v6 == 69 )
        break;
      ++result;
    }
    v7 = result;
    do
      --result;
    while ( *result == 48 );
    if ( *result == ***(_BYTE ***)(v9 + 188) )
      --result;
    do
    {
      v8 = *v7;
      ++result;
      ++v7;
      *result = v8;
    }
    while ( v8 );
  }
  if ( v11 )
  {
    result = (char *)v10;
    *(_DWORD *)(v10 + 112) &= ~2u;
  }
  return result;
}

