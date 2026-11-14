// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EE70 rf_static_cleanup_006f88f4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 6-instruction/15-byte body independently matched to original PE. No consumed arguments, plain RET. Set ECX to FIXED global receiver006F88F4,
// call004580D0(rf_shared_noop_destructor_4580d0) once, then return without further EAX assignment. Exact static receiver, not an incoming object or pointer loaded FROM that address.
// Registered with atexit by original PUSH at0x0062BB2D. Wrapper adds no NULL/ready/count guard, allocation, outer-object delete, count/header reset or unwind frame; cleanup ownership
// remains the verified callee contract. Returned EAX is delegate residue, not a promised success status. Callee is a plain no-op: it ignores supplied ECX, touches no
// object/resource/array header and preserves incoming EAX. This adapter therefore performs NO resource release; static registration does not imply cleanup.
void rf_static_cleanup_006f88f4()
{
  rf_shared_noop_destructor_4580d0();
}

