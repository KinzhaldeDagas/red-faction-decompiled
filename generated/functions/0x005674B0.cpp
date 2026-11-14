// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005674B0 rf_rsqrt_fast_lookup_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): stdcall one float bit word,RET4; floating ST0 result. b=inputIEEEbits,index=(b>>14)&1023,e=b&7F800000. Constructs output bits=table1807938[index] OR (((BE000000-e) modulo2^32 >>1 LOGICALLY)&7F800000). No Newton refinement,sign propagation,zero/negative/NaN/Inf guard or table initialization here. Requires567600-populated lookup table; special table sample1 uses mantissa007FE000 rather than exact1 output.
double __stdcall rf_rsqrt_fast_lookup_unchecked(float x)
{
  return COERCE_FLOAT(dword_1807938[(LODWORD(x) >> 14) & 0x3FF] | ((-1107296256 - (LODWORD(x) & 0x7F800000u)) >> 1)
                                                                & 0x7F800000);
}

