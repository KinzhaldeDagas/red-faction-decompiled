// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061C376 crt_x87_divide_st1_by_st0_adapter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 adapter, KEEP library flag. Incoming original ST0 is denominatorD, ST1 numeratorN; no explicit stack arguments. Reserve44 bytes, FSTP80 D
// toworkspace0 then FSTP80 N to12; call61BDC0; restoreESP andRET, leaving quotient N/D inST0 (net x87 depth decreases1, deeper entries preserved). Result is x87 extended value,
// despite saved void usercall inference. No F64 rounding spill, own validation/status handling or application mutation. Core owns private memory scaling and CW behavior; EAX is its
// scratch residue, not defined application return. Stored prototype retained rather than forcing an unproven high-level extended format.
void __usercall crt_x87_divide_st1_by_st0_adapter(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-2Ch]
  _TBYTE v3; // [esp+Ch] [ebp-20h]

  *(double *)&v2 = a1;
  *(double *)&v3 = a2;
  crt_x87_divide_ext80_with_pattern_scaling(v2, v3);
}

