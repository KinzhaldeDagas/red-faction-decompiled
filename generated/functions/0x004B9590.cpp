// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B9590 rf_object_type_lists_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): No arguments; postphysics passes in order: movers publish pending positions; physical debris update then contact response if physics-enabled
// predicate AL==0 and float+460 ordered<1; clutter contact if float+460 ordered<1 and disabled; item pickup contact if float+460 ordered<1 without physics-enabled gate; entities;
// conditional CTF flags; projectiles. All intrusive loops follow next+652 AFTER callbacks until their own sentinel. Entity change marker is set if common bit0x2000000, or
// bit0x4000000 plus ordered squared-distance(entity+108,+228)>0; it clears first bit, sets second, and remembers change. Always calls4275B0; then entity flags+2064 bit2 calls4356E0,
// otherwise fall/airborne predicate calls4D9960, otherwise4D9960 requires classification pointer+2136 DWORD+4==1, attachment handle+512==-1, and (remembered change OR physics
// flags+424 bit0x400000 OR player-flag predicate). CTF update requires nonzero runtime byte and game mode EXACT1; no own authority gate. Timestamp-counter calls bracket passes; final
// EAX/EDX is incidental last timestamp, not an update count.
unsigned __int64 rf_object_type_lists_update()
{
  char v1; // [esp+3h] [ebp-39h]
  int n; // [esp+Ch] [ebp-30h]
  int m; // [esp+10h] [ebp-2Ch]
  int j; // [esp+28h] [ebp-14h]
  int ii; // [esp+2Ch] [ebp-10h]
  int i; // [esp+34h] [ebp-8h]
  int k; // [esp+38h] [ebp-4h]

  rf_clock_read_timestamp_counter();
  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
    rf_mover_publish_pending_positions(i);
  rf_clock_read_timestamp_counter();
  for ( j = rf_physical_debris_list_head; (_UNKNOWN *)j != &rf_physical_debris_list_sentinel; j = *(_DWORD *)(j + 652) )
  {
    rf_geomod_debris_update(j);
    if ( !rf_physics_state_is_enabled(j + 136) && *(float *)(j + 460) < 1.0 )
      rf_physical_debris_contact_response((_DWORD *)j);
  }
  rf_clock_read_timestamp_counter();
  for ( k = rf_clutter_list_head; (_UNKNOWN *)k != &unk_666D18; k = *(_DWORD *)(k + 652) )
  {
    if ( *(float *)(k + 460) < 1.0 && !rf_physics_state_is_enabled(k + 136) )
      rf_clutter_contact_response_code(k);
  }
  rf_clock_read_timestamp_counter();
  for ( m = unk_6FB1C4; (_UNKNOWN *)m != &unk_6FAF38; m = *(_DWORD *)(m + 652) )
  {
    if ( *(float *)(m + 460) < 1.0 )
      rf_item_contact_try_pickup(m);
  }
  rf_clock_read_timestamp_counter();
  for ( n = unk_68211C; (_UNKNOWN *)n != &unk_681E90; n = *(_DWORD *)(n + 652) )
  {
    v1 = 0;
    if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(n + 124)) != 0
      || (*(_DWORD *)(n + 124) & 0x4000000) != 0
      && rf_vector_distance_squared((const float *)(n + 108), (const float *)(n + 228)) > 0.0 )
    {
      *(_DWORD *)(n + 124) &= ~0x2000000u;
      *(_DWORD *)(n + 124) |= 0x4000000u;
      v1 = 1;
    }
    sub_4275B0((unsigned int *)n);
    if ( (*(_DWORD *)(n + 2064) & 2) != 0 )
    {
      rf_entity_select_fall_movement_descriptor((_DWORD *)n);
    }
    else if ( rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)n) )
    {
      sub_4D9960(n);
    }
    else if ( *(_DWORD *)(*(_DWORD *)(n + 2136) + 4) == 1
           && *(_DWORD *)(n + 512) == -1
           && (v1 || (*(_DWORD *)(n + 424) & 0x400000) != 0 || rf_object_has_player_flag(n)) )
    {
      sub_4D9960(n);
    }
  }
  if ( rf_multiplayer_runtime_mode && rf_multiplayer_game_mode_get() == 1 )
    rf_ctf_flags_update();
  rf_clock_read_timestamp_counter();
  for ( ii = dword_911F74; (_UNKNOWN *)ii != &unk_911CE8; ii = *(_DWORD *)(ii + 652) )
    rf_projectile_postphysics_update(ii);
  rf_clock_read_timestamp_counter();
  return rf_clock_read_timestamp_counter();
}

