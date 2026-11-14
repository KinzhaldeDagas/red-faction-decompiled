// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581910 rf_renderer_face_passes_view_test
// UNREALRED VERIFIED [room-render-20261028]: Returns true only when renderer selector0x187CC9C==102 AND backend0x5C56B0(face plane) true. Other backends returnfalse. No additional frustum/AABB check.
bool __cdecl rf_renderer_face_passes_view_test(float *a1)
{
  return dword_187CC9C == 102 && rf_renderer_face_view_test_backend_102(a1);
}

