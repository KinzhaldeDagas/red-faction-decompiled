// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E950 rf_ui_modal_action1_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Action1 wrapper: clears modal active first via46E920, then calls nonnull user callback DWORD6F906C with ZERO explicit arguments. Supplied UI x/y are ignored; replacement
// modal created by callback remains active.
void rf_ui_modal_action1_dispatch()
{
  rf_ui_modal_clear_active();
  if ( unk_6F906C )
    unk_6F906C();
}

