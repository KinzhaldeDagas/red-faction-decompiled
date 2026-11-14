// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438170 rf_weapon_present_shell_ejection
// UNREALRED VERIFIED [weapon-shell-ejection-20261008] Shell presentation owner. Rejects a player-associated entity when Player+3894 is zero, and rejects local-observer distance squared >64 RF units. Requires selected weapon eject speed +1204 >0. First-person prop is resolved by 0x5109A0; third-person uses character class +1768 shell prop or first primary_weapon prop fallback. Samples normalized authored direction in cone min-dot 0.992, multiplies authored speed, rotates by entity aim matrix +0x7E0, adds half entity velocity +0x144. Random orientation and angular vector magnitude [150,175] are passed to shared physics (integrator cap15 rad/s). Lifetime=800ms, or1200ms for Entity+0x7C bit8. Material2, custom contact sound +1216. Calls 0x4187B0 with physical mass0.1, NOT mesh scale. No first-person reload-clip -0.6 offset. Unreal uses decoded launch inputs plus its shared Chaos debris adapter; exact collision/settling and remote shot replay are not established here.
void __cdecl rf_weapon_present_shell_ejection(float *a1)
{
  int v1; // eax
  int v2; // eax
  int *v3; // eax
  float v4; // ecx
  float *v5; // eax
  char *v6; // eax
  float v7; // [esp+0h] [ebp-10Ch] BYREF
  float *v8; // [esp+4h] [ebp-108h]
  float *v9; // [esp+8h] [ebp-104h]
  float scalar; // [esp+Ch] [ebp-100h]
  float scaled_result[4]; // [esp+10h] [ebp-FCh] BYREF
  int v12; // [esp+20h] [ebp-ECh]
  char v13[36]; // [esp+24h] [ebp-E8h] BYREF
  unsigned int selected_weapon_and_resolve_mesh; // [esp+48h] [ebp-C4h]
  int v15; // [esp+4Ch] [ebp-C0h]
  float *v16; // [esp+50h] [ebp-BCh]
  float v17[3]; // [esp+54h] [ebp-B8h] BYREF
  float v18; // [esp+60h] [ebp-ACh]
  int v19[3]; // [esp+64h] [ebp-A8h] BYREF
  float v20[9]; // [esp+70h] [ebp-9Ch] BYREF
  float v21[3]; // [esp+94h] [ebp-78h] BYREF
  float v22[11]; // [esp+A0h] [ebp-6Ch] BYREF
  int v23; // [esp+CCh] [ebp-40h]
  char v24[36]; // [esp+D0h] [ebp-3Ch] BYREF
  float *v25; // [esp+F4h] [ebp-18h]
  int v26; // [esp+F8h] [ebp-14h]
  _BYTE v27[12]; // [esp+FCh] [ebp-10h] BYREF
  float *v28; // [esp+108h] [ebp-4h]

  rf_geomod_debris_spawn_config_init((int)v19);
  rf_matrix3_construct(v24);
  rf_vector3_default_construct_noop(v27);
  if ( sub_438AC0((int)a1) && !*(_BYTE *)(*((_DWORD *)a1 + 1292) + 3894) )
    return;
  if ( dword_681E38 )
  {
    if ( *(_DWORD *)(dword_681E38 + 5168) )
    {
      rf_entity_view_copy_referenced_position(v17, *(_DWORD *)(*(_DWORD *)(dword_681E38 + 5168) + 196));
      v18 = rf_vector_distance_squared(v17, a1 + 15);
      if ( v18 > 64.0 )
        return;
    }
  }
  v25 = nullptr;
  v28 = a1;
  if ( (!sub_438AC0((int)a1) || rf_view_wrapper_get_dword8(*(_DWORD *)(*((_DWORD *)a1 + 1292) + 196)))
    && !rf_entity_jeep_second_relation_resolves_object((int)a1) )
  {
    v25 = (float *)((char *)&rf_weapon_records + 1360 * *((_DWORD *)a1 + 169));
    if ( v25[301] <= 0.0 )
      return;
    if ( *(_DWORD *)(*((_DWORD *)a1 + 165) + 1768) == -1 || !*((_DWORD *)a1 + 32) )
    {
      if ( rf_receiver_get_first_dword((void *)(*((_DWORD *)a1 + 167) + 468)) <= 0 )
        return;
      rf_matrix3_construct(v13);
      v12 = sub_50FFA0(*((_DWORD *)a1 + 169));
      if ( !v12 || !*((_DWORD *)a1 + 32) )
        return;
      scalar = COERCE_FLOAT(v19);
      v9 = (float *)v13;
      v8 = a1 + 15;
      LODWORD(v7) = a1 + 18;
      v3 = (int *)rf_inline_dword_array4_element_address_unchecked((void *)(*((_DWORD *)a1 + 167) + 468), 0);
      rf_vmesh_compose_prop_world_transform(*((_DWORD *)a1 + 32), *v3, a1 + 18, (int)(a1 + 15), (int)v13, (float *)v19);
    }
    else
    {
      rf_vmesh_compose_prop_world_transform(
        *((_DWORD *)a1 + 32),
        *(_DWORD *)(*((_DWORD *)a1 + 165) + 1768),
        a1 + 18,
        (int)(a1 + 15),
        (int)v24,
        (float *)v19);
    }
    goto LABEL_23;
  }
  v16 = *((float **)a1 + 1292);
  if ( rf_entity_jeep_second_relation_resolves_object((int)a1) )
  {
    v1 = sub_552200((_DWORD *)a1 + 563, 1);
    v16 = (float *)sub_4DD720(*(_DWORD *)(*(_DWORD *)v1 + 4));
    v2 = sub_552200((_DWORD *)a1 + 563, 1);
    v28 = (float *)rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)v2 + 4));
  }
  selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(v16);
  if ( selected_weapon_and_resolve_mesh != -1 )
  {
    v25 = (float *)((char *)&rf_weapon_records + 1360 * selected_weapon_and_resolve_mesh);
    if ( v25[301] > 0.0 )
    {
      v15 = rf_weapon_resolve_shell_eject_prop((int)v16, selected_weapon_and_resolve_mesh);
      rf_vmesh_compose_prop_world_transform(
        *((_DWORD *)v16 + 13),
        v15,
        v16 + 1021,
        (int)(v16 + 1030),
        (int)v24,
        (float *)v19);
LABEL_23:
      scalar = 0.99199998;
      rf_vector3_copy_return_destination(&v7, v25 + 298);
      rf_random_unit_vector_in_cone(v21, v7, *(float *)&v8, *(float *)&v9, scalar);
      scalar = v4;
      rf_vector3_scale_in_place_return_self(v21, v25[301]);
      rf_vector_rotate_by_matrix3(v21, v28 + 504);
      v5 = rf_vector_multiply_scalar(v28 + 81, scaled_result, 0.5);
      rf_vector_accumulate(v21, v5);
      rf_random_orientation_matrix(v20);
      rf_random_unit_vector(v22);
      scalar = rf_random_float_range(150.0, 175.0);
      rf_vector3_scale_in_place_return_self(v22, scalar);
      v26 = 800;
      if ( rf_object_has_player_flag((int)a1) )
        v26 = 1200;
      LODWORD(v22[3]) = v26;
      LODWORD(v22[4]) = 2;
      v22[5] = NAN;
      LODWORD(v22[6]) = 12;
      LODWORD(v22[7]) = 0x10000;
      v22[9] = v25[304];
      LODWORD(v22[8]) = rf_receiver_get_first_dword(a1);
      scalar = -1.0;
      v9 = nullptr;
      v8 = (float *)v19;
      v7 = 0.1;
      v6 = (char *)rf_string_object_c_str_or_empty(v25 + 302);
      v23 = rf_physical_debris_piece_create(-1, v6, (void *)LODWORD(v7), v8, (int)v9, (void *)LODWORD(scalar));
      if ( v23 )
      {
        *(_DWORD *)(v23 + 424) &= ~0x10u;
        *(_DWORD *)(v23 + 124) |= 0x10000000u;
      }
    }
  }
}

