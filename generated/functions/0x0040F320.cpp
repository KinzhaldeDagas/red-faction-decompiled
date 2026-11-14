// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040F320 sub_40F320
// UNREALRED VERIFIED [combat-panic-20261104]: Mode17 ordinary branch advances previous/current indices through40FD30; exhaustion installs cached endpoint hints then409950→40EAB0 and continues with rebuiltroute SAMEcall. Width-aware corner interpolation uses inherited route+15C and lateral+158 sequence; keeps original/workingnodepositions distinct. Movement admission includes40E830 containment, not just30cm threshold. Unsupported mover/vehicle/specialstate branches must be explicit rather than generic pathfollowing substitutes.
// UNREALRED VERIFIED [combat-panic-bounds-20261104]: Arrival distance ordinary default float0.3; fighter predicate40D2C0(class flags+724 bit800) sets2; jeep bit400000 or APC predicate4107D0(bit200) sets3; final linked_eye class flags2+728 bit40 overrides to0.5 when common+78<=2.5, otherwise1.3. common+78 is model sphere radius plus center length from4BC000, not movement radius/capsule.
// UNREALRED VERIFIED [combat-panic-movement-20261111-clarified]: Ordinary route-coordinate admission v43 derives from current descriptor858 through437F60/437FD0: exclude native IDs12,15,13,11,9,4,7; all other defined canonical IDs are ordinary. This is not class default Movemode==run, nor humanoid/modelkind. Unknown-name null and an undefined fallback record are separate pointer/payload cases; a host may explicitly decline them, but must not label that decline a native no-route result.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] At each reached full segment mode10 replans40E030 to CURRENT global player common+3C BEFORE40FD30 indexadvance. Native rebuild failure writessecondary12/rearmsAI2301000/reset; successful >=3-node rebuild advances freshly initialized current1→2. End arrival409950 case10 writessecondary0, leaves route storage; not panic random renewal.
// UNREALRED VERIFIED [combat-route-operands-20261111] MP reached-segment odd raw rand%2 branch xor8 at40F548 writes Entity7D0, alias embeddedAI530. No second entity flag field is required. Distinguish Entity814 flags2 (43BFA0 bit20) from this same-owner alias.
// UNREALRED VERIFIED [original-goto-mode2-route-20261112]: Ordinary numeric2 reached-full-segment behavior differs from10: current path node equal embedded end skips rebuilding; other reached nodes rebuild toward persisted Entity6EC. Mode10 instead always rebuilds toward current global player common3C. Native2 rebuild failure writes secondary12, arms1000 and resets same route. At exhausted path409950 case2 runs common arrival prefix once, resets same embedded route, writes secondary0 and restores saved state; these own reset mutations are not a different route owner.
char __cdecl sub_40F320(int a1, float *destination)
{
  float *v3; // eax
  double v4; // st7
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v9; // [esp+8h] [ebp-ECh]
  float v10; // [esp+8h] [ebp-ECh]
  float scalar; // [esp+Ch] [ebp-E8h]
  float *scalara; // [esp+Ch] [ebp-E8h]
  int scalarb; // [esp+Ch] [ebp-E8h]
  float scalarc; // [esp+Ch] [ebp-E8h]
  float v15; // [esp+10h] [ebp-E4h]
  float v16[3]; // [esp+14h] [ebp-E0h] BYREF
  float v17[3]; // [esp+20h] [ebp-D4h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-C8h] BYREF
  float v19[3]; // [esp+38h] [ebp-BCh] BYREF
  float v20[3]; // [esp+44h] [ebp-B0h] BYREF
  float v21[3]; // [esp+50h] [ebp-A4h] BYREF
  float scaled_result[3]; // [esp+5Ch] [ebp-98h] BYREF
  float v23[3]; // [esp+68h] [ebp-8Ch] BYREF
  float out_vector[3]; // [esp+74h] [ebp-80h] BYREF
  float v25[3]; // [esp+80h] [ebp-74h] BYREF
  float copy_result[3]; // [esp+8Ch] [ebp-68h] BYREF
  float v27; // [esp+98h] [ebp-5Ch]
  int v28; // [esp+9Ch] [ebp-58h] BYREF
  float v29; // [esp+A0h] [ebp-54h]
  int v30; // [esp+A4h] [ebp-50h]
  float v31[3]; // [esp+A8h] [ebp-4Ch] BYREF
  int v33; // [esp+B8h] [ebp-3Ch]
  int v34; // [esp+BCh] [ebp-38h]
  float *rhs; // [esp+C0h] [ebp-34h]
  float vector[3]; // [esp+C4h] [ebp-30h] BYREF
  float v37; // [esp+D0h] [ebp-24h]
  int v38; // [esp+D4h] [ebp-20h]
  float v39; // [esp+D8h] [ebp-1Ch]
  float v40; // [esp+DCh] [ebp-18h]
  float v41[3]; // [esp+E0h] [ebp-14h] BYREF
  float *lhs; // [esp+ECh] [ebp-8h]
  char v43; // [esp+F3h] [ebp-1h]

  if ( !a1 )
  {
    rf_vector3_zero_return_destination(destination);
    return 0;
  }
  lhs = *(float **)(a1 + 4 * *(_DWORD *)(a1 + 24) + 4);
  v38 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 304));
  if ( !v38 )
  {
    rf_vector_copy(destination, copy_result, lhs);
    return 0;
  }
  v43 = 0;
  rf_vector3_copy_return_destination(v41, (float *)(v38 + 2004));
  if ( !rf_entity_descriptor_mode_is_12_15_13_11_or9(v38) && !rf_entity_movement_is_index4_or7(v38) )
  {
    v43 = 1;
    v41[1] = lhs[1];
  }
  scalar = rf_vector_distance((const float *)(v38 + 60), destination);
  v9 = rf_vector_distance(lhs, v41);
  v39 = rf_float_minimum_two_values(v9, scalar);
  v40 = 0.30000001;
  if ( rf_entity_class_flags724_has_mask800(v38) )
    v40 = 2.0;
  if ( rf_entity_has_jeep_flag(v38) || rf_entity_class_has_contact_geomod_flag200(v38) )
    v40 = 3.0;
  if ( (*(_DWORD *)(*(_DWORD *)(v38 + 660) + 1832) & 0x40) != 0 )
  {
    if ( *(float *)(v38 + 120) <= 2.5 )
      v40 = 0.5;
    else
      v40 = 1.3;
  }
  if ( *(_BYTE *)(a1 + 348) != 1
    || v40 <= (double)v39 && sub_40E830((float *)(v38 + 60), *(float *)(v38 + 1984), *(float *)(v38 + 1988), v43, lhs) )
  {
LABEL_73:
    if ( !*(_DWORD *)(a1 + 276) )
      return 0;
    lhs = *(float **)(a1 + 4 * *(_DWORD *)(a1 + 24) + 4);
    rhs = *(float **)(a1 + 4 * *(_DWORD *)(a1 + 20) + 4);
    rf_vector_copy(destination, v25, lhs);
    if ( v43 == 1 )
      destination[1] = *(float *)(v38 + 2008);
    scalara = rf_vector3_set_components_return_destination(v23, 0.0, 1.0, 0.0);
    v3 = rf_vector_subtract(lhs, out_vector, rhs);
    rf_vector_cross(v3, vector, scalara);
    rf_vector_normalize(vector);
    v4 = rf_float_minimum_two_values(lhs[7], rhs[7]);
    v37 = v4 - *(float *)(v38 + 1984);
    if ( v37 < 0.0 )
      v37 = 0.0;
    v15 = v37 * *(float *)(a1 + 344);
    v5 = rf_vector_multiply_scalar(vector, scaled_result, v15);
    rf_vector_copy(vector, v21, v5);
    rf_vector_accumulate(destination, vector);
    if ( !*(_BYTE *)(a1 + 348) )
    {
      v29 = rf_vector_distance(lhs, rhs);
      if ( v29 > 0.0 )
      {
        v27 = rhs[7] - *(float *)(v38 + 1984);
        if ( v27 < 0.0 )
          v27 = 0.0;
        *(float *)&v28 = v27 / v29;
        rf_float_clamp_in_place((float *)&v28, 0.0, 1.0);
        scalarb = v28;
        v6 = rf_vector_subtract(lhs, v20, rhs);
        v7 = rf_vector_multiply_scalar(v6, v19, *(float *)&scalarb);
        v8 = rf_vector_add(rhs, sum_result, v7);
        rf_vector_copy(destination, v17, v8);
        rf_vector_accumulate(destination, vector);
        if ( v43 == 1 )
          destination[1] = *(float *)(v38 + 2008);
        scalarc = rf_vector_distance((const float *)(v38 + 60), destination);
        v10 = rf_vector_distance((const float *)(v38 + 2004), destination);
        v29 = rf_float_minimum_two_values(v10, scalarc);
        if ( v40 > (double)v29 )
        {
          rf_vector_copy(destination, v16, lhs);
          rf_vector_accumulate(destination, vector);
          if ( v43 == 1 )
            destination[1] = *(float *)(v38 + 2008);
          if ( *(_DWORD *)(v38 + 1312) == 7 || *(_DWORD *)(v38 + 1312) == 12 )
          {
            *(_DWORD *)(a1 + 276) = *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 20) + 4);
            *(_DWORD *)(a1 + 280) = *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 24) + 4);
          }
          *(_BYTE *)(a1 + 348) = 1;
        }
      }
    }
    return 1;
  }
  *(_BYTE *)(a1 + 348) = 0;
  if ( (rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active) && rand() % 2 )
  {
    v34 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 304));
    v33 = v34 + 672;
    *(_DWORD *)(v34 + 2000) ^= 8u;
  }
  switch ( *(_DWORD *)(v38 + 1312) )
  {
    case 3:
      if ( rf_object_resolve_handle(*(_DWORD *)(v38 + 1376)) )
      {
        if ( *(_DWORD *)(v38 + 1364) != 11 )
        {
          rf_vector3_default_construct_noop(v31);
          rf_ai_copy_route_target_position(v38 + 672, v31);
          if ( !rf_ai_route_build(*(_DWORD *)(v38 + 44), v31) )
          {
            rf_ai_route_reset(v38 + 1416);
            return 0;
          }
        }
      }
LABEL_54:
      if ( *(_DWORD *)(v38 + 1312) != 7 && *(_DWORD *)(v38 + 1312) != 12 )
      {
        if ( rf_route_record_advance_next_index((_DWORD *)a1) == -1 )
        {
          if ( *(_DWORD *)(a1 + 4 * *(_DWORD *)a1) == a1 + 152 )
          {
            if ( rf_receiver_get_first_dword((void *)(a1 + 192)) == 2 )
            {
              *(_DWORD *)(a1 + 276) = *(_DWORD *)sub_552200((_DWORD *)(a1 + 192), 0);
              *(_DWORD *)(a1 + 280) = *(_DWORD *)sub_552200((_DWORD *)(a1 + 192), 1);
            }
            else if ( rf_receiver_get_first_dword((void *)(a1 + 192)) == 1 )
            {
              *(_DWORD *)(a1 + 276) = *(_DWORD *)sub_552200((_DWORD *)(a1 + 192), 0);
              *(_DWORD *)(a1 + 280) = 0;
            }
          }
          else
          {
            *(_DWORD *)(a1 + 276) = *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 24) + 4);
            *(_DWORD *)(a1 + 280) = 0;
          }
          sub_409950((int *)(v38 + 672));
          if ( *(_DWORD *)(a1 + 24) == -1 || *(_DWORD *)(a1 + 20) == -1 )
            return 0;
        }
        else if ( *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 24) + 4) == a1 + 152 )
        {
          if ( rf_receiver_get_first_dword((void *)(a1 + 192)) == 2 )
          {
            *(_DWORD *)(a1 + 276) = *(_DWORD *)sub_552200((_DWORD *)(a1 + 192), 0);
            *(_DWORD *)(a1 + 280) = *(_DWORD *)sub_552200((_DWORD *)(a1 + 192), 1);
          }
          else if ( rf_receiver_get_first_dword((void *)(a1 + 192)) == 1 )
          {
            *(_DWORD *)(a1 + 276) = *(_DWORD *)sub_552200((_DWORD *)(a1 + 192), 0);
            *(_DWORD *)(a1 + 280) = 0;
          }
        }
        else
        {
          *(_DWORD *)(a1 + 276) = *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 20) + 4);
          *(_DWORD *)(a1 + 280) = *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 24) + 4);
        }
      }
      goto LABEL_73;
    case 7:
    case 0xC:
      *(_DWORD *)(a1 + 276) = *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 24) + 4);
      *(_DWORD *)(a1 + 280) = 0;
      v30 = rf_object_resolve_handle(*(_DWORD *)(v38 + 1376));
      if ( !v30 )
        goto LABEL_54;
      rf_ai_build_avoid_route_with_target_adjustment(*(_DWORD *)(v38 + 44), (float *)(v30 + 60));
      if ( *(int *)a1 > 2 )
      {
        *(_BYTE *)(a1 + 348) = 0;
        *(_DWORD *)(a1 + 20) = 1;
        *(_DWORD *)(a1 + 24) = 2;
        goto LABEL_54;
      }
      rf_replicator_arm_milliseconds((int *)(v38 + 1232), 1000);
      rf_ai_route_reset(v38 + 1416);
      if ( *(_DWORD *)(v38 + 1312) == 7 )
        rf_ai_selected_weapon_projectile_retarget_or_delay((int *)(v38 + 672));
      return 0;
    case 4:
      if ( sub_40DCA0(*(_DWORD *)(v38 + 44)) )
        goto LABEL_54;
      goto LABEL_41;
  }
  if ( *(_DWORD *)(v38 + 1312) != 6 && *(_DWORD *)(v38 + 1312) != 2 && *(_DWORD *)(v38 + 1312) != 16 )
  {
    if ( *(_DWORD *)(v38 + 1312) != 10 || rf_ai_route_build(*(_DWORD *)(v38 + 44), (float *)(dword_681E38 + 60)) )
      goto LABEL_54;
LABEL_41:
    rf_ai_secondary_state_write(v38 + 672, 12);
    rf_replicator_arm_milliseconds((int *)(v38 + 1232), 1000);
    rf_ai_route_reset(v38 + 1416);
    return 0;
  }
  if ( *(_DWORD *)(v38 + 4 * *(_DWORD *)(v38 + 1440) + 1420) == v38 + 1568
    || rf_ai_route_build(*(_DWORD *)(v38 + 44), (float *)(v38 + 1772)) )
  {
    goto LABEL_54;
  }
  if ( *(_DWORD *)(v38 + 1312) != 16 )
    rf_ai_secondary_state_write(v38 + 672, 12);
  rf_replicator_arm_milliseconds((int *)(v38 + 1232), 1000);
  rf_ai_route_reset(v38 + 1416);
  return 0;
}

