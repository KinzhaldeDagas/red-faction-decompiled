// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005261B0 rf_spot_light_intersects_aabb
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl light,min,max ALbool. For six plane indices0..5, select AABB minimum-support corner using stored DWORD244+4*i, evaluate plane148+16*i (x87 result not first roundedF32), reject on ORDERED signedDistance>PEdouble(-0.001). Equality to threshold, lower values and unorderedNaN do NOT reject; all six must avoid rejection. No range expansion, cone-angle calculation or plane build here. Selectors/planes must already be in current receiver space. This is six-plane conservative support testing, not an exact circular-cone/AABB intersection.
bool __cdecl rf_spot_light_intersects_aabb(int a1, float *bounds_min, float *bounds_max)
{
  float out_vector[3]; // [esp+0h] [ebp-14h] BYREF
  int i; // [esp+Ch] [ebp-8h]
  char v6; // [esp+13h] [ebp-1h]

  v6 = 0;
  for ( i = 0; i < 6; ++i )
  {
    rf_vector3_default_construct_noop(out_vector);
    rf_aabb_select_corner_by_index(out_vector, *(_DWORD *)(a1 + 4 * i + 244), bounds_min, bounds_max);
    if ( rf_plane_point_signed_distance((float *)(a1 + 16 * i + 148), out_vector) > -0.001 )
    {
      v6 = 1;
      return v6 == 0;
    }
  }
  return v6 == 0;
}

