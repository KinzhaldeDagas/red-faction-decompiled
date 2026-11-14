// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581B60 rf_frustum_reject_sphere
// UNREALRED VERIFIED [room-render-20261028]: For each active plane computes signed distance of caller center; returns1 if distance>caller radius,else after all planes0. Strict comparison retains tangent boundary. No abs/clamp of radius or center transform; caller handles coordinate-space adjustment.
char __cdecl rf_frustum_reject_sphere(float *a1, float a2)
{
  float v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < dword_18CD390; ++i )
  {
    v3 = rf_plane_point_signed_distance((float *)&unk_18CD3CC + 7 * i, a1);
    if ( a2 < (double)v3 )
      return 1;
  }
  return 0;
}

