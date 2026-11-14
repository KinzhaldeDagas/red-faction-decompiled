// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559980 rf_vector3_near_equal_per_axis_strict
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Returns32-bit boolean if all absolute XYZ differences are STRICTLY less than float threshold9.999999747378752e-5. Equality at threshold rejects; no Euclidean-distance test. NaN/unordered differences reject. Separate from clone squared-distance welding criterion.
BOOL __cdecl rf_vector3_near_equal_per_axis_strict(float *a1, float *a2)
{
  BOOL result; // eax
  float v3; // [esp+0h] [ebp-Ch]
  float v4; // [esp+4h] [ebp-8h]
  float v5; // [esp+8h] [ebp-4h]

  v5 = fabs(*a1 - *a2);
  result = false;
  if ( v5 < 0.00009999999747378752 )
  {
    v4 = fabs(a1[1] - a2[1]);
    if ( v4 < 0.00009999999747378752 )
    {
      v3 = fabs(a1[2] - a2[2]);
      if ( v3 < 0.00009999999747378752 )
        return true;
    }
  }
  return result;
}

