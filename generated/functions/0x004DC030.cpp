// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DC030 rf_player_update_runtime_actions_and_projectiles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player. Resolves entity20 then calls NULL-safe dead predicate before explicit NULL check. Dead/missing path: monitor predicate EXACT1 clears only target180=-1; stops voice4432 if !=-1, resets handle=-1; skips normal updates. Live path: HUD/persona/damage wrapper44A9C0; entity flags424 mask0x10 follows player byte49. Elapsed player timer188 ANY nonzero dispatches use4DC460 then disarms timer. Fpgun-presentation predicate EXACT1 updates fpgun, else advances cockpit. Entity512!=-1 rearms player timestamp60 randomly20000..40000 via4EBD20. Elapsed entity1300 EXACT1 clears holster and disarms. Elapsed player184 EXACT1 disarms then compares GLOBAL pending weapon87C648: remote-charge match
// requests(player,pending,0,0) and sets byte4164=1; else requests detonator911C88 with1,1. Checks two entity timers1216/1220, each elapsed EXACT1 disarmed; either/both coalesce into ONE projectile attempt. Remote-charge predicate EXACT1 clears player4164. Copies origin entity2004; grenade/remote-charge/flamethrower IDs use nearby-surface adjustment. Alternate flag from entity owner-player5168 flags16 mask0x20; riot-stick predicate EXACT1 plus alternate sets projectile extra mask8. Creates projectile(selected676,entity UID44,origin,view matrix2016,alternate,extra). If returned projectile nonNULL and weapon664==grenade and owner-player4160==1, OR projectile flags680 mask0x10. Multiplayer EXACT1 replicates fire via4A8390 except riot-stick ANY nonzero predicate with alternate1. Regardless of projectile creation success, consumes ammo43B1B0 and autoswitches owner-player5168. Always finishes
// live path with alt-zoom update,4EAF20,scanner update,environment voice and shared alarm deadline update. No own owner-player/model/index guards. Returned AL is final branch/helper residue, not projectile/action success.
unsigned __int8 __cdecl rf_player_update_runtime_actions_and_projectiles(int a1)
{
  unsigned __int8 result; // al
  unsigned int v2; // eax
  char v3; // [esp+3h] [ebp-21h]
  int runtime; // [esp+4h] [ebp-20h]
  float v5[3]; // [esp+8h] [ebp-1Ch] BYREF
  int v6; // [esp+14h] [ebp-10h]
  char v7; // [esp+1Bh] [ebp-9h]
  int i; // [esp+1Ch] [ebp-8h]
  _DWORD *v9; // [esp+20h] [ebp-4h]

  v9 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !rf_entity_is_dead((int)v9) && v9 )
  {
    rf_hud_update_messages_persona_audio_and_directional_damage(a1);
    if ( *(_BYTE *)(a1 + 49) )
      v2 = v9[106] | 0x10;
    else
      v2 = v9[106] & 0xFFFFFFEF;
    v9[106] = v2;
    if ( rf_replicator_has_elapsed((int *)(a1 + 188)) )
    {
      rf_player_dispatch_use_after_local_special_action(a1);
      rf_replicator_reset((_DWORD *)(a1 + 188));
    }
    if ( rf_player_should_use_fpgun_presentation(a1) )
      rf_player_update_fpgun_presentation(a1);
    else
      rf_player_advance_attached_cockpit_animation(a1);
    if ( v9[128] != -1 )
      sub_4EBD20(a1);
    if ( rf_replicator_has_elapsed(v9 + 325) )
    {
      rf_entity_clear_holster_if_mapped_weapon_owned(v9);
      rf_replicator_reset(v9 + 325);
    }
    if ( rf_replicator_has_elapsed((int *)(a1 + 184)) )
    {
      rf_replicator_reset((_DWORD *)(a1 + 184));
      if ( dword_87C648 == dword_911C78 )
      {
        rf_player_request_weapon_switch(a1, dword_87C648, 0, 0);
        *(_BYTE *)(a1 + 4164) = 1;
      }
      else
      {
        rf_player_request_weapon_switch(a1, unk_911C88, 1, 1);
      }
    }
    v7 = 0;
    for ( i = 0; i < 2; ++i )
    {
      if ( rf_replicator_has_elapsed(&v9[i + 304]) )
      {
        rf_replicator_reset(&v9[i + 304]);
        v7 = 1;
      }
    }
    if ( v7 == 1 )
    {
      if ( rf_weapon_has_remote_charge_flag(v9[169]) )
        *(_BYTE *)(a1 + 4164) = 0;
      rf_vector3_copy_return_destination(v5, (float *)v9 + 501);
      if ( v9[169] == rf_weapon_index_grenade || v9[169] == dword_911C78 || v9[169] == rf_weapon_id_flamethrower )
        rf_player_adjust_projectile_spawn_for_nearby_surfaces(a1, v5);
      v3 = (*(_DWORD *)(v9[1292] + 16) & 0x20) != 0;
      v6 = 0;
      if ( rf_weapon_is_riot_stick(v9[169]) && v3 == 1 )
        v6 |= 8u;
      runtime = rf_projectile_create_runtime(v9[169], v9[11], (int)v5, (int)(v9 + 504), v3, v6);
      if ( runtime && *(_DWORD *)(runtime + 664) == rf_weapon_index_grenade && *(_DWORD *)(v9[1292] + 4160) == 1 )
        *(_DWORD *)(runtime + 680) |= 0x10u;
      if ( rf_multiplayer_runtime_mode == 1 && (!rf_weapon_is_riot_stick(v9[169]) || v3 != 1) )
        rf_multiplayer_publish_weapon_fire(v9, v5, (float *)v9 + 504, v9[169], v3);
      rf_entity_consume_player_weapon_ammo_after_fire((int)v9, v9[169], v3);
      rf_player_autoswitch_exhausted_weapon(v9[1292], v3);
    }
    rf_player_update_alt_zoom_factor(a1);
    sub_4EAF20(a1);
    rf_player_update_scanner_flag_and_elapsed_time(a1);
    rf_player_update_environment_voice_50(a1);
    return (unsigned __int8)rf_alarm_update_shared_deadline();
  }
  else
  {
    result = rf_player_view_target_is_monitor(a1);
    if ( result == 1 )
    {
      result = a1;
      *(_DWORD *)(a1 + 180) = -1;
    }
    if ( *(_DWORD *)(a1 + 4432) != -1 )
    {
      result = (unsigned __int8)rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 4432));
      *(_DWORD *)(a1 + 4432) = -1;
    }
  }
  return result;
}

