// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004666F0 rf_multiplayer_menu_start_host
// UNREALRED VERIFIED [local-multiplayer-20261028] Host Start first calls0x45DAA0 to validate/copy a nonempty selected level rotation; failure displays an error before multiplayer initialization. Success initializes runtime, applies server name/max players/mode/password and rules, marks local host and starts authority via0x4B0770. ListLAN=true clears publication flag0x400; false sets it and invokes GameTracker initialization/registration. LAN hosting therefore does not require the internet master-service branch.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Additional native host-menu/ABI verification:before validating rotation,set pendingPane6F5E3C=-1,pane speed negative,disable pane input467320.
// Rotation-copy AL0 ->sound2/error modal and NO runtime initialization;hide already scheduled. Success:startup flag,runtime_initialize(0,0),persist/copy server name to704EC0,store
// max players704EDC/mode704ED4/fixedDWORD704EEC64,copy enabled password to704EC8;destroy local owned strings,clear notifications,apply rules. Unguarded localPlayer.net+8
// OR1;call48FEF0 then begin_authority_session BEFORE publication admission. HostLANBYTE6F5E51==EXACT1 clears gameFlag400;all other values set it. If set,tracker-init FULL EAX0
// clears400/shows error but DOES NOT undo authority session;nonzero calls control_cancel_pending_state with TWO native(0,0) words. No explicit main panel close/runtime rollback on
// publication failure. Existing SEH chunks/by-value RFString lifetimes and void prototype retained.
void rf_multiplayer_menu_start_host()
{
  _DWORD *v0; // [esp+14h] [ebp-34h]
  _DWORD *v1; // [esp+1Ch] [ebp-2Ch]
  _DWORD v2[2]; // [esp+2Ch] [ebp-1Ch] BYREF
  _DWORD v3[2]; // [esp+34h] [ebp-14h] BYREF
  int v4; // [esp+44h] [ebp-4h]

  unk_6F5E3C = -1;
  unk_6F5E4C = -rf_ui_open_transition_speed;
  rf_host_menu_disable_pane_input_and_hide();
  if ( rf_multiplayer_menu_copy_level_rotation(unk_704F00) )
  {
    rf_set_startup_session_flag();
    rf_multiplayer_runtime_initialize(0, 0);
    v1 = rf_multiplayer_setup_persist_and_copy_server_name(v3);
    v4 = 0;
    rf_string_assign_from_object(unk_704EC0, (int)v1);
    v4 = -1;
    rf_string_destroy_buffer(v3);
    *(_DWORD *)unk_704EDC = rf_multiplayer_menu_get_max_players();
    unk_704ED4 = rf_multiplayer_setup_game_mode_index_get();
    *(_DWORD *)unk_704EEC = 64;
    v0 = rf_multiplayer_setup_copy_enabled_password(v2);
    v4 = 1;
    rf_string_assign_from_object(dword_704EC8, (int)v0);
    v4 = -1;
    rf_string_destroy_buffer(v2);
    rf_multiplayer_notification_text_rows_clear();
    rf_multiplayer_rules_apply_ui_state();
    *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) |= 1u;
    sub_48FEF0();
    rf_multiplayer_begin_authority_session();
    if ( byte_6F5E51[0] == 1 )
      rf_multiplayer_game_flags &= ~0x400u;
    else
      rf_multiplayer_game_flags |= 0x400u;
    if ( (rf_multiplayer_game_flags & 0x400) != 0 )
    {
      if ( rf_tracker_initialize_host_templates_and_pool() )
      {
        rf_network_control_cancel_pending_state();
      }
      else
      {
        rf_multiplayer_game_flags &= ~0x400u;
        rf_ui_show_ok_modal(unk_88E138, unk_88E264, 0, 0);
      }
    }
  }
  else
  {
    rf_gamesound_play_event(2, 0, 0.0, 1.0);
    rf_ui_show_ok_modal(unk_88E0A4, unk_88E038, 0, 0);
  }
}

