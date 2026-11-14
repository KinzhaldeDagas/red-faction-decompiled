// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536950 rf_lightmap_plane_solve_z_from_projected_pair
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall descriptor,a,b,outputXYZ. AxisDWORD96 nonzero sets x=b,y=a,zero sets x=a,y=b. Solves z=(-normalX*x-normalY*y-D)/normalZ from plane108..120,returns output. No clamp,normalization or zero-divisor guard.
float *__thiscall rf_lightmap_plane_solve_z_from_projected_pair(int this, float a2, float a3, float *a4)
{
  if ( *(_DWORD *)(this + 96) )
  {
    *a4 = a3;
    a4[1] = a2;
  }
  else
  {
    *a4 = a2;
    a4[1] = a3;
  }
  a4[2] = (-(*(float *)(this + 108) * *a4) - *(float *)(this + 112) * a4[1] - *(float *)(this + 120))
        / *(float *)(this + 116);
  return a4;
}

