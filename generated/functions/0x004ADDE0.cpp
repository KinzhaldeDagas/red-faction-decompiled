// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ADDE0 rf_server_respawn_player
// UNREALRED VERIFIED [death-respawn-decode]: Selects a respawn point, creates a fresh miner1 entity, and finalizes the new server-owned player body.
// Authoritative respawn: select point, allocate fresh miner1 player entity, arm Player+0xC0 spawn protection for 1500 ms, arm local fresh-entity fire timers +0x4B8/+0x4BC for 250 ms, then broadcast packet 44.
_DWORD *__cdecl rf_server_respawn_player(int a1)
{
  int v2[2]; // [esp-14h] [ebp-98h] BYREF
  int v3; // [esp-Ch] [ebp-90h]
  int v4[5]; // [esp-8h] [ebp-8Ch] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-78h]
  const char *v6; // [esp+10h] [ebp-74h]
  void *v7; // [esp+14h] [ebp-70h]
  _DWORD *v8; // [esp+18h] [ebp-6Ch]
  _DWORD *v9; // [esp+1Ch] [ebp-68h]
  const char *v10; // [esp+20h] [ebp-64h]
  char *Source; // [esp+24h] [ebp-60h]
  int *v12; // [esp+28h] [ebp-5Ch]
  void *v13; // [esp+2Ch] [ebp-58h]
  int *v14; // [esp+30h] [ebp-54h]
  void *v15; // [esp+34h] [ebp-50h]
  _DWORD v16[2]; // [esp+38h] [ebp-4Ch] BYREF
  float v17[9]; // [esp+40h] [ebp-44h] BYREF
  int v18; // [esp+64h] [ebp-20h]
  float v19[3]; // [esp+68h] [ebp-1Ch] BYREF
  int v20; // [esp+74h] [ebp-10h]
  int v21; // [esp+80h] [ebp-4h]

  rf_vector3_default_construct_noop(v19);
  rf_matrix3_construct((char *)v17);
  rf_respawn_point_select(v19, v17, a1);
  v18 = sub_431680("miner1");
  v20 = rf_multiplayer_player_entity_create(a1, v18, (int)v19, (int)v17, *(_DWORD *)(a1 + 3932));
  if ( !v20 )
    return nullptr;
  rf_replicator_arm_milliseconds((int *)(a1 + 192), 1500);
  if ( a1 == rf_local_fpgun_player )
  {
    rf_camera_slot_clear_room(*(float ***)(rf_local_fpgun_player + 196));
    rf_replicator_arm_milliseconds((int *)(v20 + 1208), 250);
    rf_replicator_arm_milliseconds((int *)(v20 + 1212), 250);
    if ( a1 )
    {
      if ( a1 == rf_local_fpgun_player && rf_multiplayer_game_mode_get() )
      {
        Source = dword_88E1B4;
        rf_string_construct_from_cstr(v16, dword_88E1B4);
        v21 = 0;
        if ( *(_BYTE *)(rf_local_fpgun_player + 48) )
        {
          v6 = (const char *)unk_88E1BC;
          v13 = v4;
          v5 = rf_string_construct_from_cstr(v4, (char *)byte_63B445);
          v4[4] = (int)v5;
          LOBYTE(v21) = 2;
          v3 = 3;
          v12 = v2;
          v4[3] = (int)rf_string_concat_object_cstr(v2, v16, v6);
        }
        else
        {
          v10 = (const char *)unk_88E1B8;
          v15 = v4;
          v9 = rf_string_construct_from_cstr(v4, (char *)&byte_63B433);
          v8 = v9;
          LOBYTE(v21) = 1;
          v3 = 2;
          v14 = v2;
          v7 = rf_string_concat_object_cstr(v2, v16, v10);
        }
        LOBYTE(v21) = 0;
        rf_multiplayer_notification_enqueue(v2[0], v2[1], v3, v4[0]);
        v21 = -1;
        rf_string_destroy_buffer(v16);
      }
    }
  }
  return rf_server_broadcast_entity_spawn_to_remote_peers(v20);
}

