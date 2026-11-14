// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055DEA0 rf_affine3x4_set_rotation_translation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This destination float[12];args translation float3,rotation float9. Copies rotation indices0..8 first,then translation into9..11,returns this. Layout is three contiguous3-float basis columns followed bytranslation as used by point transform0x55EAC0. Forward scalar copy,no staging or arbitrary-overlap protection;does not normalize matrix.
float *__thiscall rf_affine3x4_set_rotation_translation(float *this, float *a2, float *a3)
{
  *this = *a3;
  *(this + 1) = a3[1];
  *(this + 2) = a3[2];
  *(this + 3) = a3[3];
  *(this + 4) = a3[4];
  *(this + 5) = a3[5];
  *(this + 6) = a3[6];
  *(this + 7) = a3[7];
  *(this + 8) = a3[8];
  *(this + 9) = *a2;
  *(this + 10) = a2[1];
  *(this + 11) = a2[2];
  return this;
}

