// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B910 rf_gameplay_priority_scroll_from_slider
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(x,y). Update/read slider6F7D58;compute(count6F7B7C-visibleRows6F7B68+1)*value,round product tobinary32 BEFORE floor_float/ftol2_sse
// ->scroll6F7B84. Clamp signed scroll0..max(0,count-visibleRows). No selected index change,swap,sound,save or own finite check. Return clamp pointer residue.
_DWORD *__cdecl rf_gameplay_priority_scroll_from_slider(int a1, int a2)
{
  int v2; // eax
  float value; // [esp+4h] [ebp-Ch]
  float v5; // [esp+Ch] [ebp-4h]

  rf_ui_slider_update_value_from_pointer((int)unk_6F7D58, a1, a2);
  v5 = rf_ui_slider_value_get(unk_6F7D58);
  value = (double)(unk_6F7B7C - unk_6F7B68 + 1) * v5;
  dword_6F7B84 = (int)rf_floor_float(value);
  v2 = rf_int_max(0, unk_6F7B7C - unk_6F7B68);
  return rf_integer_clamp_in_place(&dword_6F7B84, 0, v2);
}

