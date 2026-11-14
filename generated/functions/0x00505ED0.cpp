// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505ED0 rf_trigger_volume_contains_entity
// UNREALRED VERIFIED [trigger-attachment-20261020] Oriented trigger containment reads current common center+0x3C and orientation+0x48, alongside fixed extent+0x2C8. Attached-trigger pose changes therefore affect this consumer as well as collision dispatch. One-way branch is separate and is not reconstructed by the attachment patch.
// UNREALRED VERIFIED [trigger-geometry-20261020] CORRECTION to the entity-bounds interpretation: ordinary box branch passes object physics-current +0xE4 and physics-predicted +0xF0 to oriented-box segment helper56BE90. These are motion positions, not bounding-box corners. One-way branch uses predicted+0xF0 minus common+0x3C as direction, rejects length<=0.00001 and dot(direction,trigger third matrix row+0x60)>=0, then intersects the positive third-row face as two triangles with segment origin physics-current+0xE4.
char __cdecl rf_trigger_volume_contains_entity(int a1, const float *a2)
{
  float *v3; // eax
  float *v4; // eax
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
  float *v19; // [esp+8h] [ebp-1E4h]
  float *v20; // [esp+8h] [ebp-1E4h]
  float *v21; // [esp+8h] [ebp-1E4h]
  float *v22; // [esp+8h] [ebp-1E4h]
  float *scalar; // [esp+10h] [ebp-1DCh]
  float *scalara; // [esp+10h] [ebp-1DCh]
  float *scalarb; // [esp+10h] [ebp-1DCh]
  float *scalarc; // [esp+10h] [ebp-1DCh]
  float v27[3]; // [esp+14h] [ebp-1D8h] BYREF
  float v28[3]; // [esp+20h] [ebp-1CCh] BYREF
  float v29[3]; // [esp+2Ch] [ebp-1C0h] BYREF
  float v30[3]; // [esp+38h] [ebp-1B4h] BYREF
  float v31[3]; // [esp+44h] [ebp-1A8h] BYREF
  float v32[3]; // [esp+50h] [ebp-19Ch] BYREF
  float v33[3]; // [esp+5Ch] [ebp-190h] BYREF
  float v34[3]; // [esp+68h] [ebp-184h] BYREF
  float v35[3]; // [esp+74h] [ebp-178h] BYREF
  float v36[3]; // [esp+80h] [ebp-16Ch] BYREF
  float v37[3]; // [esp+8Ch] [ebp-160h] BYREF
  float v38[3]; // [esp+98h] [ebp-154h] BYREF
  float v39[3]; // [esp+A4h] [ebp-148h] BYREF
  float v40[3]; // [esp+B0h] [ebp-13Ch] BYREF
  float v41[3]; // [esp+BCh] [ebp-130h] BYREF
  float v42[3]; // [esp+C8h] [ebp-124h] BYREF
  float v43[3]; // [esp+D4h] [ebp-118h] BYREF
  float v44[3]; // [esp+E0h] [ebp-10Ch] BYREF
  float v45[3]; // [esp+ECh] [ebp-100h] BYREF
  float v46[3]; // [esp+F8h] [ebp-F4h] BYREF
  float v47[3]; // [esp+104h] [ebp-E8h] BYREF
  float v48[3]; // [esp+110h] [ebp-DCh] BYREF
  float v49[3]; // [esp+11Ch] [ebp-D0h] BYREF
  float v50[3]; // [esp+128h] [ebp-C4h] BYREF
  float copy_result[3]; // [esp+134h] [ebp-B8h] BYREF
  float v52[3]; // [esp+140h] [ebp-ACh] BYREF
  float v53[3]; // [esp+14Ch] [ebp-A0h] BYREF
  float v54[3]; // [esp+158h] [ebp-94h] BYREF
  float v55[3]; // [esp+164h] [ebp-88h] BYREF
  float sum_result[3]; // [esp+170h] [ebp-7Ch] BYREF
  float v57[3]; // [esp+17Ch] [ebp-70h] BYREF
  float destination[3]; // [esp+188h] [ebp-64h] BYREF
  float v59[3]; // [esp+194h] [ebp-58h] BYREF
  float v60[3]; // [esp+1A0h] [ebp-4Ch] BYREF
  float scaled_result; // [esp+1ACh] [ebp-40h] BYREF
  float v62; // [esp+1B0h] [ebp-3Ch]
  float v63; // [esp+1B4h] [ebp-38h]
  float v64; // [esp+1B8h] [ebp-34h] BYREF
  float out_vector[3]; // [esp+1BCh] [ebp-30h] BYREF
  float v66; // [esp+1C8h] [ebp-24h]
  float v67[4]; // [esp+1CCh] [ebp-20h] BYREF
  float v68[3]; // [esp+1DCh] [ebp-10h] BYREF
  char v69; // [esp+1EBh] [ebp-1h]

  rf_vector3_default_construct_noop(v68);
  if ( (*(_DWORD *)(a1 + 688) & 0x20) == 0 )
    return rf_segment_intersects_oriented_box(
             a1 + 60,
             (float *)(a1 + 72),
             a1 + 712,
             (int)(a2 + 57),
             (int)(a2 + 60),
             v68);
  rf_vector_subtract(a2 + 60, out_vector, a2 + 15);
  if ( rf_vector3_length(out_vector) <= 0.000009999999747378752 )
    return 0;
  v66 = rf_vector_dot(out_vector, (float *)(a1 + 96));
  if ( v66 >= 0.0 )
    return 0;
  rf_vector3_default_construct_noop(v60);
  rf_vector_prefix_construct_noop(v67);
  rf_force_sample44_construct_vectors_noop((char *)destination);
  rf_vector_multiply_scalar((const float *)(a1 + 712), &scaled_result, 0.5);
  scalar = rf_vector_multiply_scalar((const float *)(a1 + 96), v53, v63);
  v19 = rf_vector_multiply_scalar((const float *)(a1 + 84), v55, v62);
  v3 = rf_vector_multiply_scalar((const float *)(a1 + 72), v57, scaled_result);
  v4 = rf_vector_add((const float *)(a1 + 60), sum_result, v3);
  v5 = rf_vector_subtract(v4, v54, v19);
  v6 = rf_vector_add(v5, v52, scalar);
  rf_vector_copy((float *)dword_90B4F4[0], copy_result, v6);
  scalara = rf_vector_multiply_scalar((const float *)(a1 + 96), v46, v63);
  v20 = rf_vector_multiply_scalar((const float *)(a1 + 84), v48, v62);
  v7 = rf_vector_multiply_scalar((const float *)(a1 + 72), v50, scaled_result);
  v8 = rf_vector_subtract((const float *)(a1 + 60), v49, v7);
  v9 = rf_vector_subtract(v8, v47, v20);
  v10 = rf_vector_add(v9, v45, scalara);
  rf_vector_copy((float *)dword_90B4F8, v44, v10);
  scalarb = rf_vector_multiply_scalar((const float *)(a1 + 96), v39, v63);
  v21 = rf_vector_multiply_scalar((const float *)(a1 + 84), v41, v62);
  v11 = rf_vector_multiply_scalar((const float *)(a1 + 72), v43, scaled_result);
  v12 = rf_vector_add((const float *)(a1 + 60), v42, v11);
  v13 = rf_vector_add(v12, v40, v21);
  v14 = rf_vector_add(v13, v38, scalarb);
  rf_vector_copy((float *)dword_90B4FC, v37, v14);
  scalarc = rf_vector_multiply_scalar((const float *)(a1 + 96), v32, v63);
  v22 = rf_vector_multiply_scalar((const float *)(a1 + 84), v34, v62);
  v15 = rf_vector_multiply_scalar((const float *)(a1 + 72), v36, scaled_result);
  v16 = rf_vector_subtract((const float *)(a1 + 60), v35, v15);
  v17 = rf_vector_add(v16, v33, v22);
  v18 = rf_vector_add(v17, v31, scalarc);
  rf_vector_copy((float *)dword_90B500, v30, v18);
  rf_plane4_construct_normal_point(v67, (float *)(a1 + 96), (float *)dword_90B4F4[0]);
  rf_vector_copy(destination, v29, a2 + 57);
  rf_vector_copy(v59, v28, out_vector);
  v69 = rf_segment_triangle_intersect_front_plane((int)destination, (int)dword_90B4F4, (int)v67, v60, &v64);
  if ( !v69 )
  {
    rf_vector_copy((float *)dword_90B4FC, v27, (const float *)dword_90B500);
    return rf_segment_triangle_intersect_front_plane((int)destination, (int)dword_90B4F4, (int)v67, v60, &v64);
  }
  return v69;
}

