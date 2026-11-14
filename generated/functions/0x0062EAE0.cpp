// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EAE0 rf_static_cleanup_00666d18
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 6-instruction/15-byte body independently matched to original PE. No consumed arguments, plain RET. Set ECX to FIXED global receiver00666D18,
// call004175E0(rf_clutter_runtime_destroy_members) once, then return without further EAX assignment. Exact static receiver, not an incoming object or pointer loaded FROM that
// address. Registered with atexit by original PUSH at0x006299ED. Wrapper adds no NULL/ready/count guard, allocation, outer-object delete, count/header reset or unwind frame; cleanup
// ownership remains the verified callee contract. Returned EAX is delegate residue, not a promised success status.
void rf_static_cleanup_00666d18()
{
  rf_clutter_runtime_destroy_members((void **)&unk_666D18);
}

