// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A280 rf_solid_vertex_copy_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall solid,position3f,RET4. Always allocates/copies new44-byte geomod vertex and appends pointer to solid vertex array120,returns vertex pointer. Does NOT search for duplicates,update bounds/sphere/incidence or reject NULL allocator return before append. Distinct from epsilon reuse helper51A170. Earlier repeatable allocation note retained.
float *__thiscall rf_solid_vertex_copy_append(_DWORD *this, float *a2)
{
  float *v4; // [esp+4h] [ebp-4h]

  v4 = rf_geomod_vertex_copy_allocate(a2);
  rf_pointer_array_append_dword(this + 30, (int)v4);
  return v4;
}

