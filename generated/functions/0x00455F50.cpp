// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455F50 rf_floor_float
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one float. Copies input through x87 to a32-bit outgoing slot then calls455F70 and forwards ST0, removing4 outgoing bytes. Fresh455F70 widens the input
// to a64-bit outgoing argument for CRT floor, then explicitly FSTPs the result to32-bit local and reloads ST0. No additional rounding-mode changes, finite checks or error policy in
// outer wrapper; generic math adapter retains library classification.
float __cdecl rf_floor_float(float value)
{
  return rf_floor_float_core(value);
}

