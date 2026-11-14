// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C56B0 rf_renderer_face_view_test_backend_102
// UNREALRED VERIFIED [room-render-20261028]: When byte0x663F39 nonzero returns signed plane distance(face plane,point0x18CD5E8)>0. Otherwise returns dot(vec3 at0x18CD4CC,face normal)<=0. No plane normalization or bounds/portal/liquid flag test. Exact comparison directions and boundary behavior differ between modes.
bool __cdecl rf_renderer_face_view_test_backend_102(float *a1)
{
  if ( byte_663F39 )
    return rf_plane_point_signed_distance(a1, &flt_18CD5E8) > 0.0;
  else
    return rf_vector_dot(&flt_18CD4CC, a1) <= 0.0;
}

