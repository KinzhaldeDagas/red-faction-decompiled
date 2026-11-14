// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004460D0 rf_ui_get_raw_panel_byte6E6D94
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Load raw BYTE6E6D94 intoAL only, without normalization or clearing upperEAX. No state change, panel lookup, stack
// validation or modal activation.
char rf_ui_get_raw_panel_byte6E6D94()
{
  return unk_6E6D94;
}

