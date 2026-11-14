// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046EAD0 rf_ui_modal_process_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Modal pointer frame: absolute mouse hit-tests focus list6F8F84, requiring hit>=0 and control BYTE9 nonzero. On left PRESS-count, invokes nonnull control+32 callback with
// TWO(x,y), then sound43; native ADD ESP,4 after callback reuses remaining stack slot for float gain1.0, not a third callback argument. Stores focus6F8C80=original hit AFTER
// callback, even if it created another modal. Without press, nonzero relative motion assigns focus before comparing it to hit; comparison is therefore equal and normal hover sound42
// is unreachable. Does not update virtual control state or recheck active.
int rf_ui_modal_process_pointer()
{
  char *v0; // eax
  int result; // eax
  int v2; // eax
  int v3; // [esp+0h] [ebp-1Ch]
  int first_dword; // [esp+4h] [ebp-18h]
  int v5; // [esp+8h] [ebp-14h] BYREF
  int v6; // [esp+Ch] [ebp-10h] BYREF
  int physical_x; // [esp+10h] [ebp-Ch] BYREF
  int physical_y; // [esp+14h] [ebp-8h] BYREF
  int v9; // [esp+18h] [ebp-4h]

  rf_mouse_get_absolute_state(&physical_x, &physical_y, &unk_193A03C);
  first_dword = rf_receiver_get_first_dword(unk_6F8F84);
  v0 = rf_receiver_plus4_address_458010((char *)unk_6F8F84);
  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)v0, first_dword);
  v9 = result;
  if ( result >= 0 )
  {
    result = *(unsigned __int8 *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, v9) + 9);
    if ( result )
    {
      if ( rf_mouse_button_has_press_count(0) )
      {
        if ( *(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, v9) + 32) )
        {
          v3 = physical_x;
          v2 = rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, v9);
          (*(void (__cdecl **)(int))(*(_DWORD *)v2 + 32))(v3);
          rf_gamesound_play_event(43, 0, 0.0, 1.0);
        }
        unk_6F8C80 = v9;
        return v9;
      }
      else
      {
        result = rf_mouse_get_relative_deltas(&v6, &v5, &unk_193A03C);
        if ( v6 || v5 )
        {
          unk_6F8C80 = v9;
          return v9;
        }
      }
    }
  }
  return result;
}

