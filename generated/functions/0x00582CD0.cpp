// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582CD0 rf_quaternion_to_affine3x4_zero_translation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This source quaternion float4(x,y,z,w);one destination float[12] arg. Writes standard quadratic nine rotation components with exact layout rows in memory:[1-2y²-2z²,2xy-2zw,2xz+2yw;2xy+2zw,1-2x²-2z²,2yz-2xw;2xz-2yw,2yz+2xw,1-2x²-2y²],then three translation floats9..11=0. Returns destination. No quaternion normalization or input/output alias protection;nonunit input need not yield orthogonal rotation. This memory layout is also interpreted as basis columns by affine point transform;formulas preserve original convention.
float *__thiscall rf_quaternion_to_affine3x4_zero_translation(float *this, float *a2)
{
  *a2 = 1.0 - *(this + 1) * 2.0 * *(this + 1) - *(this + 2) * 2.0 * *(this + 2);
  a2[1] = *this * 2.0 * *(this + 1) - *(this + 2) * 2.0 * *(this + 3);
  a2[2] = *(this + 2) * 2.0 * *this + *(this + 1) * 2.0 * *(this + 3);
  a2[3] = *this * 2.0 * *(this + 1) + *(this + 2) * 2.0 * *(this + 3);
  a2[4] = 1.0 - *this * 2.0 * *this - *(this + 2) * 2.0 * *(this + 2);
  a2[5] = *(this + 2) * 2.0 * *(this + 1) - *this * 2.0 * *(this + 3);
  a2[6] = *this * 2.0 * *(this + 2) - *(this + 1) * 2.0 * *(this + 3);
  a2[7] = *(this + 2) * 2.0 * *(this + 1) + *this * 2.0 * *(this + 3);
  a2[8] = 1.0 - *this * 2.0 * *this - *(this + 1) * 2.0 * *(this + 1);
  a2[9] = 0.0;
  a2[10] = 0.0;
  a2[11] = 0.0;
  return a2;
}

