// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B81D0 rf_mesh_read_context_construct_zero_cursors
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mesh initializers, binary reader stores, caller layouts and signature classification): Mesh-reader context initializer: writes DWORD zero at offsets20,28,0,8 only and returns ECX. Pool/base pointers and remaining fields are untouched; callers populate offsets4,12,16,24,32 separately. No allocation or whole-object clearing.
_DWORD *__thiscall rf_mesh_read_context_construct_zero_cursors(_DWORD *this)
{
  *(this + 5) = 0;
  *(this + 7) = 0;
  *this = 0;
  *(this + 2) = 0;
  return this;
}

