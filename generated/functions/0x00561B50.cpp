// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561B50 rf_pool17F1120_optional_noop_hook
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): When global1809818 nonzero, passes global pool17F1120 in ECX to4BE0E0, whose instructions return0 without object reads/writes. Disabled path leaves EAX unspecified. No pool reset, allocation or release in this wrapper.
void __cdecl rf_pool17F1120_optional_noop_hook()
{
  if ( dword_1809818 )
    rf_hook_4BE0E0_return_zero();
}

