// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050D850 rf_projectile_prephysics_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): First decrements F32 lifetime+668 by frame delta unless info flags+612 remote_charge40h. Homing mask00800000 and alt_lock4000h are INDEPENDENT branches: each computes F32 age=info lifetime+176-projectile remaining+668 and requires ORDERED wakeup+316<=age. Homing with target+744=-1 checks timer+748, calls auto-acquire50DDA0 then arms200ms even if acquisition fails; an existing target steers50E020. Alt-lock steers only target!=-1; if both flags apply, steering may run twice in one frame. After steering and successful generic target resolution, ORDERED distance<=3 AND ORDERED dot(forward+96, normalized target displacement)<DOUBLE0.9 AND damage type+1324!=5 sets health+52=-1. Terminal
// handling requires ORDERED remaining<=0 OR ORDERED health<=0 (NaN alone does not expire). Nonmelee additionally needs physics flags+424 mask10000000, homing, alt_lock, remote_charge, torpedo10000h, or grenade ID to present terminal impact. Unless torpedo, calls geomod484E60(radius info+332,projectile UID+44,cached room DWORD0,position+60,normal+448,0,0); result EXACTLY1 triggers point scan505240(native one stack pointer, existing x87 annotation is artifact) and nearby-view impulse50BC70. Except multiplayer mode EXACTLY1 with zero server-authority byte, ORDERED positive info radius+520 applies radial damage4BAA30 at position with5107C0 selector0, owner UID+48, damage code4 for flamethrower else3. Mode1 AND authority EXACTLY1 also sends4B66C0(owner,1). Copies position into collision point+436, clears collision type+464, writes negative forward into normal+448, presents world
// impact50C0C0(projectile,0,1). For remote-charge global911C78 or grenade, scans entity ring68211C/sentinel681E90 through+652: entity+1376 matching projectile UID invokes central AI target setter40BA80(entity+672,owner UID), whose admission can reject. Finally marks deferred deletion for ALL expired projectiles including melee/nonpresented cases. No immediate destruction/free or target clearing.
void __cdecl rf_projectile_prephysics_update(int a1)
{
  int first_dword; // eax
  float *v2; // eax
  BOOL v3; // [esp+1Ch] [ebp-6Ch]
  float v4[3]; // [esp+20h] [ebp-68h] BYREF
  float v5[3]; // [esp+2Ch] [ebp-5Ch] BYREF
  float copy_result[3]; // [esp+38h] [ebp-50h] BYREF
  int i; // [esp+44h] [ebp-44h]
  float selected_damage_with_owner_scale; // [esp+48h] [ebp-40h]
  char v9; // [esp+4Fh] [ebp-39h]
  float v10[3]; // [esp+50h] [ebp-38h] BYREF
  float v11; // [esp+5Ch] [ebp-2Ch]
  float v12; // [esp+60h] [ebp-28h] BYREF
  int v13; // [esp+64h] [ebp-24h]
  float v14; // [esp+68h] [ebp-20h]
  float out_vector[3]; // [esp+6Ch] [ebp-1Ch] BYREF
  float v16; // [esp+78h] [ebp-10h]
  float v17; // [esp+7Ch] [ebp-Ch] BYREF
  int v18; // [esp+80h] [ebp-8h]
  float v19; // [esp+84h] [ebp-4h]

  if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x40) == 0 )
    *(float *)(a1 + 668) = *(float *)(a1 + 668) - rf_frame_delta_seconds;
  if ( ((unsigned int)&unk_800000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 612)) != 0 )
  {
    v19 = *(float *)(*(_DWORD *)(a1 + 660) + 176) - *(float *)(a1 + 668);
    if ( *(float *)(*(_DWORD *)(a1 + 660) + 316) <= (double)v19 )
    {
      if ( *(_DWORD *)(a1 + 744) == -1 )
      {
        if ( rf_replicator_has_elapsed((int *)(a1 + 748)) )
        {
          rf_projectile_auto_acquire_target(a1);
          rf_replicator_arm_milliseconds((int *)(a1 + 748), 200);
        }
      }
      else
      {
        rf_projectile_steer_to_target_preserve_speed(a1, &v17);
        v18 = rf_object_resolve_handle(*(_DWORD *)(a1 + 744));
        if ( v18 )
        {
          rf_vector_subtract((const float *)(v18 + 60), out_vector, (const float *)(a1 + 60));
          rf_vector_normalize_reciprocal_sqrt(out_vector);
          v16 = rf_vector_dot((float *)(a1 + 96), out_vector);
          if ( v17 <= 3.0 && v16 < 0.9 && *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324) != 5 )
            *(float *)(a1 + 52) = -1.0;
        }
      }
    }
  }
  if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x4000) != 0 && *(_DWORD *)(a1 + 744) != -1 )
  {
    v14 = *(float *)(*(_DWORD *)(a1 + 660) + 176) - *(float *)(a1 + 668);
    if ( *(float *)(*(_DWORD *)(a1 + 660) + 316) <= (double)v14 )
    {
      rf_projectile_steer_to_target_preserve_speed(a1, &v12);
      v13 = rf_object_resolve_handle(*(_DWORD *)(a1 + 744));
      if ( v13 )
      {
        rf_vector_subtract((const float *)(v13 + 60), v10, (const float *)(a1 + 60));
        rf_vector_normalize_reciprocal_sqrt(v10);
        v11 = rf_vector_dot((float *)(a1 + 96), v10);
        if ( v12 <= 3.0 && v11 < 0.9 && *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324) != 5 )
          *(float *)(a1 + 52) = -1.0;
      }
    }
  }
  if ( *(float *)(a1 + 668) <= 0.0 || *(float *)(a1 + 52) <= 0.0 )
  {
    if ( !rf_weapon_is_melee(*(_DWORD *)(a1 + 664))
      && ((*(_DWORD *)(a1 + 424) & 0x10000000) != 0
       || ((unsigned int)&unk_800000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 612)) != 0
       || (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x4000) != 0
       || (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x40) != 0
       || (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x10000) != 0
       || *(_DWORD *)(a1 + 664) == rf_weapon_index_grenade) )
    {
      if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x10000) == 0 )
      {
        first_dword = rf_receiver_get_first_dword((void *)a1);
        v9 = rf_geomod_operation_admit(
               *(float *)(*(_DWORD *)(a1 + 660) + 332),
               *(_DWORD *)(a1 + 44),
               first_dword,
               (float *)(a1 + 60),
               (float *)(a1 + 448),
               0,
               0);
        if ( v9 == 1 )
        {
          rf_trigger_weapon_point_scan_all((float *)(a1 + 60));
          rf_projectile_apply_nearby_local_view_impulse(a1);
        }
      }
      v3 = rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority;
      if ( !v3 && *(float *)(*(_DWORD *)(a1 + 660) + 520) > 0.0 )
      {
        selected_damage_with_owner_scale = rf_projectile_get_selected_damage_with_owner_scale(a1, 0);
        rf_damage_apply_radial(
          (float *)(a1 + 60),
          selected_damage_with_owner_scale,
          *(float *)(*(_DWORD *)(a1 + 660) + 520),
          *(_DWORD *)(a1 + 48),
          4 - (rf_weapon_id_flamethrower != *(_DWORD *)(a1 + 664)));
      }
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
        rf_multiplayer_broadcast_remote_charge_kill_packet36(*(_DWORD *)(a1 + 48), 1);
      rf_vector_copy((float *)(a1 + 436), copy_result, (const float *)(a1 + 60));
      *(_DWORD *)(a1 + 464) = 0;
      v2 = rf_vector_negate((float *)(a1 + 96), v5);
      rf_vector_copy((float *)(a1 + 448), v4, v2);
      rf_weapon_present_world_impact((float *)a1, 0, 1);
      if ( *(_DWORD *)(a1 + 664) == dword_911C78 || *(_DWORD *)(a1 + 664) == rf_weapon_index_grenade )
      {
        for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
        {
          if ( *(_DWORD *)(i + 1376) == *(_DWORD *)(a1 + 44) )
            sub_40BA80((int *)(i + 672), *(_DWORD *)(a1 + 48));
        }
      }
    }
    rf_object_mark_for_deferred_delete(a1);
  }
}

