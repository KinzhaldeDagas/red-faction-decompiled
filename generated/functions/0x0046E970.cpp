// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E970 rf_ui_modal_action2_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Action2 wrapper: clears modal active first via46E920, then calls nonnull user callback DWORD6F90B4 with ZERO explicit arguments. Supplied UI x/y are ignored; replacement
// modal created by callback remains active.
void rf_ui_modal_action2_dispatch()
{
  rf_ui_modal_clear_active();
  if ( unk_6F90B4 )
    unk_6F90B4();
}

