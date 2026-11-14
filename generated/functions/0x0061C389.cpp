// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061C389 crt_x87_divide_st0_by_st1_adapter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 adapter, KEEP library flag. No explicit stack arguments. Reserve44 bytes; originalST0 numeratorN is FSTP80 toslot12, originalST1
// denominatorD next toslot0, then61BDC0, restoreESP/RET. Leaves N/D inST0, consuming two original x87 inputs toone; deeper stack preserved. This is the REVERSED operand arrangement
// of61C376, not same numerator order. Actual result is x87 extended value despite saved void inference. No own finite/zero/exception normalization or game state; core scratch/CW
// semantics remain and EAX is incidental.
void __usercall crt_x87_divide_st0_by_st1_adapter(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-2Ch]
  _TBYTE v3; // [esp+Ch] [ebp-20h]

  *(double *)&v3 = a1;
  *(double *)&v2 = a2;
  crt_x87_divide_ext80_with_pattern_scaling(v2, v3);
}

