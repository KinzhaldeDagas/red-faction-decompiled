// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E6D0 rf_persona_history_process_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl history pointer frame(x,y). Releases capture6F89B5 when left button is not HELD. Unless captured, hit-tests focus list6F8C08 into cached hit6F89BC; capture retains
// cached hit. Miss sets focus6F89B8=-1. Valid hit with left HELD and elapsed/unarmed200ms repeat timer rearms, changes focus with sound42 when needed, and invokes nonnull focused+32
// callback with TWO(x,y). Otherwise only nonzero relative mouse motion permits held-left nonnull hit+36 drag callback, then focus-change/sound42. There is no click sound43 here.
// Always invokes EVERY focus control virtual+8 with ECX=this/no stack arguments, then focused virtual+4 if focus!=-1. No fresh bounds/active recheck after callbacks.
int __cdecl rf_persona_history_process_pointer(int physical_x, int physical_y)
{
  char *v2; // eax
  int v3; // eax
  int v4; // eax
  int result; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // eax
  int first_dword; // [esp+4h] [ebp-18h]
  int i; // [esp+10h] [ebp-Ch]
  int v10; // [esp+14h] [ebp-8h] BYREF
  int v11; // [esp+18h] [ebp-4h] BYREF

  if ( !rf_mouse_get_button_held_byte(0) )
    byte_6F89B5[0] = 0;
  if ( !byte_6F89B5[0] )
  {
    first_dword = rf_receiver_get_first_dword(unk_6F8C08);
    v2 = rf_receiver_plus4_address_458010((char *)unk_6F8C08);
    dword_6F89BC = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v2, first_dword);
  }
  if ( dword_6F89BC < 0 )
  {
    dword_6F89B8 = -1;
  }
  else if ( rf_mouse_get_button_held_byte(0)
         && (rf_clock_deadline_has_elapsed_half_period(&dword_6F8A04)
          || !rf_timestamp_is_armed_nonnegative(&dword_6F8A04)) )
  {
    rf_clock_deadline_set_wrapped_offset(&dword_6F8A04, 200);
    if ( dword_6F89B8 != dword_6F89BC )
    {
      dword_6F89B8 = dword_6F89BC;
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
    }
    if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, dword_6F89B8) + 32) )
    {
      v3 = rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, dword_6F89B8);
      (*(void (__cdecl **)(int, int))(*(_DWORD *)v3 + 32))(physical_x, physical_y);
    }
  }
  else
  {
    rf_mouse_get_relative_deltas(&v11, &v10, &unk_193A03C);
    if ( v11 || v10 )
    {
      if ( rf_mouse_get_button_held_byte(0)
        && *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, dword_6F89BC) + 36) )
      {
        v4 = rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, dword_6F89BC);
        (*(void (__cdecl **)(int, int))(*(_DWORD *)v4 + 36))(physical_x, physical_y);
      }
      if ( dword_6F89B8 != dword_6F89BC )
      {
        dword_6F89B8 = dword_6F89BC;
        rf_gamesound_play_event(42, 0, 0.0, 1.0);
      }
    }
  }
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_6F8C08);
    if ( i >= result )
      break;
    v6 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, i);
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v6 + 8))(*v6);
  }
  if ( dword_6F89B8 != -1 )
  {
    v7 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8C08, dword_6F89B8);
    return (*(int (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v7 + 4))(*v7, *v7);
  }
  return result;
}

