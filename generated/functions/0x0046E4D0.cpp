// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E4D0 rf_persona_history_process_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): History input frame. Escape scan1 OR nonnull localPlayer action21 via451F70(player+228,21,NULL) focuses Close(index1), invokes virtual+4 with ECX=this/no explicit arguments,
// then requests panel close. DOES NOT return: Down scan208/action12, else Up scan200/action11 still runs. Scroll keys focus scroll meta(index0), invoke virtual+4, and repeat only
// when200ms deadline elapsed OR unarmed, rearming before Down/Up(0,0). If neither scroll key/action, reads absolute mouse and calls46E6D0(x,y). Action helpers receive embedded
// player+228. No own active/suppress-input gate; renderer controls entry.
void rf_persona_history_process_input()
{
  _DWORD *v0; // eax
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  int v3; // [esp+Ch] [ebp-8h] BYREF
  int v4; // [esp+10h] [ebp-4h] BYREF

  if ( rf_input_get_scan_code_state_byte(1)
    || rf_local_fpgun_player && rf_input_binding_poll_pressed_or_held(rf_local_fpgun_player + 228, 21, nullptr) )
  {
    unk_6F89B8 = 1;
    v0 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, 1);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v0 + 4))(*v0);
    rf_persona_history_request_close();
  }
  if ( rf_input_get_scan_code_state_byte(208)
    || rf_local_fpgun_player && rf_input_binding_poll_pressed_or_held(rf_local_fpgun_player + 228, 12, nullptr) )
  {
    unk_6F89B8 = 0;
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, 0);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 4))(*v1);
    if ( rf_clock_deadline_has_elapsed_half_period(&dword_6F8A04) || !rf_timestamp_is_armed_nonnegative(&dword_6F8A04) )
    {
      rf_clock_deadline_set_wrapped_offset(&dword_6F8A04, 200);
      rf_persona_history_scroll_down();
    }
  }
  else if ( rf_input_get_scan_code_state_byte(200)
         || rf_local_fpgun_player && rf_input_binding_poll_pressed_or_held(rf_local_fpgun_player + 228, 11, nullptr) )
  {
    unk_6F89B8 = 0;
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, 0);
    (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
    if ( rf_clock_deadline_has_elapsed_half_period(&dword_6F8A04) || !rf_timestamp_is_armed_nonnegative(&dword_6F8A04) )
    {
      rf_clock_deadline_set_wrapped_offset(&dword_6F8A04, 200);
      rf_persona_history_scroll_up();
    }
  }
  else
  {
    rf_mouse_get_absolute_state(&v3, &v4, &unk_193A03C);
    rf_persona_history_process_pointer(v3, v4);
  }
}

