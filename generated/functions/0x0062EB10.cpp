// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EB10 rf_static_cleanup_00666ff0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 6-instruction/15-byte body independently matched to original PE. No consumed arguments, plain RET. Set ECX to FIXED global receiver00666FF0,
// call0057E410(rf_bitset_destroy) once, then return without further EAX assignment. Exact static receiver, not an incoming object or pointer loaded FROM that address. Registered with
// atexit by original PUSH at0x00629A47. Wrapper adds no NULL/ready/count guard, allocation, outer-object delete, count/header reset or unwind frame; cleanup ownership remains the
// verified callee contract. Returned EAX is delegate residue, not a promised success status.
int rf_static_cleanup_00666ff0()
{
  return rf_bitset_destroy(dword_666FF0);
}

