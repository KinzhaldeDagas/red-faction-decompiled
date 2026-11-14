// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D8AD __cftof2_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Decimal record layout from native accesses:16 bytes
// {int sign at0 (45 means negative),int decimalPoint at4,int conversionStatus at8,char* digits at12}. LocaleUpdate607051 is constructed before own validation; normal return clears
// thread DWORD+112 mask2 iff its cleanup BYTE+12 is set. Decimal separator uses ONLY first byte of localeInfo+188 -> lconv -> decimal_point. No own SEH/finally for exceptions
// escaping helpers. Mixed ABI EAX=record*, ECX=output; four caller-popped stack slots {unsigned capacity,int precision,char adjust,locale}. Read record.decimalPoint-1 BEFORE
// LocaleUpdate/output validation. NULL output or capacity0 -> errno22, invalid_parameter(5zeros),22; no other capacity check. If LOW BYTE adjust nonzero AND
// decimalPoint-1==precision, overwrite output[decimalPoint-1+(sign==45)]='0' and followingNUL. Write sign if45. decimalPoint<=0 -> shift unsigned-digit string right1 and prepend0;
// positive -> point cursor after decimalPoint digits. Only precision>0 inserts decimal separator via shift1. If decimalPoint<0 also insert leading fractional zeros:
// count=-decimalPoint if adjustByte!=0 OR precision>=-decimalPoint, otherwise count=precision; shift existing suffix by count then memset zeros. Return0. Does not create/round source
// digits, trim zeros, enforce complete output capacity, normalize negative precision or validate record pointer. All shift/copy overlap behavior delegated.
int __usercall _cftof2_l@<eax>(
        _DWORD *a1@<eax>,
        char *a2@<ecx>,
        unsigned int a3,
        int Size,
        char a5,
        struct localeinfo_struct *a6)
{
  int v8; // esi
  char *v10; // eax
  char *v11; // esi
  int v12; // eax
  char *v13; // esi
  int v14; // ebx
  char *v15; // esi
  int v16; // ebx
  int v17; // [esp+Ch] [ebp-10h] BYREF
  int v18; // [esp+14h] [ebp-8h]
  char v19; // [esp+18h] [ebp-4h]

  v8 = a1[1] - 1;
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v17, a6);
  if ( a2 && a3 )
  {
    if ( a5 && v8 == Size )
    {
      v10 = &a2[v8 + (*a1 == 45)];
      *v10 = 48;
      v10[1] = 0;
    }
    v11 = a2;
    if ( *a1 == 45 )
    {
      *a2 = 45;
      v11 = a2 + 1;
    }
    v12 = a1[1];
    if ( v12 > 0 )
    {
      v13 = &v11[v12];
    }
    else
    {
      _shift(v11, 1);
      *v11 = 48;
      v13 = v11 + 1;
    }
    if ( Size > 0 )
    {
      _shift(v13, 1);
      *v13 = ***(_BYTE ***)(v17 + 188);
      v14 = a1[1];
      v15 = v13 + 1;
      if ( v14 < 0 )
      {
        v16 = -v14;
        if ( a5 || Size >= v16 )
          Size = v16;
        _shift(v15, Size);
        memset(v15, 48, Size);
      }
    }
    if ( v19 )
      *(_DWORD *)(v18 + 112) &= ~2u;
    return 0;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    if ( v19 )
      *(_DWORD *)(v18 + 112) &= ~2u;
    return 22;
  }
}

