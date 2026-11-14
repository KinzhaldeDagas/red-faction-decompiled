// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582160 rf_clip_vertex_update_camera_outcode
// UNREALRED VERIFIED [extended-clip-20261028]: Computes rf_camera_frustum_outcode from first three floats of caller vertex,stores result at byte24 and returns stored byte. Does not set projection/temporary flags at byte25 or modify coordinates.
char __cdecl rf_clip_vertex_update_camera_outcode(int a1)
{
  *(_BYTE *)(a1 + 24) = rf_camera_frustum_outcode((float *)a1);
  return *(_BYTE *)(a1 + 24);
}

