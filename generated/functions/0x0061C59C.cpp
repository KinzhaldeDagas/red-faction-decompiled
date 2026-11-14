// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061C59C crt_x87_divide_st1_by_st0_preserve_eax
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 adapter, KEEP library flag. PUSH saves full incomingEAX, reserve44-byte private area, spill originalST0 denominator to80-bit slot0 then
// originalST1 numerator toslot12, call61BDC0, releasearea, POP restores ORIGINAL fullEAX, RET. Normal x87 resultST0=numerator/denominator, net twoinputs->one, deeper stack preserved.
// EAX is preserved, not numeric division/status return. Core handles scaling/CW; no own argument/finite/error gate, allocation or game state. Saved void usercall does not express the
// actual ST0 quotient; no forced format/type correction is adopted.
void __usercall crt_x87_divide_st1_by_st0_preserve_eax(double a1@<st1>, double a2@<st0>)
{
  _TBYTE v2; // [esp+0h] [ebp-30h]
  _TBYTE v3; // [esp+Ch] [ebp-24h]

  *(double *)&v2 = a1;
  *(double *)&v3 = a2;
  crt_x87_divide_ext80_with_pattern_scaling(v2, v3);
}

