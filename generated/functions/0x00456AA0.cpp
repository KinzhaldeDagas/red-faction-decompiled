// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456AA0 rf_save_list_b_scroll_from_slider
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl rawX/rawY. First clear BYTE6F23D0=0 before any delegate. 471930 updates slider6F2910 using X/Y;471A30 returns value, explicitly stored FLOAT32. LIVE
// count486DE0(array6F26AC) minus visible-row DWORD6F23C8 wraps32 bits then signed FILD; multiply by rounded slider value and explicitly store productFLOAT32, pass float to455F50
// floor core, then605F00 integer conversion. Store raw resultDWORD at6F23E8; negative signed result is replaced by0 IN MEMORY ONLY. Full returnEAX remains original converted result,
// possibly negative, not final stored offset. No upper/count-range clamp, selected-row adjustment, slider finite guard or overflow policy beyond native helpers.
int __cdecl rf_save_list_b_scroll_from_slider(int a1, int a2)
{
  int result; // eax
  float value; // [esp+4h] [ebp-Ch]
  float v4; // [esp+Ch] [ebp-4h]

  byte_6F23D0[0] = 0;
  rf_ui_slider_update_value_from_pointer((int)unk_6F2910, a1, a2);
  v4 = rf_ui_slider_value_get(unk_6F2910);
  value = (double)(rf_receiver_get_first_dword(dword_6F26AC) - unk_6F23C8) * v4;
  result = (int)rf_floor_float(value);
  unk_6F23E8 = result;
  if ( result < 0 )
    unk_6F23E8 = 0;
  return result;
}

