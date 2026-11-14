// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00524990 rf_world_decal_update_volume_and_reproject
// UNREALRED VERIFIED [decal-face-links-20261028]: Replaces decal matrix+12,position+0,dimensions+48,bitmap+60. Rebuilds six clipping planes+92..+187 from final matrix axes and half dimensions, updates broadphase bounds through0x522950, releases all existing attached polygons0x5215D0 then calls general projection dispatcher0x523C40. Does not update owner/context pointers,alpha,flags or scalar; does not gather/clear global candidate faces before reprojection, so dispatcher can use existing global scratch list. No rollback or dimension validation; return is dispatcher result.
float *__cdecl rf_world_decal_update_volume_and_reproject(float *lhs, float *source, float *a3, float *a4, int a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  float *v21; // eax
  float *v22; // eax
  float *scalar; // [esp+0h] [ebp-148h]
  float *scalara; // [esp+0h] [ebp-148h]
  float *scalarb; // [esp+0h] [ebp-148h]
  float v27; // [esp+4h] [ebp-144h]
  float v28; // [esp+8h] [ebp-140h]
  float v29; // [esp+Ch] [ebp-13Ch]
  float v30; // [esp+10h] [ebp-138h]
  float v31; // [esp+14h] [ebp-134h]
  float v32; // [esp+18h] [ebp-130h]
  float v33[3]; // [esp+1Ch] [ebp-12Ch] BYREF
  float v34[3]; // [esp+28h] [ebp-120h] BYREF
  float v35[3]; // [esp+34h] [ebp-114h] BYREF
  _BYTE v36[16]; // [esp+40h] [ebp-108h] BYREF
  float v37[3]; // [esp+50h] [ebp-F8h] BYREF
  float v38[3]; // [esp+5Ch] [ebp-ECh] BYREF
  _BYTE v39[16]; // [esp+68h] [ebp-E0h] BYREF
  float v40[3]; // [esp+78h] [ebp-D0h] BYREF
  float v41[3]; // [esp+84h] [ebp-C4h] BYREF
  float v42[3]; // [esp+90h] [ebp-B8h] BYREF
  _BYTE v43[16]; // [esp+9Ch] [ebp-ACh] BYREF
  float v44[3]; // [esp+ACh] [ebp-9Ch] BYREF
  float v45[3]; // [esp+B8h] [ebp-90h] BYREF
  _BYTE v46[16]; // [esp+C4h] [ebp-84h] BYREF
  float v47[3]; // [esp+D4h] [ebp-74h] BYREF
  float out_vector[3]; // [esp+E0h] [ebp-68h] BYREF
  float v49[3]; // [esp+ECh] [ebp-5Ch] BYREF
  _BYTE v50[16]; // [esp+F8h] [ebp-50h] BYREF
  float sum_result[3]; // [esp+108h] [ebp-40h] BYREF
  float scaled_result[3]; // [esp+114h] [ebp-34h] BYREF
  _BYTE v53[16]; // [esp+120h] [ebp-28h] BYREF
  float v54[3]; // [esp+130h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+13Ch] [ebp-Ch] BYREF

  rf_matrix3_copy(lhs + 3, a3);
  rf_vector_copy(lhs, copy_result, source);
  rf_vector_copy(lhs + 12, v54, a4);
  *((_DWORD *)lhs + 15) = a5;
  v32 = lhs[13] * 0.5;
  v5 = rf_vector_multiply_scalar(lhs + 6, scaled_result, v32);
  v6 = rf_vector_add(lhs, sum_result, v5);
  v7 = (float *)rf_plane_construct_from_normal_point(v53, lhs + 6, (int)v6);
  rf_plane_copy(lhs + 23, v7);
  v31 = lhs[13] * 0.5;
  v8 = rf_vector_multiply_scalar(lhs + 6, v49, v31);
  scalar = rf_vector_subtract(lhs, out_vector, v8);
  v9 = rf_vector_negate(lhs + 6, v47);
  v10 = (float *)rf_plane_construct_from_normal_point(v50, v9, (int)scalar);
  rf_plane_copy(lhs + 27, v10);
  v30 = lhs[14] * 0.5;
  v11 = rf_vector_multiply_scalar(lhs + 9, v45, v30);
  v12 = rf_vector_add(lhs, v44, v11);
  v13 = (float *)rf_plane_construct_from_normal_point(v46, lhs + 9, (int)v12);
  rf_plane_copy(lhs + 31, v13);
  v29 = lhs[14] * 0.5;
  v14 = rf_vector_multiply_scalar(lhs + 9, v42, v29);
  scalara = rf_vector_subtract(lhs, v41, v14);
  v15 = rf_vector_negate(lhs + 9, v40);
  v16 = (float *)rf_plane_construct_from_normal_point(v43, v15, (int)scalara);
  rf_plane_copy(lhs + 35, v16);
  v28 = lhs[12] * 0.5;
  v17 = rf_vector_multiply_scalar(lhs + 3, v38, v28);
  v18 = rf_vector_add(lhs, v37, v17);
  v19 = (float *)rf_plane_construct_from_normal_point(v39, lhs + 3, (int)v18);
  rf_plane_copy(lhs + 39, v19);
  v27 = lhs[12] * 0.5;
  v20 = rf_vector_multiply_scalar(lhs + 3, v35, v27);
  scalarb = rf_vector_subtract(lhs, v34, v20);
  v21 = rf_vector_negate(lhs + 3, v33);
  v22 = (float *)rf_plane_construct_from_normal_point(v36, v21, (int)scalarb);
  rf_plane_copy(lhs + 43, v22);
  rf_world_decal_build_broadphase_aabb(lhs);
  rf_world_decal_release_attached_polygons((int)lhs);
  return rf_world_decal_project_candidate_or_tree_faces(lhs);
}

