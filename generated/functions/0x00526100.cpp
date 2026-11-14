// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00526100 rf_point_light_intersects_aabb
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl light,minXYZ,maxXYZ, ALbool. Compute expandedMin=min-light.rangeF32at60 and expandedMax=max+range via component helpers. If DWORD18CD388 nonzero use light alternate/transformed position92 else original position12. Return inclusive AABB contains-point helper on selected position and expanded bounds. Conservative axis expansion, not Euclidean sphere/AABB distance; diagonal points can pass. No light type, negative range, min<=max, finite or pointer validation; comparison behavior inherited from containment helper. Does not mutate light/receiver bounds.
bool __cdecl rf_point_light_intersects_aabb(float *a1, float *a2, float *a3)
{
  float *v3; // eax
  float *v4; // eax
  float v6[3]; // [esp+4h] [ebp-58h] BYREF
  int v7[3]; // [esp+10h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-40h] BYREF
  int v9[3]; // [esp+28h] [ebp-34h] BYREF
  float v10[3]; // [esp+34h] [ebp-28h] BYREF
  float destination[3]; // [esp+40h] [ebp-1Ch] BYREF
  _BYTE v12[12]; // [esp+4Ch] [ebp-10h] BYREF
  float *v13; // [esp+58h] [ebp-4h]

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v10);
  rf_vector3_default_construct_noop(v12);
  v3 = rf_vector3_subtract_scalar_from_components(a2, (float *)v9, a1[15]);
  rf_vector_copy(destination, copy_result, v3);
  v4 = rf_vector3_add_scalar_to_components(a3, (float *)v7, a1[15]);
  rf_vector_copy(v10, v6, v4);
  v13 = nullptr;
  if ( unk_18CD388 )
    v13 = a1 + 23;
  else
    v13 = a1 + 3;
  return rf_aabb_contains_point_inclusive(v13, destination, v10);
}

