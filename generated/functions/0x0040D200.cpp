// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D200 rf_vector_scale
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Free cdecl(outVector,scalar FLOAT,sourceVector), not ECX receiver ABI. Reads/multiplies source components
// in Z,Y,X order, each rounded through a four-byte local/stack slot BEFORE output setter is called. Calls vector setter with ECX=out and stack(x,y,z); returns out pointer EAX. Thus
// all three input components are captured before any destination write, including ordinary source/destination overlap. No own zero/finite/normalization guard, source mutation or
// reciprocal multiplication.
float *__cdecl rf_vector_scale(float *a1, float a2, float *a3)
{
  float v4; // [esp+Ch] [ebp-Ch]
  float v5; // [esp+10h] [ebp-8h]
  float v6; // [esp+14h] [ebp-4h]

  v6 = a3[2] * a2;
  v5 = a3[1] * a2;
  v4 = *a3 * a2;
  rf_vector3_set_components_return_destination(a1, v4, v5, v6);
  return a1;
}

