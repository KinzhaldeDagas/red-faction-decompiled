// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E0B0 rf_affine3x4_get_translation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Thiscall source12-float affine,stack destination float3. Copies source floats[9..11] into destination through vector setter,returns destination. No rotation/matrix transpose,normalization or source mutation;RF translation occupies final three contiguous floats.
float *__thiscall rf_affine3x4_get_translation(float *this, float *a2)
{
  rf_vector3_set_components_return_destination(a2, *(this + 9), *(this + 10), *(this + 11));
  return a2;
}

