// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FA80 rf_demo_upsell_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl FULL-DWORD key. Any nonzero value attempts throttled advance46FA30. Always calls rf_input_reset_all_key_and_event_state, including key0. No key filtering, own index
// bound or readiness check.
void __cdecl rf_demo_upsell_handle_key(int a1)
{
  if ( a1 )
    rf_demo_upsell_advance_if_ready();
  rf_input_reset_all_key_and_event_state();
}

