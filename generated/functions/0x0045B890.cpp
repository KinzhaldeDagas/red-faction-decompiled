// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B890 rf_multiplayer_level_rotation_remove_all
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Delegate pointer_array_release_storage on selected-index array6F2E64. Clears/releases selection storage
// according to verified generic helper,not filtered/master level records. No current-row/scroll adjustment,redraw,sound or registry write here. Return delegate pointer
// residue;distinct from add-all which retains existing entries.
void **rf_multiplayer_level_rotation_remove_all()
{
  return rf_pointer_array_release_storage((void **)unk_6F2E64);
}

