// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00533FF0 rf_geomod_line_minus_parameter_plane_residual
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Cdecl by-value float t,line pointer,plane pointer; caller pops12. Form F32 temporary direction*t from line+12, then F32 point=line.origin0-that temporary; compute dot(point,plane.normal0)+plane.d12 and explicitly store/reload F32 for x87 ST0 return. Sign is origin-MINUS-direction*t, not plus. Does not normalize plane, clamp t, divide by direction dot normal, or modify either input. Used by5339B0 iterative crossing residual checks.
double __cdecl rf_geomod_line_minus_parameter_plane_residual(float scalar, float *lhs, float *a3)
{
  float *v3; // eax
  float scaled_result[3]; // [esp+8h] [ebp-18h] BYREF
  float out_vector[3]; // [esp+14h] [ebp-Ch] BYREF

  v3 = rf_vector_multiply_scalar(lhs + 3, scaled_result, scalar);
  rf_vector_subtract(lhs, out_vector, v3);
  return (float)(rf_vector_dot(out_vector, a3) + a3[3]);
}

