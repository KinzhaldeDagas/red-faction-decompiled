// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D44A __cftoe_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Decimal record layout from native accesses:16 bytes
// {int sign at0 (45 means negative),int decimalPoint at4,int conversionStatus at8,char* digits at12}. Cdecl(binary64Pointer,output,unsigned capacity,int precision,int
// uppercase,locale). BEFORE output validation, dereference full8-byte input and call fltout2(value,localRecord,local22byteDigits,22). NULL output/capacity0 ->
// errno22,invalid_parameter(5zeros),22. Sign reserve=(record.sign==45), point reserve=(precision>0). fptostr(output+sign+point,capacity-sign-point or FFFFFFFF sentinel,precision+1
// modulo32,&record). Nonzero digit status clears original output[0], returns status. Otherwise cftoe2_l(output,capacity,precision,uppercase,&record,adjustByte0,locale), returning
// status. No own precision clamp, input NULL guard, capacity-underflow guard before helper or separate locale update. Security cookie checked on normal return; helper validation and
// final suffix-capacity check remain delegated.
int __cdecl _cftoe_l(double *a1, _BYTE *a2, unsigned int a3, int a4, int a5, struct localeinfo_struct *a6)
{
  int result; // eax
  unsigned int v7; // eax
  _DWORD v8[4]; // [esp+Ch] [ebp-2Ch] BYREF
  char v9[24]; // [esp+1Ch] [ebp-1Ch] BYREF

  _fltout2(*a1, v8, v9, 0x16u);
  if ( a2 && a3 )
  {
    if ( a3 == -1 )
      v7 = -1;
    else
      v7 = a3 - (v8[0] == 45) - (a4 > 0);
    result = _fptostr(&a2[(v8[0] == 45) + (a4 > 0)], v7, a4 + 1, v8);
    if ( result )
      *a2 = 0;
    else
      return _cftoe2_l(a2, a3, a4, a5, v8, 0, a6);
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 22;
  }
  return result;
}

