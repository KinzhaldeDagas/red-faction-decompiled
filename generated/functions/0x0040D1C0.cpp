// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D1C0 rf_vector_length_squared
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Thiscall ECX receiver, no stack arguments, plainRET. Native x87 computes (x*x+y*y)+z*z with no intermediate
// float32 stores; final four-byte FSTP/FLD rounds to float32 and returnsST0 despite stored double type. NO square root, normalization, positive clamp, finite guard or receiver
// mutation. Retains native x87 operation order/control environment.
double __thiscall rf_vector_length_squared(float *this)
{
  return (float)(*this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2));
}

