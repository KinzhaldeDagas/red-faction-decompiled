// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D9A4 __cftof_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Decimal record layout from native accesses:16 bytes
// {int sign at0 (45 means negative),int decimalPoint at4,int conversionStatus at8,char* digits at12}. Cdecl(binary64Pointer,output,unsigned capacity,int fractionalPrecision,locale);
// corrected unsigned-capacity/signed-precision types. Dereference input and fltout2 to local record/22-byte digit buffer BEFORE output validation. NULL output/capacity0 ->
// errno22,invalid_parameter5zeros,22. fptostr(output+(sign==45),capacity-sign or FFFFFFFF sentinel,fractionalPrecision+decimalPoint modulo32,&record). Failure clears original
// output,returns status. Success cftof2_l(recordEAX,outputECX,capacity,precision,adjustByte0,locale),returns status. No own input guard, precision clamp,
// addition-overflow/capacity-underflow check or locale snapshot. Final layout helper only tests nonzero capacity, so this wrapper does not prove capacity for all later inserted
// leading zeros/point. Cookie checked on normal return.
int __cdecl _cftof_l(_DWORD *a1, char *a2, unsigned int a3, int Size, struct localeinfo_struct *a5)
{
  int result; // eax
  unsigned int v6; // eax
  _DWORD v7[4]; // [esp+Ch] [ebp-2Ch] BYREF
  char v8[24]; // [esp+1Ch] [ebp-1Ch] BYREF

  _fltout2(*(double *)a1, v7, v8, 0x16u);
  if ( a2 && (v6 = a3) != 0 )
  {
    if ( a3 != -1 )
      v6 = a3 - (v7[0] == 45);
    result = _fptostr(&a2[v7[0] == 45], v6, Size + v7[1], v7);
    if ( result )
      *a2 = 0;
    else
      return _cftof2_l(v7, a2, a3, Size, 0, a5);
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  return result;
}

