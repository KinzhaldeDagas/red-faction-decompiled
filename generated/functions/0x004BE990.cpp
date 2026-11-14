// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE990 rf_collision_prepare_projectile_pair_planes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Cdecl projectile. Reads class pointer660 and float class192; scale=F32(10/class192), no local zero/finite guard. With physical orientation rows R0=object252,R1=264,F=276, physical position228: n0=normalize(R0+scale*F), writes plane at813BD8 through position; n1=n0-2*dot(R0,n0)*R0 writes813BE8. Then n2=normalize(R1+scale*F) writes813BF8; n3=n2-2*dot(R1,n2)*R1 writes813C08. Reflected normals are not renormalized and source rows are not checked unit/orthogonal. Overwrites four GLOBAL16-byte planes, not per-pair storage. Returns final plane pointer. No matrix/class/null checks or restoration; caller4BFCF0 only invokes for type2 with class616 mask0x20.
float *__cdecl rf_collision_prepare_projectile_pair_planes(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v10; // [esp+0h] [ebp-B4h]
  float v11; // [esp+0h] [ebp-B4h]
  int v12[3]; // [esp+8h] [ebp-ACh] BYREF
  float v13[3]; // [esp+14h] [ebp-A0h] BYREF
  int v14[3]; // [esp+20h] [ebp-94h] BYREF
  float v15[3]; // [esp+2Ch] [ebp-88h] BYREF
  float v16[3]; // [esp+38h] [ebp-7Ch] BYREF
  int v17[3]; // [esp+44h] [ebp-70h] BYREF
  int v18[3]; // [esp+50h] [ebp-64h] BYREF
  float v19[3]; // [esp+5Ch] [ebp-58h] BYREF
  int v20[3]; // [esp+68h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+74h] [ebp-40h] BYREF
  float sum_result[3]; // [esp+80h] [ebp-34h] BYREF
  int v23[3]; // [esp+8Ch] [ebp-28h] BYREF
  float destination[3]; // [esp+98h] [ebp-1Ch] BYREF
  float v25[3]; // [esp+A4h] [ebp-10h] BYREF
  float v26; // [esp+B0h] [ebp-4h]

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v25);
  v26 = 10.0 / *(float *)(*(_DWORD *)(a1 + 660) + 192);
  v1 = rf_vector_scale((float *)v23, v26, (float *)(a1 + 276));
  v2 = rf_vector_add((const float *)(a1 + 252), sum_result, v1);
  rf_vector_copy(destination, copy_result, v2);
  rf_vector_normalize_reciprocal_sqrt(destination);
  rf_plane4_construct_normal_point(flt_813BD8, destination, (float *)(a1 + 228));
  v10 = rf_vector_dot((float *)(a1 + 252), destination);
  v3 = rf_vector_scale((float *)v20, v10, (float *)(a1 + 252));
  rf_vector_copy(v25, v19, v3);
  v4 = rf_vector_scale((float *)v18, -2.0, v25);
  rf_vector_accumulate(destination, v4);
  rf_plane4_construct_normal_point(flt_813BE8, destination, (float *)(a1 + 228));
  v5 = rf_vector_scale((float *)v17, v26, (float *)(a1 + 276));
  v6 = rf_vector_add((const float *)(a1 + 264), v16, v5);
  rf_vector_copy(destination, v15, v6);
  rf_vector_normalize_reciprocal_sqrt(destination);
  rf_plane4_construct_normal_point(flt_813BF8, destination, (float *)(a1 + 228));
  v11 = rf_vector_dot((float *)(a1 + 264), destination);
  v7 = rf_vector_scale((float *)v14, v11, (float *)(a1 + 264));
  rf_vector_copy(v25, v13, v7);
  v8 = rf_vector_scale((float *)v12, -2.0, v25);
  rf_vector_accumulate(destination, v8);
  return rf_plane4_construct_normal_point(flt_813C08, destination, (float *)(a1 + 228));
}

