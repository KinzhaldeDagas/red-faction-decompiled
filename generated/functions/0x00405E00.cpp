// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405E00 rf_ai_mode12_target_geometry_and_reload_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, owner entity DWORD+0; central numeric mode12 handler. Resolves target+704 as ENTITY;
// missing returns resolver0 without clearing target/mode. Secondary+692==1: copy owner retained point+2004, subtract class FLOAT(+660)->+3956 from copied Y (float32).
// Geometry(owner+2004,target+2004,mask17,NULL)==EXACT AL1 writes AI DWORD+588=2, resets route+744, sets flags+1328 mask0x4000. Otherwise4354D0(owner)==EXACT1 plus geometry(lowered
// point,target+2004,17,NULL)==EXACT1 writes+588=1, calls crouch436100, resets route and sets same mask. Neither geometry branch: route-update native stack(route+744,extra1), clean8;
// signed EAX>-1 exits ENTIRE function before probes/look/weapon work, all other values continue. Reached fallback writes secondary0 and arms+572 inclusive2000..5000ms. Then
// runs4025D0(block,target), movement-dependent target point4010E0,410920(owner,point), discardsST0. Crouch any-nonzero plus BYTE+669==EXACT1 (tested twice natively) rearms+572
// inclusive1500..2500. Independently noncrouch, DWORD+588==1 and BOTH bytes+669/+668==0 rearms same interval. Finally +572 elapsed EXACT1 and+588==1 toggle mask0x4000: set->clear and
// rearm1500..2500; clear->set and same rearm, then reload-request(owner,0,0) regardless of return. Calls401670(block) last. No own runtime/authority/dead gate; AL/EAX incidental on
// non-missing paths.
char __cdecl rf_ai_mode12_target_geometry_and_reload_update(int *a1)
{
  int v1; // eax
  float v3; // [esp+0h] [ebp-1Ch] BYREF
  float v4; // [esp+4h] [ebp-18h]
  float target_point[3]; // [esp+Ch] [ebp-10h] BYREF
  int v6; // [esp+18h] [ebp-4h]

  v1 = rf_entity_resolve_handle(a1[176]);
  v6 = v1;
  if ( v1 )
  {
    if ( a1[173] == 1 )
    {
      rf_vector3_copy_return_destination(&v3, (float *)(*a1 + 2004));
      v4 = v4 - *(float *)(*(_DWORD *)(*a1 + 660) + 3956);
      if ( rf_geometry_segment_is_obstructed(*a1 + 2004, v6 + 2004, 17, 0) == 1 )
      {
        a1[147] = 2;
        rf_ai_route_reset((int)(a1 + 186));
        a1[332] |= 0x4000u;
      }
      else if ( rf_entity_has_record_at974_or964(*a1)
             && rf_geometry_segment_is_obstructed((int)&v3, v6 + 2004, 17, 0) == 1 )
      {
        a1[147] = 1;
        rf_entity_apply_crouch_shape_centers(*a1);
        rf_ai_route_reset((int)(a1 + 186));
        a1[332] |= 0x4000u;
      }
      else
      {
        v1 = rf_ai_route_update((int)(a1 + 186));
        if ( v1 > -1 )
          return v1;
      }
      rf_ai_secondary_state_write((int)a1, 0);
      rf_timestamp_arm_random_inclusive_milliseconds(a1 + 143, 2000, 5000);
    }
    rf_ai_refresh_target_collision_and_corridor_probes(a1, v6);
    rf_vector3_default_construct_noop(target_point);
    rf_ai_copy_target_point_for_current_movement(a1, v6, target_point);
    sub_410920(*a1, target_point);
    if ( rf_entity_is_crouched_state810(*a1) && *((_BYTE *)a1 + 669) == 1 )
      rf_timestamp_arm_random_inclusive_milliseconds(a1 + 143, 1500, 2500);
    if ( !rf_entity_is_crouched_state810(*a1) && a1[147] == 1 && !*((_BYTE *)a1 + 669) && !*((_BYTE *)a1 + 668) )
      rf_timestamp_arm_random_inclusive_milliseconds(a1 + 143, 1500, 2500);
    if ( rf_replicator_has_elapsed(a1 + 143) && a1[147] == 1 )
    {
      if ( (a1[332] & 0x4000) != 0 )
      {
        a1[332] &= ~0x4000u;
        rf_timestamp_arm_random_inclusive_milliseconds(a1 + 143, 1500, 2500);
      }
      else
      {
        a1[332] |= 0x4000u;
        rf_timestamp_arm_random_inclusive_milliseconds(a1 + 143, 1500, 2500);
        rf_weapon_reload_request(*a1, 0, 0);
      }
    }
    LOBYTE(v1) = rf_ai_dispatch_selected_primary_weapon_action(a1);
  }
  return v1;
}

