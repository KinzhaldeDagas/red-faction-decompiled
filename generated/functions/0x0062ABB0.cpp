// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062ABB0 rf_static_init_multiplayer_filtered_level_pairs
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments, plainRET. Push DWORD0 and call45E2A0 with ECX=fixed global006F2DC4; ignore constructor EAX. Verified shared constructor for16-byte two-RFString
// elements consumes stack argument viaRET4; capacity0 produces empty12-byte header(count0,capacity0,backingNULL), without seeding elements or freeing an old live backing store.
// Destination ownership is independently established by existing verified RF consumer contracts, not the old locale name. After normal constructor return, call CRT atexit6060D2 with
// exact callback62ED10, pop4, return full raw atexit EAX. Callback is REGISTERED, not executed by this body. No once guard, own allocation/element traversal/prerelease,
// registration-result test or rollback: initialization remains if registration fails; repeated invocation attempts repeated registration. No locale lookup, locale object,
// language/ctype manipulation or floating operation. This fixed RF-container initialization/cleanup-registration wrapper is RF application code; false library flag cleared while all
// other flags preserved.
int rf_static_init_multiplayer_filtered_level_pairs()
{
  rf_two_rfstring_array16_construct((char *)dword_6F2DC4, 0);
  return atexit(rf_static_cleanup_006f2dc4);
}

