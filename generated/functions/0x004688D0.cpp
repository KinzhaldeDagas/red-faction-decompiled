// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004688D0 rf_controls_scroll_actions_from_slider
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(x,y). Update/read vertical slider6F6428;compute (actionCount-visibleRows+1)*floatValue,round product to binary32 BEFORE floor_float/ftol2_sse into
// scroll6F62B8. Clamp scroll signed0..max(0,actionCount-visibleRows). Unlike arrow/ensure-visible routines,this handles negative upper difference via max0. No
// selected-action,capture,sound or save;existing pointer return is clamp delegate residue.
_DWORD *__cdecl rf_controls_scroll_actions_from_slider(int a1, int a2)
{
  int v2; // eax
  float value; // [esp+4h] [ebp-Ch]
  float v5; // [esp+Ch] [ebp-4h]

  rf_ui_slider_update_value_from_pointer((int)unk_6F6428, a1, a2);
  v5 = rf_ui_slider_value_get(unk_6F6428);
  value = (double)(unk_6F62AC - unk_6F62A8 + 1) * v5;
  dword_6F62B8 = (int)rf_floor_float(value);
  v2 = rf_int_max(0, unk_6F62AC - unk_6F62A8);
  return rf_integer_clamp_in_place(&dword_6F62B8, 0, v2);
}

