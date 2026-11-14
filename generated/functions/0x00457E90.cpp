// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00457E90 rf_frontend_float6f23cc_matches_dword6f29c8
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. FLD FLOAT6F23CC, call605F00 integer conversion, compare FULL convertedEAX with DWORD6F29C8; return AL1 on equality elseAL0 through
// SETZCL/MOVAL. ECX is zeroed beforeSETZ, but upperEAX still conversion residue. Not raw float equality, inclusive bound/crossing, or finite test; NaN/out-of-range conversion policy
// remains605F00-owned. No state writes.
bool rf_frontend_float6f23cc_matches_dword6f29c8()
{
  return (int)unk_6F23CC == unk_6F29C8;
}

