// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061C5B1 crt_x87_divide_st0_by_st1_preserve_eax
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 adapter, KEEP library flag. Save fullEAX, reserve44bytes; spill originalST0 NUMERATOR to80-bit slot12, originalST1 DENOMINATOR toslot0,
// call61BDC0, releasearea andrestore originalEAX beforeRET. Return quotient inST0, net x87 depth-1; deeper entries preserved. Reverse of61C59C, EAX preservation is explicit. No stack
// arguments/own FP policy/game state; core's private-workspace and environment effects remain, saved void inference is not a claim of no x87 result.
void __usercall crt_x87_divide_st0_by_st1_preserve_eax(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-30h]
  _TBYTE v3; // [esp+Ch] [ebp-24h]

  *(double *)&v3 = a1;
  *(double *)&v2 = a2;
  crt_x87_divide_ext80_with_pattern_scaling(v2, v3);
}

