// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536080 rf_geomod_face_plane_reverse
// UNREALRED VERIFIED [geomod-lighting-20261027] Disassembly confirms vector negation of the three normal floats at face +0, followed by fld/fchs/fstp of plane scalar +0x0C at 0x5360A5..0x5360AD. It negates the retained plane, not a full geometry recomputation. Called after ordered-loop reversal at 0x534834.
float *__thiscall rf_geomod_face_plane_reverse(float *this)
{
  float *v1; // eax
  float copy_result[3]; // [esp+4h] [ebp-18h] BYREF
  float v5[3]; // [esp+10h] [ebp-Ch] BYREF

  v1 = rf_vector_negate(this, v5);
  rf_vector_copy(this, copy_result, v1);
  *(this + 3) = -*(this + 3);
  return this;
}

