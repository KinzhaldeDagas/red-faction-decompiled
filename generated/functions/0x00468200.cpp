// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468200 rf_controls_reset_bindings_and_mouse_defaults
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg,Yes-confirm callback. For signed i0..<actionCount6F62AC:copy localPlayer WORD240+28*i default key ->WORD260+28*i current key,and WORD244+28*i default mouse
// ->WORD264+28*i current mouse. No clamp to physical128 slots/dedup. Copy playerBYTE3853 default inversion->3845/current checkbox6F68B8. Force sensitivityFLOAT228=original binary32
// constant0.2 (not read from per-player defaults),load slider6F6730. No playerNULL/count bounds,save,selected-action/scroll/capture reset or sound. Raw default WORD values retained.
void rf_controls_reset_bindings_and_mouse_defaults()
{
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < unk_6F62AC; ++i )
  {
    *(_WORD *)(rf_local_fpgun_player + 28 * i + 260) = *(_WORD *)(rf_local_fpgun_player + 28 * i + 240);
    *(_WORD *)(rf_local_fpgun_player + 28 * i + 264) = *(_WORD *)(rf_local_fpgun_player + 28 * i + 244);
  }
  *(_BYTE *)(rf_local_fpgun_player + 3845) = *(_BYTE *)(rf_local_fpgun_player + 3853);
  byte_6F68B8[0] = *(_BYTE *)(rf_local_fpgun_player + 3845);
  *(float *)(rf_local_fpgun_player + 228) = 0.2;
  rf_ui_slider_set_value_clamped(unk_6F6730, *(float *)(rf_local_fpgun_player + 228));
}

