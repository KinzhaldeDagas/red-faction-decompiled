// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D0220 rf_geometry_segment_is_obstructed
// UNREALRED VERIFIED [mission-protection-20261020] UnHide0x501140 uses this segment geometry-obstruction result with mask3 and no output record. Return1 admits show (target obscured by world/type9 geometry); return0 can keep ordinary entity pending. This is not a camera-frustum or character/clutter occlusion query.
// UNREALRED VERIFIED [mission-visibility-20261020] Geometry-only obstruction queries each type9 solid in its current transform plus world solid. UnHide mask3 translates to0x21, world branch also sets query bit4. Characters, clutter and projectiles are not traversed as occluders. The caller admits an ordinary entity when this returns1, not when it returns0.
// UNREALRED VERIFIED [mission-unhide-20261020] Type9 moving-solid traversal does not filter the common inactive bit before querying its current transform. UnrealRed therefore retains hidden moving geometry as an UnHide occluder even while its UE component collision is disabled. World/current edited geometry is queried separately.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Pickup473940 requests PUBLIC mask1, mapping internal flags1 via4D0590. Iterates type9 geometry list/current position+orientation, no inactive-type9 exclusion, then worldsolid with querybit4 added. Any admitted hit returns early because querybit1. No entity/clutter/projectile occluder scan. Outputrecord is null for pickup; boolean obstruction only. A host visibility/UnHide mask3 query is not equivalent.
// UNREALRED VERIFIED (2026-11-11; native output-field refinement): Hit-output writer sets point0..8,normal12..20,fraction24,material28,zero32,zero velocity36..44,UID48,raw material52,face60,zero64, but NEVER writes DWORD56 (liquid/contact field). Misses do not write output. Both mover and world branches skip56 (native4D042A/4D0573 store60 instead). Corpse support41CDC0 uses no-op-constructed local then copies ALL68 bytes on>=2 probes, propagating unwritten local56 into corpse492; do not assume zero/default liquid metadata.
// UNREALRED VERIFIED [original-target-scan-geometry-20261112]:402160 calls this geometry-only wrapper with publicmask3 and null output. It traverses current type9 solid list704BCC->704940, not entity/model occluders; then committed world.4D0590 maps3 to internal21 (world additionally4).52F1B0 rejects see-through face40, not damage face80; point radius has no sphere-edge expansion or alpha sampling. Do not substitute pickupmask1, damage mask5 or4D0650 objects/model trace.
char __cdecl rf_geometry_segment_is_obstructed(float *rhs, float *lhs, char a3, float *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v11[3]; // [esp+4h] [ebp-170h] BYREF
  float v12[3]; // [esp+10h] [ebp-164h] BYREF
  float v13[3]; // [esp+1Ch] [ebp-158h] BYREF
  float v14[3]; // [esp+28h] [ebp-14Ch] BYREF
  float v15[3]; // [esp+34h] [ebp-140h] BYREF
  float sum_result[3]; // [esp+40h] [ebp-134h] BYREF
  float scaled_result[3]; // [esp+4Ch] [ebp-128h] BYREF
  float v18[3]; // [esp+58h] [ebp-11Ch] BYREF
  float v19[3]; // [esp+64h] [ebp-110h] BYREF
  float v20[3]; // [esp+70h] [ebp-104h] BYREF
  float v21[3]; // [esp+7Ch] [ebp-F8h] BYREF
  float v22[3]; // [esp+88h] [ebp-ECh] BYREF
  float v23[3]; // [esp+94h] [ebp-E0h] BYREF
  float out_vector[3]; // [esp+A0h] [ebp-D4h] BYREF
  float copy_result[3]; // [esp+ACh] [ebp-C8h] BYREF
  int v26; // [esp+B8h] [ebp-BCh] BYREF
  float scalar; // [esp+BCh] [ebp-B8h]
  float v28[3]; // [esp+C0h] [ebp-B4h] BYREF
  float source[4]; // [esp+CCh] [ebp-A8h] BYREF
  int v30; // [esp+DCh] [ebp-98h]
  float v31[3]; // [esp+E0h] [ebp-94h] BYREF
  float v32[3]; // [esp+ECh] [ebp-88h] BYREF
  char v33; // [esp+FBh] [ebp-79h]
  char v34[4]; // [esp+FCh] [ebp-78h] BYREF
  float v35[3]; // [esp+100h] [ebp-74h] BYREF
  float v36[9]; // [esp+10Ch] [ebp-68h] BYREF
  float destination[3]; // [esp+130h] [ebp-44h] BYREF
  float vector[4]; // [esp+13Ch] [ebp-38h] BYREF
  int flags; // [esp+14Ch] [ebp-28h]
  int i; // [esp+170h] [ebp-4h]

  rf_vector3_default_construct_noop(v32);
  rf_vector3_copy_return_destination(v31, lhs);
  rf_solid_collision_query_construct_clear_face_hint(v34);
  rf_solid_collision_result_construct_noop((int)&v26);
  v33 = 0;
  rf_vector_copy(destination, copy_result, rhs);
  v4 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(vector, v23, v4);
  vector[3] = 0.0;
  flags = rf_geometry_segment_mask_to_query_flags(a3);
  scalar = 1.0;
  for ( i = unk_704BCC; (_UNKNOWN *)i != &unk_704940; i = *(_DWORD *)(i + 652) )
  {
    if ( rf_segment_intersects_aabb((float *)(i + 400), (float *)(i + 412), rhs, v31, v32) )
    {
      rf_matrix3_copy(v36, (const float *)(i + 72));
      rf_vector_copy(v35, v22, (const float *)(i + 60));
      rf_world_collision_sweep(*(char **)(i + 660), (int)v34, (int)&v26, 0);
      if ( v26 > 0 )
      {
        v33 = 1;
        if ( a4 )
        {
          a4[6] = scalar;
          v5 = rf_matrix3_rotate_vector(source, v21, (float *)(i + 252));
          rf_vector_copy(a4 + 3, v20, v5);
          v6 = rf_matrix3_rotate_vector(v28, v19, (float *)(i + 252));
          rf_vector_copy(a4, v18, v6);
          rf_vector_accumulate(a4, (float *)(i + 228));
          a4[8] = 0.0;
          *((_DWORD *)a4 + 7) = rf_bitmap_material_to_index(*(_DWORD *)(v30 + 48));
          rf_vector3_zero_return_destination(a4 + 9);
          a4[12] = *(float *)(i + 44);
          a4[13] = *(float *)(v30 + 48);
          *((_DWORD *)a4 + 15) = v30;
          a4[16] = 0.0;
        }
        if ( (a3 & 1) != 0 )
          return 1;
        v8 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
        v9 = rf_vector_add(rhs, sum_result, v8);
        rf_vector_copy(v31, v15, v9);
        v10 = rf_vector_subtract(v31, v14, rhs);
        rf_vector_copy(vector, v13, v10);
      }
    }
  }
  flags |= 4u;
  rf_world_collision_sweep((char *)rf_world_solid, (int)v34, (int)&v26, 0);
  if ( v26 > 0 )
  {
    v33 = 1;
    if ( a4 )
    {
      a4[6] = scalar;
      rf_vector_copy(a4 + 3, v12, source);
      rf_vector_copy(a4, v11, v28);
      a4[8] = 0.0;
      *((_DWORD *)a4 + 7) = rf_bitmap_material_to_index(*(_DWORD *)(v30 + 48));
      rf_vector3_zero_return_destination(a4 + 9);
      a4[12] = NAN;
      a4[13] = *(float *)(v30 + 48);
      *((_DWORD *)a4 + 15) = v30;
      a4[16] = 0.0;
    }
  }
  return v33;
}

