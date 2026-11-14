// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062F370 rf_static_cleanup_0088e4fc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 6-instruction/15-byte body independently matched to original PE. No consumed arguments, plain RET. Set ECX to FIXED global receiver0088E4FC,
// call00592030(rf_command_line_option_destruct_argument_and_unlink) once, then return without further EAX assignment. Exact static receiver, not an incoming object or pointer loaded
// FROM that address. Registered with atexit by original PUSH at0x0062D1C9. Wrapper adds no NULL/ready/count guard, allocation, outer-object delete, count/header reset or unwind
// frame; cleanup ownership remains the verified callee contract. Returned EAX is delegate residue, not a promised success status. Delegate destroys owned argument+16 and
// conditionally unlinks named option; does not free static receiver or borrowed name. Wrapper has no repeated-destruction guard.
void **rf_static_cleanup_0088e4fc()
{
  return rf_command_line_option_destruct_argument_and_unlink((void **)byte_88E4FC);
}

