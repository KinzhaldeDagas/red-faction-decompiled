// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005368D0 rf_lightmap_plane_solve_y_from_projected_pair
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall descriptor,a,b,outputXYZ. AxisDWORD96 nonzero sets x=b,z=a,zero sets x=a,z=b. Solves y=(-normalX*x-normalZ*z-D)/normalY from plane108..120. Returns output;no NULL/divisor/finite guards or UV scaling.
float *__thiscall rf_lightmap_plane_solve_y_from_projected_pair(int this, float a2, float a3, float *a4)
{
  if ( *(_DWORD *)(this + 96) )
  {
    *a4 = a3;
    a4[2] = a2;
  }
  else
  {
    *a4 = a2;
    a4[2] = a3;
  }
  a4[1] = (-(*(float *)(this + 108) * *a4) - *(float *)(this + 116) * a4[2] - *(float *)(this + 120))
        / *(float *)(this + 112);
  return a4;
}

