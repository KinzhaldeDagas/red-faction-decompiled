// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C4540 rf_renderer_rebuild_world_clip_planes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Recomputes projection-scaled globals 18CD370=18CD3C4*18CD36C and 18CD37C=18CD3C4*18CD378. From camera position 18CD5E8 and basis vectors at 18CD398/3A4/3B0, constructs four world corner points one forward unit away with horizontal/vertical extents +/-18CD3C4/18CD3BC and +/-18CD3C4/18CD3C0. Resets plane count 18CD390, then fills 28-byte records at 18CD3C8. If byte 663F39 is nonzero: builds four lateral planes through the camera and corner pairs (outcodes 4,8,16,32), a camera-position plane with normal -forward (outcode128), and optionally a +forward-normal plane through camera+forward*18CD36C (outcode2) when byte18CD369 is set. Otherwise emits only four planes with normals -basisX,+basisX,-basisY,+basisY through the relevant corners. Every initializer stores AABB support selectors.
// No device call or fog update; used to restore full projection clipping before aperture replacement. Divisors are used without zero checks.
void rf_renderer_rebuild_world_clip_planes()
{
  float *v0; // eax
  float *v1; // eax
  float *v2; // eax
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
  float v14; // [esp-4h] [ebp-21Ch] BYREF
  float v15; // [esp+0h] [ebp-218h]
  float v16; // [esp+4h] [ebp-214h]
  char v17[4]; // [esp+8h] [ebp-210h] BYREF
  float v18; // [esp+Ch] [ebp-20Ch]
  float v19; // [esp+10h] [ebp-208h]
  float *scalar; // [esp+14h] [ebp-204h] BYREF
  float v21; // [esp+18h] [ebp-200h]
  float v22; // [esp+1Ch] [ebp-1FCh]
  void *v23; // [esp+20h] [ebp-1F8h]
  void *v24; // [esp+24h] [ebp-1F4h]
  void *v25; // [esp+28h] [ebp-1F0h]
  void *v26; // [esp+2Ch] [ebp-1ECh]
  void *v27; // [esp+30h] [ebp-1E8h]
  void *v28; // [esp+34h] [ebp-1E4h]
  void *v29; // [esp+38h] [ebp-1E0h]
  void *v30; // [esp+3Ch] [ebp-1DCh]
  void *v31; // [esp+40h] [ebp-1D8h]
  void *v32; // [esp+44h] [ebp-1D4h]
  float v33[26]; // [esp+4Ch] [ebp-1CCh] BYREF
  float v34[3]; // [esp+B4h] [ebp-164h] BYREF
  float v35[3]; // [esp+C0h] [ebp-158h] BYREF
  float v36[3]; // [esp+CCh] [ebp-14Ch] BYREF
  float v37[3]; // [esp+D8h] [ebp-140h] BYREF
  float v38[3]; // [esp+E4h] [ebp-134h] BYREF
  float v39[3]; // [esp+F0h] [ebp-128h] BYREF
  float v40[3]; // [esp+FCh] [ebp-11Ch] BYREF
  float v41[3]; // [esp+108h] [ebp-110h] BYREF
  float v42[3]; // [esp+114h] [ebp-104h] BYREF
  float v43[3]; // [esp+120h] [ebp-F8h] BYREF
  float v44[3]; // [esp+12Ch] [ebp-ECh] BYREF
  float v45[3]; // [esp+138h] [ebp-E0h] BYREF
  float v46[3]; // [esp+144h] [ebp-D4h] BYREF
  float v47[3]; // [esp+150h] [ebp-C8h] BYREF
  float v48[3]; // [esp+15Ch] [ebp-BCh] BYREF
  float v49[3]; // [esp+168h] [ebp-B0h] BYREF
  float v50[3]; // [esp+174h] [ebp-A4h] BYREF
  float v51[3]; // [esp+180h] [ebp-98h] BYREF
  float v52[3]; // [esp+18Ch] [ebp-8Ch] BYREF
  float v53[3]; // [esp+198h] [ebp-80h] BYREF
  float scaled_result[3]; // [esp+1A4h] [ebp-74h] BYREF
  float copy_result[3]; // [esp+1B0h] [ebp-68h] BYREF
  float v56[3]; // [esp+1BCh] [ebp-5Ch] BYREF
  float v57; // [esp+1C8h] [ebp-50h]
  float destination[3]; // [esp+1CCh] [ebp-4Ch] BYREF
  float v59; // [esp+1D8h] [ebp-40h]
  float v60[3]; // [esp+1DCh] [ebp-3Ch] BYREF
  float sum_result[3]; // [esp+1E8h] [ebp-30h] BYREF
  float v62; // [esp+1F4h] [ebp-24h]
  float v63; // [esp+1F8h] [ebp-20h]
  float v64; // [esp+1FCh] [ebp-1Ch]
  float v65[3]; // [esp+200h] [ebp-18h] BYREF
  float v66[3]; // [esp+20Ch] [ebp-Ch] BYREF

  flt_18CD370 = unk_18CD3C4 * flt_18CD36C;
  flt_18CD37C = unk_18CD3C4 * flt_18CD378;
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v60);
  rf_vector3_default_construct_noop(v65);
  rf_vector3_default_construct_noop(v56);
  rf_vector3_default_construct_noop(v66);
  rf_vector_copy(destination, copy_result, &flt_18CD5E8);
  v64 = 1.0;
  v63 = (float)1.0 * unk_18CD3C4 / unk_18CD3BC;
  v62 = -v63;
  v57 = (float)1.0 * unk_18CD3C4 / unk_18CD3C0;
  v59 = -v57;
  v0 = rf_vector_multiply_scalar(&flt_18CD3B0, scaled_result, 1.0);
  rf_vector_add(v0, sum_result, &flt_18CD5E8);
  scalar = rf_vector_multiply_scalar(&flt_18CD3A4, v52, v57);
  v1 = rf_vector_multiply_scalar(unk_18CD398, v53, v63);
  v2 = rf_vector_add(v1, v51, scalar);
  v3 = rf_vector_add(v2, v50, sum_result);
  rf_vector_copy(v65, v49, v3);
  scalar = rf_vector_multiply_scalar(&flt_18CD3A4, v47, v57);
  v4 = rf_vector_multiply_scalar(unk_18CD398, v48, v62);
  v5 = rf_vector_add(v4, v46, scalar);
  v6 = rf_vector_add(v5, v45, sum_result);
  rf_vector_copy(v60, v44, v6);
  scalar = rf_vector_multiply_scalar(&flt_18CD3A4, v42, v59);
  v7 = rf_vector_multiply_scalar(unk_18CD398, v43, v62);
  v8 = rf_vector_add(v7, v41, scalar);
  v9 = rf_vector_add(v8, v40, sum_result);
  rf_vector_copy(v56, v39, v9);
  scalar = rf_vector_multiply_scalar(&flt_18CD3A4, v37, v59);
  v10 = rf_vector_multiply_scalar(unk_18CD398, v38, v63);
  v11 = rf_vector_add(v10, v36, scalar);
  v12 = rf_vector_add(v11, v35, sum_result);
  rf_vector_copy(v66, v34, v12);
  dword_18CD390 = 0;
  if ( byte_663F39 )
  {
    v28 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v60);
    rf_vector3_copy_return_destination((float *)v17, v56);
    rf_vector3_copy_return_destination(&v14, destination);
    rf_clip_plane_record_from_three_points(v28, 4u, v14, v15, v16, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
    v27 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v66);
    rf_vector3_copy_return_destination((float *)v17, v65);
    rf_vector3_copy_return_destination(&v14, destination);
    rf_clip_plane_record_from_three_points(v27, 8u, v14, v15, v16, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
    v26 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v56);
    rf_vector3_copy_return_destination((float *)v17, v66);
    rf_vector3_copy_return_destination(&v14, destination);
    rf_clip_plane_record_from_three_points(
      v26,
      0x10u,
      v14,
      v15,
      v16,
      *(float *)v17,
      v18,
      v19,
      *(float *)&scalar,
      v21,
      v22);
    v25 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v65);
    rf_vector3_copy_return_destination((float *)v17, v60);
    rf_vector3_copy_return_destination(&v14, destination);
    rf_clip_plane_record_from_three_points(
      v25,
      0x20u,
      v14,
      v15,
      v16,
      *(float *)v17,
      v18,
      v19,
      *(float *)&scalar,
      v21,
      v22);
    v24 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, &flt_18CD5E8);
    rf_vector_scale((float *)v17, -1.0, &flt_18CD3B0);
    rf_clip_plane_record_from_normal_point(v24, 0x80u, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
    if ( byte_18CD369 )
    {
      v23 = &byte_18CD3C8[28 * dword_18CD390++];
      v13 = rf_vector_multiply_scalar(&flt_18CD3B0, v33, flt_18CD36C);
      rf_vector_add(&flt_18CD5E8, (float *)&scalar, v13);
      rf_vector3_copy_return_destination((float *)v17, &flt_18CD3B0);
      rf_clip_plane_record_from_normal_point(v23, 2u, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
    }
  }
  else
  {
    v32 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v60);
    rf_vector_negate(unk_18CD398, (float *)v17);
    rf_clip_plane_record_from_normal_point(v32, 4u, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
    v31 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v65);
    rf_vector3_copy_return_destination((float *)v17, unk_18CD398);
    rf_clip_plane_record_from_normal_point(v31, 8u, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
    v30 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v56);
    rf_vector_negate(&flt_18CD3A4, (float *)v17);
    rf_clip_plane_record_from_normal_point(v30, 0x10u, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
    v29 = &byte_18CD3C8[28 * dword_18CD390++];
    rf_vector3_copy_return_destination((float *)&scalar, v60);
    rf_vector3_copy_return_destination((float *)v17, &flt_18CD3A4);
    rf_clip_plane_record_from_normal_point(v29, 0x20u, *(float *)v17, v18, v19, *(float *)&scalar, v21, v22);
  }
}

