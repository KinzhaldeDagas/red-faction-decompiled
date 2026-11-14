// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E080 rf_affine3x4_set_translation_return_source
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This affine float[12],arg translation float3. Writes only matrix indices9,10,11 and RETURNS SOURCE pointer. Rotation0..8 unchanged. No staging,normalization or NULL check;not returning this as conventional assignment.
float *__thiscall rf_affine3x4_set_translation_return_source(float *this, float *a2)
{
  *(this + 9) = *a2;
  *(this + 10) = a2[1];
  *(this + 11) = a2[2];
  return a2;
}

