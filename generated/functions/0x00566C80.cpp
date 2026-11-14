// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566C80 rf_model_render_options_copy_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): ECX destination plus source,RET4. Copies first11DWORD-sized fields(offset0..40) sequentially,then matrix3 copy constructor for44..79,returns destination. No default initialization or repair of source uninitialized RGBA bytes. Exact same-base safe; arbitrary overlap not protected.
float *__thiscall rf_model_render_options_copy_construct(float *this, float *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  *(this + 4) = a2[4];
  *(this + 5) = a2[5];
  *(this + 6) = a2[6];
  *(this + 7) = a2[7];
  *(this + 8) = a2[8];
  *(this + 9) = a2[9];
  *(this + 10) = a2[10];
  rf_matrix3_copy_construct((int)(this + 11), a2 + 11);
  return this;
}

