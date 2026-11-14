// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455F70 rf_floor_float_core
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one float. Loads32-bit input then reserves8 outgoing bytes and stores it as64-bit double for CRT floor at455F7D. Removes8 bytes, explicitly FSTPs
// result to32-bit local and reloads ST0 before normal return. This is the input-widening/result-float-rounding core beneath455F50, with no finite/domain guard, x87 control-word
// change, or separate errno handling in its own body.
float __cdecl rf_floor_float_core(float value)
{
  return floor(value);
}

