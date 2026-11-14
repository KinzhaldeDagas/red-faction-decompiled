// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046DFC0 rf_persona_history_scroll_slider_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl slider press/drag(x,y). Sets capture BYTE6F89B5=1 and updates slider from pointer. Stores binary32(1-sliderValue), then binary32(range6F898C*that); floors result to
// signed integer distance and sets target=distance+clipHeight. Starts viewoffset=historyCount-1; index=newest-offset, negative replaced with EXACT79; dereferences entry height SIGNED
// WORD+0x106 without null check. Remembers distance<=that height. While remaining height<target, invokes Up(0,0), recomputes height, and if height==clipHeight+range OR remembered
// flag with height>target, invokes Down(0,0) and stops. Finally updates slider again from original pointer, overriding intermediate normalized slider settings while preserving chosen
// offset. No own empty-count, invalid-height, zero-range or loop-saturation guard.
int __cdecl rf_persona_history_scroll_slider_pointer(int a1, int a2)
{
  float value; // [esp+4h] [ebp-20h]
  float v4; // [esp+8h] [ebp-1Ch]
  int v5; // [esp+Ch] [ebp-18h]
  int v6; // [esp+14h] [ebp-10h]
  char v7; // [esp+1Bh] [ebp-9h]
  int index; // [esp+1Ch] [ebp-8h]
  int v9; // [esp+20h] [ebp-4h]

  byte_6F89B5[0] = 1;
  rf_ui_slider_update_value_from_pointer((int)unk_6F8A08, a1, a2);
  v4 = 1.0 - rf_ui_slider_value_get(unk_6F8A08);
  value = (double)dword_6F898C * v4;
  v6 = (int)rf_floor_float(value);
  v5 = v6 + dword_6F8974;
  dword_6F899C = rf_persona_history_get_count() - 1;
  v7 = 0;
  index = rf_persona_history_get_newest_index() - dword_6F899C;
  if ( index < 0 )
    index = 79;
  if ( v6 <= rf_persona_history_entry_at(index)->layout_height )
    v7 = 1;
  v9 = rf_persona_history_remaining_layout_height();
  while ( v9 < v5 )
  {
    rf_persona_history_scroll_up();
    v9 = rf_persona_history_remaining_layout_height();
    if ( v9 == dword_6F8974 + dword_6F898C || v7 && v9 > v5 )
    {
      rf_persona_history_scroll_down();
      return rf_ui_slider_update_value_from_pointer((int)unk_6F8A08, a1, a2);
    }
  }
  return rf_ui_slider_update_value_from_pointer((int)unk_6F8A08, a1, a2);
}

