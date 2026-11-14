// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564E90 rf_vmesh_submesh_bounds_get
// UNREALRED VERIFIED [clutter-debris-decode]: Returns an authored VMesh submesh center and size used to seed one physical clutter-debris piece.
void __cdecl rf_vmesh_submesh_bounds_get(_DWORD *a1, int a2, float *a3, float *a4)
{
  rf_model_handle_get_indexed_bounds_sphere(a1, a2, a3, a4);
}

