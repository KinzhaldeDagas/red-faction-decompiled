// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497430 rf_ctf_capture_at_base
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(player, base item). Requires mode1 and shared cooldown admission (reject only armed exactly1 and not elapsed). Base instance +700 bit80 has priority: requires player team
// exactly0, blue carrier==player, red carrier null and red flag home bit200 set. In order: increment red captures/assist awards, add4 player frags, add1 score WORD+4, clear blue
// carrier (arming25s), play event63, return blue home(selector0,sound0), broadcast packet32(selector0,player), then server-only capture feedback(player,0). Home reset cancels both
// return timers and arms500ms cooldown.
// Otherwise bit100 requires team exactly1, red carrier==player, blue carrier null and blue home bit200. Performs blue captures/assists, +4 frags, +1 WORD+4, clears red carrier,
// event63, red home reset(1,0), packet32(1,player), then server-only capture feedback(player,0). BOTH native feedback calls pass zero, selecting blue wording even in red-flag capture
// branch; preserve this asymmetry. Only final feedback is guarded by runtime mode1 and authority exactly1: score/counter/state actions have no own authority guard. No
// pointer/score/type validation.
void __cdecl rf_ctf_capture_at_base(int a1, int a2)
{
  if ( rf_multiplayer_game_mode_get() == 1
    && (!rf_replicator_is_armed(&unk_77D72C) || rf_replicator_has_elapsed(&unk_77D72C)) )
  {
    if ( (*(_DWORD *)(a2 + 700) & 0x80) != 0 )
    {
      if ( *(_BYTE *)(a1 + 48) != 1
        && !*(_BYTE *)(a1 + 48)
        && rf_ctf_blue_carrier_get() == a1
        && !rf_ctf_red_carrier_get()
        && (*(_DWORD *)(dword_77D6E4 + 700) & 0x200) != 0 )
      {
        rf_ctf_red_capture_increment_and_assists();
        rf_multiplayer_player_add_frags(a1, 4);
        rf_player_score_record_add_word4(a1, 1);
        rf_ctf_blue_carrier_set(0);
        rf_gamesound_play_event(63, 0, 0.0, 1.0);
        rf_ctf_return_flag_home(0, 0);
        rf_ctf_broadcast_flag_captured_packet32(0, a1);
        if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
          rf_ctf_flag_capture_notification(a1, 0);
      }
    }
    else if ( (*(_DWORD *)(a2 + 700) & 0x100) != 0 )
    {
      if ( *(_BYTE *)(a1 + 48) )
      {
        if ( *(_BYTE *)(a1 + 48) == 1
          && rf_ctf_red_carrier_get() == a1
          && !rf_ctf_blue_carrier_get()
          && (*(_DWORD *)(dword_77D6E8 + 700) & 0x200) != 0 )
        {
          rf_ctf_blue_capture_increment_and_assists();
          rf_multiplayer_player_add_frags(a1, 4);
          rf_player_score_record_add_word4(a1, 1);
          rf_ctf_red_carrier_set(0);
          rf_gamesound_play_event(63, 0, 0.0, 1.0);
          rf_ctf_return_flag_home(1, 0);
          rf_ctf_broadcast_flag_captured_packet32(1, a1);
          if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
            rf_ctf_flag_capture_notification(a1, 0);
        }
      }
    }
  }
}

