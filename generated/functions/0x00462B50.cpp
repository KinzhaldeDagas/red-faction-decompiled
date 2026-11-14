// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462B50 rf_browser_scroll_from_slider
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl(x,y). Update slider6F53F0 from pointer,readfloat value;compute (visibleCount6F5088-visibleRows6F508C+1)*value,ROUND TOFLOAT then floor_float and
// ftol2_sse ->scroll6F52E4. Unlike level-list slider45B660,this explicitly FLOORS instead of direct truncation. Signed clamp in place to0..(visibleCount-visibleRows) WITHOUT
// max(0,upper);then explicit ifscroll<0 set0 repairs possible negative upper-bound result. Native lower-first clamp delegate semantics preserved. No selected-row/list/query
// update,sound or own finite/overflow guard;return clamp pointer residue.
_DWORD *__cdecl rf_browser_scroll_from_slider(int a1, int a2)
{
  _DWORD *result; // eax
  float value; // [esp+4h] [ebp-Ch]
  float v4; // [esp+Ch] [ebp-4h]

  rf_ui_slider_update_value_from_pointer((int)unk_6F53F0, a1, a2);
  v4 = rf_ui_slider_value_get(unk_6F53F0);
  value = (double)(int)(MEMORY[0x6F5088] - unk_6F508C + 1) * v4;
  dword_6F52E4 = (int)rf_floor_float(value);
  result = rf_integer_clamp_in_place(&dword_6F52E4, 0, MEMORY[0x6F5088] - unk_6F508C);
  if ( dword_6F52E4 < 0 )
    dword_6F52E4 = 0;
  return result;
}

