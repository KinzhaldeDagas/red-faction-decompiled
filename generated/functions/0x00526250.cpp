// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00526250 rf_tube_light_intersects_aabb
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl light,min,max ALbool. Expand receiver bounds componentwise by rangeF32at60. DWORD18CD388 nonzero chooses segment endpoints light92/104;zero chooses12/24. Call finite segment/AABB helper with temporary outpoint and return its boolean unchanged, discarding point. Conservative axis expansion rather than exact capsule/AABB distance; no normalization, endpoint order test, light type/range/finite checks or state changes.
bool __cdecl rf_tube_light_intersects_aabb(float *a1, float *a2, float *a3)
{
  float *v4; // [esp+4h] [ebp-2Ch]
  int v5[3]; // [esp+8h] [ebp-28h] BYREF
  float v6[3]; // [esp+14h] [ebp-1Ch] BYREF
  int v7[3]; // [esp+20h] [ebp-10h] BYREF
  float *v8; // [esp+2Ch] [ebp-4h]

  rf_vector3_subtract_scalar_from_components(a2, (float *)v7, a1[15]);
  rf_vector3_add_scalar_to_components(a3, (float *)v5, a1[15]);
  v8 = nullptr;
  if ( unk_18CD388 )
  {
    v8 = a1 + 23;
    v4 = a1 + 26;
  }
  else
  {
    v8 = a1 + 3;
    v4 = a1 + 6;
  }
  rf_vector3_default_construct_noop(v6);
  return rf_segment_intersects_aabb((float *)v7, (float *)v5, v8, v4, v6);
}

