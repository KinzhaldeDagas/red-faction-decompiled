// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004119E0 rf_camera_update_slot_by_numeric_state
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required three-DWORD camera slot). At ENTRY resolves slotDWORD1 player with4E0760 monitor/view fallback (which may mutate
// player view handle even for states not using result), captures slotDWORD0 camera, then dispatches slotDWORD2 using UNSIGNED<=7 table411DA4; state3, values>7 and negative DWORDs
// take default final refresh. State0 only if captured view ENTITY exists: camera+60=view+2004, camera matrix+72=view+72, camera matrix+2016=view+2016, then411DD0(slot) which
// RE-RESOLVES player and may modify camera retained-forward+2040/orientation+2016 from its timed cone path; result ignored. State1 requires captured view entity: camera+60=view+2004
// + (camera vector+520 ROW-VECTOR times view matrix+2016); camera matrices+72/+2016 become camera relative matrix+532 LEFT-multiplied by view matrices+72/+2016 respectively
// through413070(out=L*R), each followed by55B770 basis rebuild. No FOV/cone helper in state1. States2/4: componentwise sums camera vectors+2148 and+2172, EACH roundedfloat32, build
// pitch/heading basis through4DA050 and copy ONLY to camera+2016; set roomNULL and cache position via4BC210. State5: copy active-cutscene position to camera+60 and orientation to
// camera+72 (476D50 gets ONE pushed destination pointer, caller pops4); then camera+2004=camera+60, camera+2016=camera+72, invoke411DD0(slot), ignore returns. State6: resolve
// global87C31C as COMMON object. If found, subtract unchecked selected vector sample at666AD0[index666A98] from target COMMON position+60, unchecked reciprocal-sqrt normalize and
// construct orientation; otherwise copy selected matrix sample666AB8[same raw index]. Copy orientation to camera+2016 and selected vector to camera+60, set roomNULL/cache. No array
// count/capacity/index check or sample advance; no target entity-type restriction. State7: in-place rotate camera+60 about global pivot666AC4 with axis(0,1,0),
// angle=float32(frameDeltaSeconds*DOUBLE -0.7853981852531433); then unchecked normalize(pivot-camera+60), build camera+2016 orientation, set roomNULL/cache. No own finite/coincident
// safeguards; math delegates retain native degeneracies. ALL paths, including missing view/default, call4BC240(ECX=captured camera) final refresh. Final EAX is its newly masked
// common flags+124 with04000000 cleared, not a normalized success or slot-state value. State0/1 omit explicit roomNULL setter, states2/4/6/7 use it, state5 uses final refresh only.
// No slot-state mutation here, no rollback or own pointer validation; failures after earlier pose writes leave partial changes.
unsigned int __cdecl rf_camera_update_slot_by_numeric_state(void **a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  const float *v5; // eax
  const float *v6; // eax
  const float *v7; // eax
  const float *v8; // eax
  float v10; // [esp+Ch] [ebp-128h]
  float v11; // [esp+10h] [ebp-124h]
  float v12; // [esp+14h] [ebp-120h]
  float v13; // [esp+18h] [ebp-11Ch]
  float v14[3]; // [esp+20h] [ebp-114h] BYREF
  float v15[3]; // [esp+2Ch] [ebp-108h] BYREF
  _BYTE v16[36]; // [esp+38h] [ebp-FCh] BYREF
  float v17[9]; // [esp+5Ch] [ebp-D8h] BYREF
  float v18[9]; // [esp+80h] [ebp-B4h] BYREF
  float v19[3]; // [esp+A4h] [ebp-90h] BYREF
  float sum_result[3]; // [esp+B0h] [ebp-84h] BYREF
  float v21[3]; // [esp+BCh] [ebp-78h] BYREF
  float copy_result[3]; // [esp+C8h] [ebp-6Ch] BYREF
  float v23[3]; // [esp+D4h] [ebp-60h] BYREF
  int v24[3]; // [esp+E0h] [ebp-54h] BYREF
  float out_vector[3]; // [esp+ECh] [ebp-48h] BYREF
  float v26[9]; // [esp+F8h] [ebp-3Ch] BYREF
  int v27; // [esp+11Ch] [ebp-18h]
  float v28[3]; // [esp+120h] [ebp-14h] BYREF
  const float *v29; // [esp+12Ch] [ebp-8h]
  void *v30; // [esp+130h] [ebp-4h]

  v29 = (const float *)rf_player_resolve_view_entity_with_monitor_fallback((int)a1[1]);
  v30 = *a1;
  switch ( (unsigned int)a1[2] )
  {
    case 0u:
      if ( v29 )
      {
        rf_vector_copy((float *)v30 + 15, copy_result, v29 + 501);
        rf_matrix3_copy((float *)v30 + 18, v29 + 18);
        rf_matrix3_copy((float *)v30 + 504, v29 + 504);
        sub_411DD0((int *)a1);
      }
      break;
    case 1u:
      if ( v29 )
      {
        v1 = rf_matrix3_rotate_vector((float *)v30 + 130, v21, (float *)v29 + 504);
        v2 = rf_vector_add(v29 + 501, sum_result, v1);
        rf_vector_copy((float *)v30 + 15, v19, v2);
        v3 = rf_matrix3_argument_times_receiver_to_output(v29 + 18, v18, (const float *)v30 + 133);
        rf_matrix3_copy((float *)v30 + 18, v3);
        rf_matrix3_rebuild_basis_from_forward_in_place((char *)v30 + 72);
        v4 = rf_matrix3_argument_times_receiver_to_output(v29 + 504, v17, (const float *)v30 + 133);
        rf_matrix3_copy((float *)v30 + 504, v4);
        rf_matrix3_rebuild_basis_from_forward_in_place((char *)v30 + 2016);
      }
      break;
    case 2u:
    case 4u:
      v13 = *((float *)v30 + 539) + *((float *)v30 + 545);
      v12 = *((float *)v30 + 538) + *((float *)v30 + 544);
      v11 = *((float *)v30 + 537) + *((float *)v30 + 543);
      rf_vector3_set_components_return_destination(v28, v11, v12, v13);
      v5 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v16, v28);
      rf_matrix3_copy((float *)v30 + 504, v5);
      rf_object_set_room_and_cache_position((float *)v30, 0);
      break;
    case 5u:
      rf_cutscene_copy_active_position((float *)v30 + 15);
      rf_cutscene_copy_active_orientation((float *)v30 + 18);
      rf_vector_copy((float *)v30 + 501, v15, (const float *)v30 + 15);
      rf_matrix3_copy((float *)v30 + 504, (const float *)v30 + 18);
      sub_411DD0((int *)a1);
      break;
    case 6u:
      rf_matrix3_construct((char *)v26);
      v27 = rf_object_resolve_handle(dword_87C31C);
      if ( v27 )
      {
        v6 = (const float *)rf_vector_array12_element_address_unchecked(dword_666AD0, unk_666A98);
        rf_vector_subtract((const float *)(v27 + 60), out_vector, v6);
        rf_vector_normalize_reciprocal_sqrt(out_vector);
        rf_orientation_matrix_from_normalized_direction(v26, out_vector);
      }
      else
      {
        v7 = (const float *)rf_matrix_array36_element_address_unchecked(dword_666AB8, unk_666A98);
        rf_matrix3_copy(v26, v7);
      }
      rf_matrix3_copy((float *)v30 + 504, v26);
      v8 = (const float *)rf_vector_array12_element_address_unchecked(dword_666AD0, unk_666A98);
      rf_vector_copy((float *)v30 + 15, v14, v8);
      rf_object_set_room_and_cache_position((float *)v30, 0);
      break;
    case 7u:
      rf_vector3_default_construct_noop(v24);
      rf_vector3_set_components_thiscall((float *)v24, 0.0, 1.0, 0.0);
      v10 = rf_frame_delta_seconds * -0.7853981852531433;
      rf_point_rotate_about_axis_pivot((int)v30 + 60, (int)v30 + 60, v10, (int)&flt_666AC4, (int)v24);
      rf_vector_subtract(&flt_666AC4, v23, (const float *)v30 + 15);
      rf_vector_normalize_reciprocal_sqrt(v23);
      rf_orientation_matrix_from_normalized_direction((float *)v30 + 504, v23);
      rf_object_set_room_and_cache_position((float *)v30, 0);
      break;
    default:
      return rf_object_refresh_room_cache_and_audio(v30);
  }
  return rf_object_refresh_room_cache_and_audio(v30);
}

