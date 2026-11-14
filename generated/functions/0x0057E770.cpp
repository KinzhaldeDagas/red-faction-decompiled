// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E770 rf_renderer_store_auxiliary_byte_18CCFB9
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Recovered cdecl byte input,stores it at global18CCFB9,returns same AL. No readers/xrefs beyond this store currently identified;original meaning unproven. Does not change renderer backend,clip planes or immediate draw state through any call.
unsigned __int8 __cdecl rf_renderer_store_auxiliary_byte_18CCFB9(unsigned __int8 a1)
{
  byte_18CCFB9 = a1;
  return a1;
}

