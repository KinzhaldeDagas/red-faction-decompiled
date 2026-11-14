// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5250 rf_savegame_restore_player_subrecord
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Require player argument non-null. State10 skips entity/player reconstruction and returns1. Otherwise decode saved entity transform and create player entity from header byte+60; optional header flags+172 mask4 requests shared undercover replacement using mask8. Restore full536-byte entity state (queues references), then directly resolve header stable association+0 and publish entity+0x200 or-1. Restore bounded player name, low16 flags with mask8 cleared, selected scalar/vector/orientation fields,32 presence bits and32 unsigned byte counters. Force player+180=-1 despite writer saving monitor id+80. Header float+12/four words+4..10 are not read here. Rebuild entity association/presentation and optional physics flags. Later caller fixup pass can publish queued references again; direct field writes here are not the whole restore pipeline.
char __cdecl rf_savegame_restore_player_subrecord(int a1, int a2, int a3)
{
  float v4[3]; // [esp+0h] [ebp-9Ch] BYREF
  float v5[3]; // [esp+Ch] [ebp-90h] BYREF
  float v6[3]; // [esp+18h] [ebp-84h] BYREF
  float v7[3]; // [esp+24h] [ebp-78h] BYREF
  float v8[3]; // [esp+30h] [ebp-6Ch] BYREF
  float copy_result[3]; // [esp+3Ch] [ebp-60h] BYREF
  float *v10; // [esp+48h] [ebp-54h]
  int v11; // [esp+4Ch] [ebp-50h]
  float v12[9]; // [esp+50h] [ebp-4Ch] BYREF
  float v13[4]; // [esp+74h] [ebp-28h] BYREF
  float *v14; // [esp+84h] [ebp-18h]
  float world_position[3]; // [esp+88h] [ebp-14h] BYREF
  int i; // [esp+94h] [ebp-8h]
  int v17; // [esp+98h] [ebp-4h]

  if ( !a2 )
    return 0;
  if ( rf_ui_panel_stack_current_id() != 10 )
  {
    rf_float4_construct_zero_zero_zero_one(v13);
    rf_matrix3_construct((char *)v12);
    rf_vector3_default_construct_noop(world_position);
    rf_snapshot_unpack_quaternion_s16(v13, (__int16 *)(a3 + 26));
    rf_quaternion_to_matrix3_rows(v13, v12);
    rf_geomod_saved_position_decode_u16(
      (const float *)rf_world_solid,
      (const unsigned __int16 *)(a3 + 12),
      world_position);
    v17 = rf_multiplayer_player_entity_create(a2, *(unsigned __int8 *)(a1 + 60), world_position, v12, -1);
    if ( !v17 )
      return 0;
    if ( (*(_BYTE *)(a1 + 172) & 4) != 0 )
    {
      rf_undercover_enter_replace_player_entity((*(_BYTE *)(a1 + 172) & 8) != 0);
      v17 = dword_681E38;
      *(_DWORD *)(dword_681E38 + 676) = dword_87FC1C;
      rf_fpgun_selected_mesh_resolve((_DWORD *)a2, *(_DWORD *)(v17 + 676));
      rf_undercover_apply_local_weapon_skin_profile();
    }
    if ( !v17 )
      return 0;
    rf_entity_snapshot_restore_record(v17, a3);
    v14 = (float *)rf_object_find_by_saved_identifier(*(_DWORD *)a1);
    if ( v14 )
      *(float *)(v17 + 512) = v14[11];
    else
      *(_DWORD *)(v17 + 512) = -1;
    rf_string_assign_from_cstr((_DWORD *)(a2 + 8), (char *)(a1 + 20));
    *(_DWORD *)(a2 + 16) = *(_WORD *)(a1 + 52) & 0xFFF7;
    *(_DWORD *)(a2 + 4600) = *(unsigned __int16 *)(a1 + 54);
    *(_DWORD *)(a2 + 24) = *(unsigned __int8 *)(a1 + 60);
    *(_BYTE *)(a2 + 40) = *(_BYTE *)(a1 + 61);
    rf_vector_copy((float *)(a2 + 28), copy_result, (const float *)(a1 + 64));
    for ( i = 0; i < 32; ++i )
      *(_BYTE *)(i + a2 + 80) = (*(_DWORD *)(a1 + 76) & (1 << i)) != 0;
    *(_DWORD *)(a2 + 180) = -1;
    for ( i = 0; i < 32; ++i )
      *(_DWORD *)(a2 + 4 * i + 4436) = *(unsigned __int8 *)(i + a1 + 84);
    rf_vector_copy((float *)(a2 + 4120), v8, (const float *)(a1 + 152));
    rf_matrix3_copy((float *)(a2 + 4084), (const float *)(a1 + 116));
    *(_BYTE *)(a2 + 4156) = (*(_BYTE *)(a1 + 172) & 1) == 1;
    *(_DWORD *)(a2 + 4160) = *(unsigned __int8 *)(a1 + 164);
    *(_BYTE *)(a2 + 4164) = (*(_BYTE *)(a1 + 172) & 2) != 0;
    if ( *(_DWORD *)(v17 + 676) == dword_911C78 && !*(_BYTE *)(a2 + 4164) )
      *(_DWORD *)(v17 + 676) = unk_911C88;
    if ( *(_DWORD *)(v17 + 512) != -1 )
    {
      v11 = *(_DWORD *)(v17 + 516);
      *(_DWORD *)(v17 + 516) = -1;
      if ( !*((_DWORD *)v14 + 9) )
      {
        v10 = v14;
        rf_entity_disable_headlamp_recursive(v14);
        rf_entity_associate_child_with_last_slot_key((int)v10, *(_DWORD *)(v17 + 44), v11);
        *((_DWORD *)v10 + 516) |= 0x10000u;
        *((_DWORD *)v10 + 516) &= ~0x20000u;
        sub_4BBF50((int)v10, 1);
        rf_vector_copy(v10 + 1293, v7, (const float *)(*((_DWORD *)v10 + 165) + 108));
        rf_vector_copy(v10 + 1296, v6, (const float *)(*((_DWORD *)v10 + 165) + 120));
        if ( rf_entity_is_parent_jeep_relation1(v17) )
        {
          rf_vector_copy((float *)(v17 + 5172), v5, &flt_87C67C);
          rf_vector_copy((float *)(v17 + 5184), v4, &flt_87C68C);
        }
        if ( rf_entity_class_has_angular_decay_flags((int)v10) )
          rf_object_request_physics_reactivation_flags((int)v10);
      }
    }
    rf_entity_update_allocated_sphere_center_positions(v17);
    if ( (*(_DWORD *)(v17 + 2064) & 0x400) != 0 )
    {
      rf_entity_apply_crouch_shape_centers(v17);
      *(_BYTE *)(a2 + 177) = 1;
    }
  }
  return 1;
}

