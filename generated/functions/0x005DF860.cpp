// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF860 rf_float32_as_uint32_bits
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, immediate vertex conversion, face-list lighting, bump-stage calls and original PE bytes): Cdecl4-byte argument returned by MOV intoEAX unchanged. Only observed callers are the six bump-environment setter writes5D4270;corrected signature float input,uint32 output models exact IEEE bitcast,not numeric conversion. No x87/SSE arithmetic,rounding,NaN canonicalization or pointer dereference;all32 input bits preserved.
unsigned int __cdecl rf_float32_as_uint32_bits(float a1)
{
  return LODWORD(a1);
}

