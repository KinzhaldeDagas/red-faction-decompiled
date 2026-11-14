// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583380 rf_quaternion_conjugate_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered in-place quaternion conjugate:negates x,y,z sequentially,leaves w unchanged,returns receiver. No squared-norm division,normalization or allocation;not full quaternion sign negation.
float *__thiscall rf_quaternion_conjugate_in_place(float *this)
{
  *this = -*this;
  *(this + 1) = -*(this + 1);
  *(this + 2) = -*(this + 2);
  return this;
}

