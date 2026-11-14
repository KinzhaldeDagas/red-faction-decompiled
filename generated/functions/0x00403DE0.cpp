// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403DE0 rf_ai_update_one_block
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): One required AI-block pointer with owner entity at+0. Global BYTE6663D1==EXACT1 skips entire body; other values execute. Mode DWORD+640==0 first
// calls40A2A0. Then4042A0 clears control fields, zero vector+1280,4042E0, and408DB0 for mode!=0 AND!=1 (including negative modes). If lengthSquared(vector+1280) ordered>DOUBLE1e-5,
// copies it to+1140 and inverse-rotates by owner common matrix+72. Independently clamps each+1140/+1144/+1148 to[-1,1] through three-argument helper; native stack slots are reused
// across calls. Calls in fixed order40BE80,40BD80,409260,4093E0,4030D0,409530,4031F0 with block. If deadline+1256 armed and (mode!=3 OR both splitscreen/runtime bytes0),
// calls410920(owner,block+1260) before testing expiry and resetting deadline. Deadline+1204 elapsed EXACT AL1 toggles flags DWORD+1328 mask0x8000: set->clear WITHOUT reset/rearm,
// clear->set and rearm inclusive100..600 milliseconds. Therefore a still-expired clear phase can set/rearm next update. Conditional corpse reaction requires global681E38 nonnull, its
// DWORD+2000 mask0x10000, shared alarm AL0, and block deadline+1208 elapsed EXACT1. Rearms+1208 with200ms BEFORE skipping modes7/16/1. Resolves global entity carried-corpse
// handle+1884; if found copies global COMMON position+60 into corpse COMMON+60 only (no physics/bounds publication). Scans corpse list next+652: fast distance test checks x87 C0
// only, admitting distance<DOUBLE40 OR UNORDERED; then4024E0(owner,corpse) nonzero AL and collision query(owner+2004,corpse+60,FLOAT0.5,3,owner,corpse,NULL)==AL0. First passing
// corpse breaks loop: if owner weapon+676!=-1 OR AI flags+1328 mask0x800, calls40B2D0 then40BA80(block,global handle+44); otherwise calls40AC80(block,global handle,random
// FLOAT60..120). No retry after delegate rejection. Computes unused float32(global seconds clock6FC428-block FLOAT+664), calls4095D0. If final mode1 and owner not
// local-player-or-related predicate, stops weapon firing(owner handle+44,block weapon+4), then returns incidental result of403350(block). No own inactive/dead or multiplayer
// authority admission beyond stated gates.
char __cdecl rf_ai_update_one_block(int *Character)
{
  char result; // al
  float v2; // [esp+10h] [ebp-2Ch]
  float v3[3]; // [esp+14h] [ebp-28h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-1Ch] BYREF
  float v5; // [esp+2Ch] [ebp-10h]
  int v6; // [esp+30h] [ebp-Ch]
  int i; // [esp+34h] [ebp-8h]
  float v8; // [esp+38h] [ebp-4h]

  result = byte_6663D1;
  if ( byte_6663D1 != 1 )
  {
    if ( !Character[160] )
      sub_40A2A0(Character);
    rf_ai_clear_frame_control_fields((int)Character);
    rf_vector3_zero_return_destination((float *)Character + 320);
    sub_4042E0((float *)Character);
    if ( (unsigned int)Character[160] >= 2 )
      rf_ai_scan_projectile_and_entity_reactions(Character);
    if ( rf_vector_length_squared((float *)Character + 320) > 0.00001 )
    {
      rf_vector_copy((float *)Character + 285, copy_result, (const float *)Character + 320);
      rf_matrix3_inverse_rotate_vector((float *)Character + 285, (float *)(*Character + 72));
    }
    rf_float_clamp_in_place((float *)Character + 285, -1.0, 1.0);
    rf_float_clamp_in_place((float *)Character + 286, -1.0, 1.0);
    rf_float_clamp_in_place((float *)Character + 287, -1.0, 1.0);
    rf_ai_spawn_elapsed_projectiles(Character);
    sub_40BD80(Character);
    rf_ai_update_idle_to_ready_transition(Character);
    rf_ai_update_ready_to_idle_transition(Character);
    rf_ai_play_global_elapsed_mode3_speech(Character);
    rf_ai_update_unholster_deadlines((int)Character);
    rf_ai_consume_multiplayer_jump_request(Character);
    if ( rf_replicator_is_armed(Character + 314)
      && (Character[160] != 3 || !(rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode)) )
    {
      sub_410920(*Character, (const float *)Character + 315);
      if ( rf_replicator_has_elapsed(Character + 314) )
        rf_replicator_reset(Character + 314);
    }
    if ( rf_replicator_has_elapsed(Character + 301) )
    {
      if ( (Character[332] & 0x8000) != 0 )
      {
        Character[332] &= ~0x8000u;
      }
      else
      {
        Character[332] |= 0x8000u;
        rf_timestamp_arm_random_inclusive_milliseconds(Character + 301, 100, 600);
      }
    }
    if ( dword_681E38 )
    {
      if ( (*(_DWORD *)(dword_681E38 + 2000) & 0x10000) != 0
        && !rf_alarm_get_shared_active()
        && rf_replicator_has_elapsed(Character + 302) )
      {
        rf_replicator_arm_milliseconds(Character + 302, 200);
        if ( Character[160] != 7 && Character[160] != 16 && Character[160] != 1 )
        {
          v6 = rf_corpse_resolve_handle_type7(*(_DWORD *)(dword_681E38 + 1884));
          if ( v6 )
            rf_vector_copy((float *)(v6 + 60), v3, (const float *)(dword_681E38 + 60));
          for ( i = rf_corpse_list_head; (_UNKNOWN *)i != &unk_681AF8; i = *(_DWORD *)(i + 652) )
          {
            v5 = rf_vector_fast_distance((const float *)(*Character + 60), (const float *)(i + 60));
            if ( v5 < 40.0
              && sub_4024E0(*Character, i)
              && !rf_segment_objects_or_world_hit_filtered_by_radius(
                    *Character + 2004,
                    i + 60,
                    0.5,
                    3,
                    *Character,
                    i,
                    0) )
            {
              if ( *(_DWORD *)(*Character + 676) != -1 || (Character[332] & 0x800) != 0 )
              {
                sub_40B2D0(Character);
                sub_40BA80(Character, *(_DWORD *)(dword_681E38 + 44));
              }
              else
              {
                v2 = rf_random_float_range(60.0, 120.0);
                sub_40AC80(Character, *(_DWORD *)(dword_681E38 + 44), v2);
              }
              break;
            }
          }
        }
      }
    }
    v8 = *(float *)&dword_6FC428 - *((float *)Character + 166);
    rf_ai_scan_close_unholstered_candidates(Character);
    if ( Character[160] == 1 && !rf_entity_matches_local_player_or_related_handle(*Character) )
      rf_entity_stop_weapon_firing(*(_DWORD *)(*Character + 44), Character[1]);
    return rf_ai_consume_route_refresh_request(Character);
  }
  return result;
}

