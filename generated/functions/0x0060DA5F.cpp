// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DA5F __cftog_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Decimal record layout from native accesses:16 bytes
// {int sign at0 (45 means negative),int decimalPoint at4,int conversionStatus at8,char* digits at12}. Cdecl(binary64Pointer,output,unsigned capacity,int significantPrecision,int
// uppercase,locale). fltout2 into local record/22-byte digits BEFORE output validation. NULL output/capacity0 -> errno22,invalid_parameter5zeros,22. Save pre-round
// exponent=decimalPoint-1; fptostr(output+sign,capacity-sign or FFFFFFFF,significantPrecision,&record). Failure clears original output/returns status. With UPDATED rounded exponent:
// if exponent<-4 OR exponent>=precision, call cftoe2_l(...,precision,uppercase,&record,adjustByte1,locale). Otherwise fixed path: if exponent increased during rounding, remove final
// digit by scanning to NUL and setting preceding byte0; call cftof2_l(recordEAX,outputECX,capacity,precision,adjustByte1,locale). No own conversion-code check, precision
// normalization, special-value switch or final cropzeros call. Cookie checked on normal return; layout/error semantics delegated.
int __cdecl _cftog_l(_DWORD *a1, char *a2, unsigned int a3, int Size, int a5, struct localeinfo_struct *a6)
{
  int result; // eax
  unsigned int v7; // ecx
  BOOL v8; // eax
  char *v9; // edi
  int v10; // [esp+Ch] [ebp-30h] BYREF
  int v11; // [esp+10h] [ebp-2Ch]
  int v12; // [esp+1Ch] [ebp-20h]
  char v13[24]; // [esp+20h] [ebp-1Ch] BYREF

  _fltout2(*(double *)a1, &v10, v13, 0x16u);
  if ( a2 && (v7 = a3) != 0 )
  {
    v12 = v11 - 1;
    v8 = v10 == 45;
    v9 = &a2[v8];
    if ( a3 != -1 )
      v7 = a3 - v8;
    result = _fptostr(v9, v7, Size, &v10);
    if ( result )
    {
      *a2 = 0;
    }
    else if ( v11 - 1 < -4 || v11 - 1 >= Size )
    {
      return _cftoe2_l(a2, a3, Size, a5, &v10, 1, a6);
    }
    else
    {
      if ( v12 < v11 - 1 )
        v9[strlen(v9) - 1] = 0;
      return _cftof2_l(&v10, a2, a3, Size, 1, a6);
    }
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  return result;
}

