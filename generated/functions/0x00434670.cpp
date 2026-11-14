// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434670 rf_entity_contact_effects_and_response_code
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): ECX entity,thiscall,no stack arguments,plain RET. Returns ONLY1 or2 across all native exits;does not itself perform generic collision velocity response59C0. Liquid492 nonzero: when replicator5140 elapsed exactly1,chooses effect global90B828 only for ORDERED radius120>=2.5,otherwise90B834;spawns at contact436 using object firstDWORD/room receiver and radius120,arms2000ms,returns2. Otherwise ONLY ORDERED reciprocal468==0 enters world/special-impact branch;nonzero OR unordered uses resolved otherUID484. World branch class660 flag1828 bit0x200 has priority: requires ORDERED velocity324 squared>2240^2*0.8999999761581421 AND dot(common forward96,normal448)<-0.8999999761581421;finds bumper_1 node,loads
// Holey_APC.v3d,composes node world transform,admits geomod at composed point/direction96 with ownUID,radius120,loaded model,flags30,and damage75;skips later vehicle foley even if operation fails. Only if class0x200 predicate false,bit0x400+material464==8+ORDERED dot(velocity,N)<-3 admits geomod at contact with radius2*radius120/flags16 and damage100 attributed ownUID;for each local player whose resolved entity512 equals ownUID,calls effect helper4123F0 with0.995/0.5 and sets directional nibble fromN;also suppressesfoley. Otherwise use-vehicle calls impact-foley434B50 at contact. Every world path returns2. Other-object path: unresolved UID ->2;other type4 whose clutter record664 equals global666B64 ->1 BEFORE own player check. Own player-flag ->2. Other type0 delegates421700 and maps true2/false1;type1 attempts item pickup(other,self,1,0) then ALWAYS1 regardless pickup success;types3/4/7/9
// ->2;type2 and all other/default including negative ->1. No own NULL/class/model/node/player-array guards or rollback of effects/damage on later misses.
int __thiscall rf_entity_contact_effects_and_response_code(int this)
{
  int first_dword; // eax
  int result; // eax
  int v3; // eax
  int v4; // eax
  char v5; // al
  float v6; // [esp+Ch] [ebp-78h]
  int v7; // [esp+14h] [ebp-70h]
  float v8; // [esp+20h] [ebp-64h]
  int v10; // [esp+28h] [ebp-5Ch]
  int v11; // [esp+2Ch] [ebp-58h]
  int i; // [esp+38h] [ebp-4Ch]
  int v13[3]; // [esp+3Ch] [ebp-48h] BYREF
  int name; // [esp+48h] [ebp-3Ch]
  char v15[36]; // [esp+4Ch] [ebp-38h] BYREF
  int node_adapter; // [esp+70h] [ebp-14h]
  float v17; // [esp+74h] [ebp-10h]
  int v18; // [esp+78h] [ebp-Ch]
  char v19; // [esp+7Fh] [ebp-5h]
  _DWORD *v20; // [esp+80h] [ebp-4h]

  v19 = 1;
  if ( *(_DWORD *)(this + 492) )
  {
    if ( rf_replicator_has_elapsed((int *)(this + 5140)) )
    {
      v18 = unk_90B834;
      if ( *(float *)(this + 120) >= 2.5 )
        v18 = unk_90B828;
      v6 = *(float *)(this + 120);
      first_dword = rf_receiver_get_first_dword((void *)this);
      rf_vclip_spawn_runtime_effect(v18, first_dword, this + 60, this + 436, v6, -1, 0, 1);
      rf_replicator_arm_milliseconds((int *)(this + 5140), 2000);
    }
    return 2;
  }
  else if ( *(float *)(this + 468) == 0.0 )
  {
    if ( rf_entity_class_has_contact_geomod_flag200(this) )
    {
      if ( *(float *)(this + 2240) * *(float *)(this + 2240) * 0.8999999761581421 < rf_vector_length_squared((float *)(this + 324)) )
      {
        v17 = rf_vector_dot((float *)(this + 96), (float *)(this + 448));
        if ( v17 < -0.8999999761581421 )
        {
          rf_vector3_default_construct_noop(v13);
          rf_matrix3_construct(v15);
          node_adapter = rf_model_handle_find_node_adapter(*(_DWORD *)(this + 128), "bumper_1");
          name = rf_geomod_cutter_registry_find_name("Holey_APC.v3d");
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(this + 128),
            node_adapter,
            (float *)(this + 72),
            this + 60,
            (int)v15,
            (float *)v13);
          v7 = name;
          v3 = rf_receiver_get_first_dword((void *)this);
          rf_geomod_operation_admit(*(float *)(this + 120), *(_DWORD *)(this + 44), v3, (int)v13, this + 96, v7, 30);
          rf_damage_dispatch(*(_DWORD *)(this + 44), 75.0, -1, 0, -1, 0, -1, 0);
          v19 = 0;
        }
      }
    }
    else if ( rf_entity_class_has_contact_geomod_flag400(this)
           && *(_DWORD *)(this + 464) == 8
           && rf_vector_dot((float *)(this + 324), (float *)(this + 448)) < -3.0 )
    {
      v4 = rf_receiver_get_first_dword((void *)this);
      v8 = *(float *)(this + 120) + *(float *)(this + 120);
      rf_geomod_operation_admit(v8, *(_DWORD *)(this + 44), v4, this + 436, this + 448, 0, 16);
      rf_damage_dispatch(*(_DWORD *)(this + 44), 100.0, *(_DWORD *)(this + 44), -1, 0, 0, -1, 0);
      for ( i = 0; i < rf_local_player_entry_count; ++i )
      {
        v11 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20));
        if ( v11 && *(_DWORD *)(v11 + 512) == *(_DWORD *)(this + 44) )
        {
          rf_entity_set_player_linked_perturbation_timer(*(_DWORD *)(*(_DWORD *)(v11 + 5168) + 196), 0.995, 0.5);
          v5 = rf_player_direction_to_local_quadrant_mask(rf_local_player_entries[i], (float *)(this + 448));
          rf_player_or_direction_nibble_into_flags(rf_local_player_entries[i], v5);
        }
      }
      v19 = 0;
    }
    if ( v19 && rf_object_is_use_vehicle((_DWORD *)this) )
      rf_entity_try_play_vehicle_impact_foley(this, (float *)(this + 436));
    return 2;
  }
  else
  {
    v20 = (_DWORD *)rf_object_resolve_handle(*(_DWORD *)(this + 484));
    if ( v20 )
    {
      if ( v20[9] == 4 && (v10 = rf_clutter_find_by_uid(v20[11])) != 0 && *(_DWORD *)(v10 + 664) == unk_666B64 )
      {
        return 1;
      }
      else if ( rf_object_has_player_flag(this) )
      {
        return 2;
      }
      else
      {
        switch ( v20[9] )
        {
          case 0:
            if ( rf_entity_contact_with_entity_allows_velocity_response(this, (int)v20) )
              result = 2;
            else
              result = 1;
            break;
          case 1:
            rf_item_pickup_dispatch(v20, this, 1, 0);
            result = 1;
            break;
          case 2:
            result = 1;
            break;
          case 3:
          case 4:
          case 7:
            result = 2;
            break;
          case 9:
            result = 2;
            break;
          default:
            result = 1;
            break;
        }
      }
    }
    else
    {
      return 2;
    }
  }
  return result;
}

