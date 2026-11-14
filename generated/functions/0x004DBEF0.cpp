// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBEF0 rf_local_players_reset_level_runtime_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): No arguments. Resets64-slot historical body-credit registry. For each signed local entry: flags16 &=0xFFFE0079; only multiplayer byte0 clears first THREE WORDS through member44 (score/stat storage, not input bindings); target180=-1; voice handle4432=-1 WITHOUT stopping existing voice here; disarms timestamps184/188, arms192 with0ms, float4564=0. Afterwards resets/loads local fpgun models, clears global weapon-selector-open byte and resets shared cockpit latch. No own NULL entry/member guard or full-player memset.
void rf_local_players_reset_level_runtime_state()
{
  int v0; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  sub_4DBE30();
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    v0 = rf_local_player_entries[i];
    *(_DWORD *)(v0 + 16) &= 0xFFFE0079;
    if ( !rf_multiplayer_runtime_mode )
    {
      **(_WORD **)(v0 + 44) = 0;
      *(_WORD *)(*(_DWORD *)(v0 + 44) + 2) = 0;
      *(_WORD *)(*(_DWORD *)(v0 + 44) + 4) = 0;
    }
    *(_DWORD *)(v0 + 180) = -1;
    *(_DWORD *)(v0 + 4432) = -1;
    rf_replicator_reset((_DWORD *)(v0 + 184));
    rf_replicator_reset((_DWORD *)(v0 + 188));
    rf_replicator_arm_milliseconds((int *)(v0 + 192), 0);
    *(float *)(v0 + 4564) = 0.0;
  }
  rf_local_players_reset_fpgun_state_and_load_models();
  rf_weapon_selector_is_open = 0;
  rf_vehicle_cockpit_reset_shared_animation_latch();
}

