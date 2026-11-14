// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D4C0 rf_vector_divide
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Thiscall ECX source receiver, stack(outVector,scalar FLOAT), RET8. Three separate x87 FDIVs by supplied
// scalar in Z,Y,X order; each result roundedfloat32 in local/stack slots before any destination setter call. ECX then becomes outVector; setter receives stack(x,y,z), returns
// outVector inEAX. Ordinary overlapping source/output preserves all original source components because reads precede writes. Not reciprocal-then-multiply, no scalar0/finite guard,
// normalization or input modification except destination alias.
float *__thiscall rf_vector_divide(float *this, float *a2, float a3)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *(this + 2) / a3;
  v5 = *(this + 1) / a3;
  v4 = *this / a3;
  rf_vector3_set_components_return_destination(a2, v4, v5, v6);
  return a2;
}

