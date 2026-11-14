// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D2DB __cftoe2_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Decimal record layout from native accesses:16 bytes
// {int sign at0 (45 means negative),int decimalPoint at4,int conversionStatus at8,char* digits at12}. LocaleUpdate607051 is constructed before own validation; normal return clears
// thread DWORD+112 mask2 iff its cleanup BYTE+12 is set. Decimal separator uses ONLY first byte of localeInfo+188 -> lconv -> decimal_point. No own SEH/finally for exceptions
// escaping helpers. Mixed ABI EAX=output, six caller-popped stack slots {unsigned capacity,int precision,int uppercase,record*,char adjust,locale}. Return0/errno-style status. NULL
// output or capacity0 -> errno22 + invalid_parameter(5zeros),22 without clearing output. Require unsigned capacity > (precision>0?precision:0)+9 modulo32; otherwise errno34 + invalid
// handler,34 without clearing. Negative precision is NOT normalized; pointer arithmetic may move backward. If LOW BYTE adjust nonzero, shift string at output+(sign==45) right
// by(precision>0). Write '-' iff sign45; precision>0 moves first digit left and inserts separator. Exponent suffix position = currentPointer+precision+(adjustByte==0). strcpy_s
// suffix 'e+000', remaining capacity or FFFFFFFF sentinel; nonzero copy result -> Watson(5zeros). Uppercase int nonzero changes e to E. Unless record.digits[0]=='0',
// exponent=decimalPoint-1, signed magnitude emitted into three template digits; negative exponent uses '-'. No exponent-range validation beyond assumptions on record. Output-format
// global2021DB4 mask1 plus hundreds digit0 removes leading exponent zero by overlapping memcpy_0 of three bytes INCLUDING terminator. Does not itself generate/round initial digits,
// trim mantissa zeros, validate record pointer or catch exceptions.
int __usercall _cftoe2_l@<eax>(
        _BYTE *a1@<eax>,
        unsigned int a2,
        int a3,
        int a4,
        _DWORD *a5,
        char a6,
        struct localeinfo_struct *a7)
{
  int *v8; // eax
  int v9; // edi
  int v11; // eax
  _BYTE *v12; // esi
  char *v13; // esi
  rsize_t v14; // ebx
  _BYTE *v15; // ecx
  _BYTE *v16; // esi
  int v17; // eax
  _BYTE *v18; // esi
  _BYTE *v19; // esi
  int v20; // [esp-4h] [ebp-20h]
  int v21; // [esp+Ch] [ebp-10h] BYREF
  int v22; // [esp+14h] [ebp-8h]
  char v23; // [esp+18h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v21, a7);
  if ( !a1 || !a2 )
  {
    v8 = _errno();
    v20 = 22;
LABEL_3:
    v9 = v20;
    *v8 = v20;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v23 )
      *(_DWORD *)(v22 + 112) &= ~2u;
    return v9;
  }
  if ( a3 <= 0 )
    v11 = 0;
  else
    v11 = a3;
  if ( a2 <= v11 + 9 )
  {
    v8 = _errno();
    v20 = 34;
    goto LABEL_3;
  }
  if ( a6 )
    _shift(&a1[*a5 == 45], a3 > 0);
  v12 = a1;
  if ( *a5 == 45 )
  {
    *a1 = 45;
    v12 = a1 + 1;
  }
  if ( a3 > 0 )
  {
    *v12 = v12[1];
    *++v12 = ***(_BYTE ***)(v21 + 188);
  }
  v13 = &v12[a3 + (a6 == 0)];
  if ( a2 == -1 )
    v14 = -1;
  else
    v14 = a2 + a1 - v13;
  if ( strcpy_s(v13, v14, "e+000") )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  v15 = v13 + 2;
  if ( a4 )
    *v13 = 69;
  v16 = v13 + 1;
  if ( *(_BYTE *)a5[3] != 48 )
  {
    v17 = a5[1] - 1;
    if ( v17 < 0 )
    {
      v17 = 1 - a5[1];
      *v16 = 45;
    }
    v18 = v16 + 1;
    if ( v17 >= 100 )
    {
      *v18 += v17 / 100;
      v17 %= 100;
    }
    v19 = v18 + 1;
    if ( v17 >= 10 )
    {
      *v19 += v17 / 10;
      LOBYTE(v17) = v17 % 10;
    }
    v19[1] += v17;
  }
  if ( (unk_2021DB4 & 1) != 0 && *v15 == 48 )
    memcpy_0(v15, v15 + 1, 3u);
  if ( v23 )
    *(_DWORD *)(v22 + 112) &= ~2u;
  return 0;
}

