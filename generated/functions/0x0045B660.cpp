// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B660 rf_multiplayer_level_scroll_from_slider
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(x,y). First update slider6F3740 from pointer coordinates471930,then read its float52. Store
// scrollDWORD6F2D04=truncTowardZero((levelCount6F2DC4-visibleRows6F2CF0+1)*sliderValue),then signed clamp in place to0..max(0,levelCount-visibleRows). The +1 exists only in initial
// scaling,not final maximum. No current-row/rotation mutation,sound or explicit finite/overflow admission;slider delegates own value mapping/clamp. Return clamp pointer residue,not
// row count.
_DWORD *__cdecl rf_multiplayer_level_scroll_from_slider(int a1, int a2)
{
  int first_dword; // eax
  int v3; // eax
  float v5; // [esp+4h] [ebp-4h]

  rf_ui_slider_update_value_from_pointer((int)flt_6F3740, a1, a2);
  v5 = rf_ui_slider_value_get(flt_6F3740);
  dword_6F2D04 = (int)((double)(rf_receiver_get_first_dword(&unk_6F2DC4) - unk_6F2CF0 + 1) * v5);
  first_dword = rf_receiver_get_first_dword(&unk_6F2DC4);
  v3 = rf_int_max(0, first_dword - unk_6F2CF0);
  return rf_integer_clamp_in_place(&dword_6F2D04, 0, v3);
}

