// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582E90 rf_quaternion_to_matrix3_rows
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Thiscall source quaternion(x,y,z,w),stack output nine floats. Writes row-major coefficients: [1-2y^2-2z^2,2xy-2zw,2xz+2yw;2xy+2zw,1-2x^2-2z^2,2yz-2xw;2xz-2yw,2yz+2xw,1-2x^2-2y^2]. Returns SOURCE quaternion pointer,not output. No normalization or source snapshot; output/source overlap can affect subsequent reads. Particle emitter uses output matrix to rotate rectangular positions/velocities.
// UNREALRED VERIFIED [combat-selected-drop-item-20261111]: Static grip and character geometry-prop frames consume raw source quaternion through this exact matrix producer, with no quaternion normalization. Current render PropPoint.Rotation normalizes and is not identical. Preserve raw7float record values for native localaffine composition; current primarybone/body frame is an explicitlydeclaredhostpose adapter.
float *__thiscall rf_quaternion_to_matrix3_rows(float *this, float *a2)
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
  return this;
}

