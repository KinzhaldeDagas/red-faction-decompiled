// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1D70 rf_player_enter_death_transition
// UNREALRED VERIFIED [lan-body-credit-20261029] Records the current non--1 body via4E1E60, THEN sets Player+0x14=-1. Sole direct caller420140 obtains player via current-body lookup4DD720; a finalizing body already replaced in that current-player slot cannot enroll through this path. Preserve this distinction when representing early fresh-body replacement.
void __cdecl rf_player_enter_death_transition(int unused_player)
{
  if ( *(_DWORD *)(unused_player + 20) != -1 )
    sub_4E1E60(unused_player);
  *(_DWORD *)(unused_player + 20) = -1;
  *(_BYTE *)(unused_player + 4016) = 0;
  if ( rf_splitscreen_runtime_active )
  {
    if ( *(_DWORD *)(unused_player + 3968) != -1 )
    {
      rf_fpgun_cancel_transition_hook_noop(unused_player);
      *(_DWORD *)(unused_player + 3968) = -1;
      rf_replicator_reset((_DWORD *)(unused_player + 3972));
    }
    rf_fpgun_player_weapon_hook_noop(unused_player, dword_911CBC);
  }
  if ( rf_multiplayer_runtime_mode == 1
    && rf_player_has_flags16_mask10(unused_player)
    && (rf_multiplayer_game_flags & 0x20) != 0 )
  {
    if ( rf_multiplayer_server_authority == 1 )
      rf_server_respawn_player(unused_player);
    else
      rf_client_send_respawn_request(
        *(_DWORD *)(unused_player + 3932),
        *(_BYTE *)(*(_DWORD *)(unused_player + 4608) + 20));
  }
}

