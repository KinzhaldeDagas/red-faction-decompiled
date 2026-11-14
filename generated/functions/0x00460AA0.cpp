// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460AA0 rf_multiplayer_profile_handle_key
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl FULL keyDWORD,stored int type preserved as incidental. EXACT1 disable/hide profile460550;does not commit name. EXACT15 increments focus6F4A50 with
// signed count wrap0;EXACT100F decrements with negative wrapcount-1;both sound42 and clear edit latch6F4AD5,no empty-list/state9 skipping. EXACT203/205 invoke previous/next character
// arrow only if its BYTE8 nonzero and callback32 nonNULL,passing(-1,-1). ALL other keys,including Enter,pass to edit470A40 only when name-control BYTE8 nonzero;nonzero AL sets
// nameDirty6F4AD6=1. No own profile/menu-active/current-pane/runtime gate,focus bounds or name commit;outer router supplies pane admission.
void __cdecl rf_multiplayer_profile_handle_key(int a1)
{
  if ( a1 > 203 )
  {
    if ( a1 != 205 )
    {
      if ( a1 != 4111 )
      {
LABEL_24:
        if ( unk_6F4B10 )
        {
          if ( rf_ui_edit_handle_key(byte_6F4B08, a1) )
            unk_6F4AD6 = 1;
        }
        return;
      }
      --unk_6F4A50;
      if ( unk_6F4A50 < 0 )
        unk_6F4A50 = rf_receiver_get_first_dword(dword_6F5028) - 1;
LABEL_12:
      rf_gamesound_play_event(42, 0, 0.0, 1.0);
      unk_6F4AD5 = 0;
      return;
    }
    if ( unk_6F4BC0 && unk_6F4BD8 )
      unk_6F4BD8(-1, -1);
  }
  else
  {
    if ( a1 != 203 )
    {
      if ( a1 == 1 )
      {
        rf_multiplayer_profile_disable_input_and_schedule_hide();
        return;
      }
      if ( a1 != 15 )
        goto LABEL_24;
      ++unk_6F4A50;
      if ( unk_6F4A50 >= rf_receiver_get_first_dword(dword_6F5028) )
        unk_6F4A50 = 0;
      goto LABEL_12;
    }
    if ( unk_6F5048 && unk_6F5060 )
      unk_6F5060(-1, -1);
  }
}

