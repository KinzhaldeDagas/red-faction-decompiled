// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005833C0 rf_quaternion_unit_log_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered in-place counterpart of583140. Computes r from original xyz and factor atan2(r,w)/r when r>0,else r;scales xyz and sets w0,returns receiver. No real log(norm) term,normalization or finite check. Factor computed before writes,so w used before it is overwritten.
float *__thiscall rf_quaternion_unit_log_in_place(float *this)
{
  float v2; // [esp+8h] [ebp-10h]
  float v4; // [esp+10h] [ebp-8h]
  float X; // [esp+14h] [ebp-4h]

  v2 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  X = rf_sqrt_float(v2);
  if ( X > 0.0 )
  {
    v4 = atan2f(X, *(this + 3));
    X = v4 / X;
  }
  *this = X * *this;
  *(this + 1) = X * *(this + 1);
  *(this + 2) = X * *(this + 2);
  *(this + 3) = 0.0;
  return this;
}

