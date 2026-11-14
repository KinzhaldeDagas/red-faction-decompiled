// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472FD0 rf_item_models_prepare_materials
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): No arguments. Walks item circular list from DWORD6FB1C4 until sentinel6FAF38, following object next DWORD+652 AFTER each callback. For
// nonnull model pointerDWORD+128 calls564F10 material-preparation delegate. Does not save next before callback, check list/object validity, load models, mutate item flags or perform
// respawn. EAX is path-dependent pointer/delegate residue, not a count.
int rf_item_models_prepare_materials()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = unk_6FB1C4;
  for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
  {
    result = i;
    if ( *(_DWORD *)(i + 128) )
      result = rf_model_handle_prepare_materials_if_nonnull(*(_DWORD **)(i + 128));
  }
  return result;
}

