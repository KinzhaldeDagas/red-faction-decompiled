// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004680F0 rf_controls_toggle_mouse_y_invert
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Noarg. Normalize logical-not checkboxBYTE6F68B8 (any nonzero->0,zero->1),copy into unchecked localPlayerBYTE3845(F05). Newtrue sound44,newfalse45. Native Mouse Y
// Invert builder fallback/binding verified. No write to default inversionBYTE3853,save,capture-state reset or runtime gate.
int rf_controls_toggle_mouse_y_invert()
{
  byte_6F68B8[0] = byte_6F68B8[0] == 0;
  *(_BYTE *)(rf_local_fpgun_player + 3845) = byte_6F68B8[0];
  if ( byte_6F68B8[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

