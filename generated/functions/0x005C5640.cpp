// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5640 rf_renderer_plane_faces_camera
// UNREALRED VERIFIED [renderer-overlays-20261028]: Inputs three-float normal and point on plane. If byte0x663F39 clear,returns dot(globalcamera thirdrow0x18CD4CC,normal)<=0,ignoring point. Otherwise returns dot(cameraPosition0x18CD5E8-point,normal)>0. Strictness differs between branches; no normal normalization or epsilon tolerance.
bool __cdecl rf_renderer_plane_faces_camera(float *a1, float *rhs)
{
  float out_vector[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !byte_663F39 )
    return rf_vector_dot(&flt_18CD4CC, a1) <= 0.0;
  rf_vector_subtract(&flt_18CD5E8, out_vector, rhs);
  return rf_vector_dot(out_vector, a1) > 0.0;
}

