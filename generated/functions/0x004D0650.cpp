// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D0650 rf_segment_objects_or_world_hit_filtered_by_radius
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl start,end,minimum object radius,public flags,ignored object pointer A,ignored object pointer B,optional world-result pointer. Builds model query: position0,matrix12,start48,direction60,radius72=0,flags76=(public mask1?1:0); original start/direction saved separately. Third float is an ADMISSION threshold against object float384, not swept radius. Iterates entities(head68211C,sentinel681E90),clutter(sentinel666D18),corpses(sentinel681AF8),next652. Threshold<=object384 OR unordered admits; inactive predicate AL EXACT1 rejects; pointer matches either ignored object reject; AABB400/412 tests original start/end. Entities/corpses also reject flags124 mask2; clutter does not. Uses object physics
// position228/orientation252 and model128, no own model NULL check. Each model call initializeByte1 seeds result fraction0=1 and extra28=0 via delegate, then ORs returned AL into aggregate. Any aggregate hit with public mask1 returns1 BEFORE world query, leaving optional world-result untouched. Otherwise query flags76 mask2 restores original model-query start/direction and clears mask2. Clutter path additionally overwrites query direction with SAVED original direction*that call result fraction after EVERY admitted model call, even on miss, before optional mask2 restoration; entity/corpse paths do not perform that extra scale. After all lists always calls geometry_segment_is_obstructed(original start,end,public flags,world-result), ORs its byte with aggregate. Object narrow-phase point/normal/fraction is NOT copied to optional world-result. No nearest-object result contract, cycle, finite
// or ownership validation.
char __cdecl rf_segment_objects_or_world_hit_filtered_by_radius(
        float *rhs,
        float *lhs,
        float a3,
        char a4,
        int a5,
        int a6,
        float *a7)
{
  float *v7; // eax
  char v8; // bl
  char v10; // bl
  float *v11; // eax
  char v12; // bl
  char v13; // bl
  float v14[3]; // [esp+8h] [ebp-164h] BYREF
  float v15[3]; // [esp+14h] [ebp-158h] BYREF
  float v16[3]; // [esp+20h] [ebp-14Ch] BYREF
  float v17[3]; // [esp+2Ch] [ebp-140h] BYREF
  float v18[3]; // [esp+38h] [ebp-134h] BYREF
  float v19[3]; // [esp+44h] [ebp-128h] BYREF
  float scaled_result[3]; // [esp+50h] [ebp-11Ch] BYREF
  float v21[3]; // [esp+5Ch] [ebp-110h] BYREF
  float v22[3]; // [esp+68h] [ebp-104h] BYREF
  float v23[3]; // [esp+74h] [ebp-F8h] BYREF
  float v24[3]; // [esp+80h] [ebp-ECh] BYREF
  float v25[3]; // [esp+8Ch] [ebp-E0h] BYREF
  float out_vector[3]; // [esp+98h] [ebp-D4h] BYREF
  float copy_result[3]; // [esp+A4h] [ebp-C8h] BYREF
  int i; // [esp+B0h] [ebp-BCh]
  char v29; // [esp+B7h] [ebp-B5h]
  float v30[3]; // [esp+B8h] [ebp-B4h] BYREF
  float scalar[8]; // [esp+C4h] [ebp-A8h] BYREF
  float v32[3]; // [esp+E4h] [ebp-88h] BYREF
  float v33[9]; // [esp+F0h] [ebp-7Ch] BYREF
  float destination[3]; // [esp+114h] [ebp-58h] BYREF
  float v35[4]; // [esp+120h] [ebp-4Ch] BYREF
  int v36; // [esp+130h] [ebp-3Ch]
  float vector[3]; // [esp+14Ch] [ebp-20h] BYREF
  int j; // [esp+158h] [ebp-14h]
  float source[3]; // [esp+15Ch] [ebp-10h] BYREF
  int k; // [esp+168h] [ebp-4h]

  v29 = 0;
  rf_vector3_default_construct_noop(v30);
  rf_model_collision_query_construct_noop((char *)v32);
  rf_model_collision_result_construct_noop((int)scalar);
  v35[3] = 0.0;
  rf_vector_copy(destination, copy_result, rhs);
  v7 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(v35, v25, v7);
  v36 = (a4 & 1) != 0;
  rf_vector3_copy_return_destination(source, destination);
  rf_vector3_copy_return_destination(vector, v35);
  for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( a3 <= (double)*(float *)(i + 384)
      && !rf_object_has_respawn_inactive_flag(i)
      && (*(_DWORD *)(i + 124) & 2) == 0
      && i != a5
      && i != a6
      && rf_segment_intersects_aabb((float *)(i + 400), (float *)(i + 412), rhs, lhs, v30) )
    {
      rf_vector_copy(v32, v24, (const float *)(i + 228));
      rf_matrix3_copy(v33, (const float *)(i + 252));
      v8 = v29;
      v29 = rf_model_handle_collide_all_adapter(*(_DWORD **)(i + 128), (int)v32, (int)scalar, 1) | v8;
      if ( v29 && (a4 & 1) != 0 )
        return 1;
      if ( (v36 & 2) != 0 )
      {
        rf_vector_copy(destination, v23, source);
        rf_vector_copy(v35, v22, vector);
        v36 &= ~2u;
      }
    }
  }
  for ( j = rf_clutter_list_head; (_UNKNOWN *)j != &unk_666D18; j = *(_DWORD *)(j + 652) )
  {
    if ( a3 <= (double)*(float *)(j + 384)
      && !rf_object_has_respawn_inactive_flag(j)
      && j != a5
      && j != a6
      && rf_segment_intersects_aabb((float *)(j + 400), (float *)(j + 412), rhs, lhs, v30) )
    {
      rf_vector_copy(v32, v21, (const float *)(j + 228));
      rf_matrix3_copy(v33, (const float *)(j + 252));
      v10 = v29;
      v29 = rf_model_handle_collide_all_adapter(*(_DWORD **)(j + 128), (int)v32, (int)scalar, 1) | v10;
      v11 = rf_vector_multiply_scalar(vector, scaled_result, scalar[0]);
      rf_vector_copy(v35, v19, v11);
      if ( v29 && (a4 & 1) != 0 )
        return 1;
      if ( (v36 & 2) != 0 )
      {
        rf_vector_copy(destination, v18, source);
        rf_vector_copy(v35, v17, vector);
        v36 &= ~2u;
      }
    }
  }
  for ( k = rf_corpse_list_head; (_UNKNOWN *)k != &unk_681AF8; k = *(_DWORD *)(k + 652) )
  {
    if ( a3 <= (double)*(float *)(k + 384)
      && !rf_object_has_respawn_inactive_flag(k)
      && (*(_DWORD *)(k + 124) & 2) == 0
      && k != a5
      && k != a6
      && rf_segment_intersects_aabb((float *)(k + 400), (float *)(k + 412), rhs, lhs, v30) )
    {
      rf_vector_copy(v32, v16, (const float *)(k + 228));
      rf_matrix3_copy(v33, (const float *)(k + 252));
      v12 = v29;
      v29 = rf_model_handle_collide_all_adapter(*(_DWORD **)(k + 128), (int)v32, (int)scalar, 1) | v12;
      if ( v29 && (a4 & 1) != 0 )
        return 1;
      if ( (v36 & 2) != 0 )
      {
        rf_vector_copy(destination, v15, source);
        rf_vector_copy(v35, v14, vector);
        v36 &= ~2u;
      }
    }
  }
  v13 = v29;
  return rf_geometry_segment_is_obstructed(rhs, lhs, a4, a7) | v13;
}

