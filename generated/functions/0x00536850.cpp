// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536850 rf_lightmap_plane_solve_x_from_projected_pair
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall descriptor,a,b,outputXYZ. If projection axisDWORD96==1,sets y=a,z=b;otherwise y=b,z=a. Solves x=(-normalY*y-normalZ*z-D)/normalX using plane108..120,returns output. No normalizedUV interpretation,clamp,plane validation or zero-divisor guard;inputs are selected coordinate-plane values.
float *__thiscall rf_lightmap_plane_solve_x_from_projected_pair(int this, float a2, float a3, float *a4)
{
  if ( *(_DWORD *)(this + 96) == 1 )
  {
    a4[1] = a2;
    a4[2] = a3;
  }
  else
  {
    a4[1] = a3;
    a4[2] = a2;
  }
  *a4 = (-(*(float *)(this + 112) * a4[1]) - *(float *)(this + 116) * a4[2] - *(float *)(this + 120))
      / *(float *)(this + 108);
  return a4;
}

