// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454960 rf_save_list_a_scroll_from_slider
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl rawX/rawY. 471930 updates slider6F2200 using X/Y;471A30 returns value, explicitly stored FLOAT32. LIVE count486DE0(array6F21AC) minus visible-row
// DWORD6F1F80 wraps32 bits then signed FILD; multiply by rounded slider value and explicitly store productFLOAT32, pass float to455F50 floor core, then605F00 integer conversion.
// Store raw resultDWORD at6F1F9C; negative signed result is replaced by0 IN MEMORY ONLY. Full returnEAX remains original converted result, possibly negative, not final stored offset.
// No upper/count-range clamp, selected-row adjustment, slider finite guard or overflow policy beyond native helpers.
int __cdecl rf_save_list_a_scroll_from_slider(int a1, int a2)
{
  int result; // eax
  float value; // [esp+4h] [ebp-Ch]
  float v4; // [esp+Ch] [ebp-4h]

  rf_ui_slider_update_value_from_pointer((int)unk_6F2200, a1, a2);
  v4 = rf_ui_slider_value_get(unk_6F2200);
  value = (double)(rf_receiver_get_first_dword(dword_6F21AC) - unk_6F1F80) * v4;
  result = (int)rf_floor_float(value);
  unk_6F1F9C = result;
  if ( result < 0 )
    unk_6F1F9C = 0;
  return result;
}

