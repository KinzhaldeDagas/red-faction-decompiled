// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F8A0 rf_ui_modal_active_byte_get
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Returns raw active BYTE6F8C84 in AL only; upper EAX is not cleared or normalized. No state change.
char rf_ui_modal_active_byte_get()
{
  return unk_6F8C84;
}

