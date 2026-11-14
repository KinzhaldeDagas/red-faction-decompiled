// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D110 rf_vector_dot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Thiscall receiver ECX points to three FLOATs, one source pointer on stack, RET4. Native x87 computes
// (receiver.x*source.x + receiver.y*source.y) +receiver.z*source.z, with NO intermediate float32 stores between products/additions. Stores final sum to four-byte local, reloadsST0,
// so result roundsfloat32 despite stored double return. Does not normalize, mutate either vector, clamp NaN/Inf or change x87 control mode. EAX is incidental; numerical result isST0.
double __thiscall rf_vector_dot(float *this, float *a2)
{
  return (float)(*this * *a2 + *(this + 1) * a2[1] + *(this + 2) * a2[2]);
}

