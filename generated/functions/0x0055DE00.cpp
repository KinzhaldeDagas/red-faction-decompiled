// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055DE00 rf_affine3x4_set_rows_translation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Copies four source vector3 objects sequentially into twelve-float receiver: rotation rows at0,3,6 and translation at9. Returns receiver. No normalization/transposition. Exact self sources are safe; arbitrary partial aliasing follows sequential store behavior, not snapshot semantics.
float *__thiscall rf_affine3x4_set_rows_translation(float *this, float *a2, float *a3, float *a4, float *a5)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = *a3;
  *(this + 4) = a3[1];
  *(this + 5) = a3[2];
  *(this + 6) = *a4;
  *(this + 7) = a4[1];
  *(this + 8) = a4[2];
  *(this + 9) = *a5;
  *(this + 10) = a5[1];
  *(this + 11) = a5[2];
  return this;
}

