// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004680C0 rf_controls_sensitivity_from_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(x,y). Update sensitivity slider6F6730 from pointer,read value via x87 ST0,and store binary32 into unchecked localPlayer+228(E4). No own
// playerNULL/finite/value-range guard,configuration save,sound or capture/pane gate;slider owns clamp. Existing int return incidental EAX,actual sensitivity transferred via x87.
int __cdecl rf_controls_sensitivity_from_pointer(int a1, int a2)
{
  int result; // eax

  rf_ui_slider_update_value_from_pointer((int)unk_6F6730, a1, a2);
  *(float *)(rf_local_fpgun_player + 228) = rf_ui_slider_value_get(unk_6F6730);
  return result;
}

