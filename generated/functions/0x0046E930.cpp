// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E930 rf_ui_modal_action0_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Action0 wrapper: clears modal active first via46E920, then calls nonnull user callback DWORD6F9024 with ZERO explicit arguments. Supplied UI x/y are ignored. Clearing first
// permits callback to create a replacement modal; no post-callback clear.
void rf_ui_modal_action0_dispatch()
{
  rf_ui_modal_clear_active();
  if ( unk_6F9024 )
    unk_6F9024();
}

