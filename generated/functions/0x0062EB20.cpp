// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EB20 rf_static_cleanup_006807d4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 6-instruction/15-byte body independently matched to original PE. No consumed arguments, plain RET. Set ECX to FIXED global receiver006807D4,
// call0055F6D0(rf_string_destroy_buffer) once, then return without further EAX assignment. Exact static receiver, not an incoming object or pointer loaded FROM that address.
// Registered with atexit by original PUSH at0x00414894. Wrapper adds no NULL/ready/count guard, allocation, outer-object delete, count/header reset or unwind frame; cleanup ownership
// remains the verified callee contract. Returned EAX is delegate residue, not a promised success status. Delegate destroys RFString buffer at receiver+4 when nonnull and clears that
// pointer while preserving stored extent; containing static RFString remains allocated.
void __cdecl rf_static_cleanup_006807d4()
{
  rf_string_destroy_buffer(dword_6807D4);
}

