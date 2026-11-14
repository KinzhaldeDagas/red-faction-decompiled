// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049A550 rf_client_process_entity_create_packet_44
// UNREALRED VERIFIED [player-identity-20260930] Player-associated entity-create records read a signed 32-bit character selection into Player+0xF5C and pass that value to 0x4DE480 before entity visual creation; the constructor range-resolves then forwards the chosen slot to 0x42CB80. Thus remote body identity is part of each entity bootstrap, not merely a durable player preference. Unreal must initialize each replicated pawn with the authority-resolved character slot before visual loading, independently of later PlayerState arrival or possession. This evidence does not establish arbitrary live model switching or authored preview-AI reconstruction.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662B58 registers opcode44 (entity_create), callback0x0049A550. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
int __cdecl rf_client_process_entity_create_packet_44(const char *a1)
{
  int result; // eax
  int v2; // eax
  int v3; // [esp+1Ch] [ebp-160h]
  int weapon_index; // [esp+20h] [ebp-15Ch]
  float v5[3]; // [esp+28h] [ebp-154h] BYREF
  char v6; // [esp+37h] [ebp-145h]
  int runtime; // [esp+38h] [ebp-144h]
  int v8; // [esp+3Ch] [ebp-140h]
  float v9[9]; // [esp+40h] [ebp-13Ch] BYREF
  char Destination[260]; // [esp+64h] [ebp-118h] BYREF
  char v11; // [esp+16Eh] [ebp-Eh]
  unsigned __int8 v12; // [esp+16Fh] [ebp-Dh]
  int player; // [esp+170h] [ebp-Ch]
  int v14; // [esp+174h] [ebp-8h]
  int v15; // [esp+178h] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    rf_vector3_default_construct_noop(v5);
    rf_matrix3_construct((char *)v9);
    v14 = 0;
    strncpy(Destination, a1, 0xFFu);
    Destination[254] = 0;
    v14 = (unsigned __int16)(v14 + strlen(a1) + 1);
    v6 = a1[v14];
    v12 = a1[++v14];
    v15 = *(_DWORD *)&a1[++v14];
    v14 += 4;
    v8 = *(_DWORD *)&a1[v14];
    v14 += 4;
    v5[0] = *(float *)&a1[v14];
    v14 += 4;
    v5[1] = *(float *)&a1[v14];
    v14 += 4;
    v5[2] = *(float *)&a1[v14];
    v14 += 4;
    v9[0] = *(float *)&a1[v14];
    v14 += 4;
    v9[1] = *(float *)&a1[v14];
    v14 += 4;
    v9[2] = *(float *)&a1[v14];
    v14 += 4;
    v9[3] = *(float *)&a1[v14];
    v14 += 4;
    v9[4] = *(float *)&a1[v14];
    v14 += 4;
    v9[5] = *(float *)&a1[v14];
    v14 += 4;
    v9[6] = *(float *)&a1[v14];
    v14 += 4;
    v9[7] = *(float *)&a1[v14];
    v14 += 4;
    v9[8] = *(float *)&a1[v14];
    v14 += 4;
    v11 = a1[v14++];
    rf_replication_timer7B25EC_arm_8s();
    if ( *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) == 2
      || (result = *(_DWORD *)(rf_local_fpgun_player + 4608), *(_DWORD *)(result + 12) == 1) )
    {
      player = 0;
      runtime = 0;
      if ( v11 == -1 )
      {
        v8 = rf_replication_server_id_to_local_handle(v8);
        runtime = rf_entity_create_runtime(v12, Destination, v8, v5, v9, 0, -1);
      }
      else
      {
        player = (int)rf_player_find_by_network_id(v11);
        if ( !player )
          return printf("Received an object create packet for a player that doesn't exist\n");
        *(_DWORD *)(player + 3932) = *(_DWORD *)&a1[v14];
        *(_DWORD *)(player + 3932) = *(_DWORD *)(player + 3932);
        v14 += 4;
        if ( *(_DWORD *)(player + 3932) > rf_multiplayer_character_count || *(int *)(player + 3932) < 0 )
        {
          v2 = rf_multiplayer_character_find_by_name("parker");
          *(_DWORD *)(player + 3932) = v2;
        }
        runtime = rf_multiplayer_player_entity_create(player, v12, (int)v5, (int)v9, *(_DWORD *)(player + 3932));
        if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority && player == rf_local_fpgun_player )
          rf_clock_deadline_set_wrapped_offset(&dword_7B2538, 0);
        if ( runtime )
        {
          rf_replicator_arm_milliseconds((int *)(runtime + 1208), 250);
          rf_replicator_arm_milliseconds((int *)(runtime + 1212), 250);
        }
      }
      if ( runtime )
      {
        *(_BYTE *)(runtime + 40) = v6;
        rf_replication_bind_server_id_to_local_handle(v15, *(_DWORD *)(runtime + 44));
      }
      if ( player )
        *(_BYTE *)(player + 48) = v6;
      if ( player && runtime )
      {
        weapon_index = *(_DWORD *)&a1[v14];
        v14 += 4;
        v3 = *(_DWORD *)&a1[v14];
        v14 += 4;
        if ( weapon_index >= 0 )
        {
          rf_entity_inventory_grant_weapon((int *)(runtime + 672), weapon_index, -1);
          rf_player_apply_weapon_selection_by_class(player, weapon_index);
        }
        if ( v3 >= 0 )
          rf_entity_inventory_grant_weapon((int *)(runtime + 672), v3, -1);
      }
      result = *(_DWORD *)(rf_local_fpgun_player + 4608);
      if ( *(_DWORD *)(result + 12) == 2 )
        return rf_gamesound_play_positional_event(58, v5, 1.0, (int)flt_17F10B0, 0);
    }
  }
  return result;
}

