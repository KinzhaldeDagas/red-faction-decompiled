// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004461B0 rf_ui_pending_panel_id_get
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Return raw DWORD6E6DE0 fullEAX; no current/previous panel lookup, validation, normalization, mutation or side
// effect. Zero has pending-sentinel meaning only in its consumers, not a Boolean conversion here.
int rf_ui_pending_panel_id_get()
{
  return unk_6E6DE0;
}

