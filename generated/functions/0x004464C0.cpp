// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004464C0 rf_ui_top_panel_is11_or18
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, canonicalAL0/1 only. Unconditionally read stack6E6DE8[global depth6615F8], then return1 iff rawID EXACT11 OR
// EXACT18. Negative depth, invalid ID/stack extent and absent session are not guarded; depth-1 addresses adjacent6E6DE4. No scan of older panels, normalization of ID or mutation;
// upperEAX incidental.
bool rf_ui_top_panel_is11_or18()
{
  int v2; // [esp+4h] [ebp-4h]

  v2 = unk_6E6DE8[dword_6615F8];
  return v2 == 11 || v2 == 18;
}

