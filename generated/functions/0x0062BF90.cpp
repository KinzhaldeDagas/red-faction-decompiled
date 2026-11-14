// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062BF90 rf_static_init_liquid_room_transition_registry
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments, plainRET. Push DWORD0 and call549FB0 with ECX=fixed global006FC46C; ignore constructor EAX. Verified shared constructor forraw4-byte
// entries/pointers consumes stack argument viaRET4; capacity0 produces empty12-byte header(count0,capacity0,backingNULL), without seeding elements or freeing an old live backing
// store. Destination ownership is independently established by existing verified RF consumer contracts, not the old locale name. After normal constructor return, call CRT
// atexit6060D2 with exact callback62EFA0, pop4, return full raw atexit EAX. Callback is REGISTERED, not executed by this body. No once guard, own allocation/element
// traversal/prerelease, registration-result test or rollback: initialization remains if registration fails; repeated invocation attempts repeated registration. No locale lookup,
// locale object, language/ctype manipulation or floating operation. This fixed RF-container initialization/cleanup-registration wrapper is RF application code; false library flag
// cleared while all other flags preserved.
int rf_static_init_liquid_room_transition_registry()
{
  rf_dword_array_construct_capacity(unk_6FC46C, 0);
  return atexit(rf_static_cleanup_006fc46c);
}

