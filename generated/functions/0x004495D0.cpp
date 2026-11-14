// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004495D0 rf_destroy_two_global_models_and_clear_handles
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void/incidental EAX. Test globalDWORD87C6DC for ANYnonzero, not signed-positive; admitted raw value goes to564280
// cdecl model-destroy adapter, then overwrite global87C6DC=0 AFTER callback. Next independently read87C6E0 and apply same nonzero destroy-then-zero sequence. Negative/all-ones bit
// patterns are admitted, no validity/type/ownership check or duplicate-handle deduplication. Second field is not captured before first callback; callbacks changing either field
// retain native ordering, and first callback's replacement of its own global is overwritten with0. No allocation free of containing globals, aggregate success or rollback.
void __cdecl rf_destroy_two_global_models_and_clear_handles()
{
  if ( dword_87C6DC )
  {
    rf_model_handle_destroy_cdecl_adapter((_DWORD *)dword_87C6DC);
    dword_87C6DC = 0;
  }
  if ( dword_87C6E0 )
  {
    rf_model_handle_destroy_cdecl_adapter((_DWORD *)dword_87C6E0);
    dword_87C6E0 = 0;
  }
}

