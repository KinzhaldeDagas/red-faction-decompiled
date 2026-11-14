// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A870 rf_renderer_compute_reflection_uv
// UNREALRED VERIFIED [reflection-uv-20260903]: Computes retail spherical reflection-map UV for one mesh vertex. With V = normalize(view_position - vertex_position) and unit surface normal N, it forms and normalizes R = 2*N*dot(N,V) - V, then writes U = 0.5*(atan2(R.z,R.x)/pi + 1) and V = 0.5*(1 - R.y). Its sole caller is mesh-face submission at 0x005D78B0.
float *__cdecl rf_renderer_compute_reflection_uv(float *a1, float *a2, float *rhs, float *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  double v7; // st7
  float scalar; // [esp+Ch] [ebp-54h]
  float copy_result[3]; // [esp+18h] [ebp-48h] BYREF
  float v11[3]; // [esp+24h] [ebp-3Ch] BYREF
  float scaled_result[3]; // [esp+30h] [ebp-30h] BYREF
  int v13[3]; // [esp+3Ch] [ebp-24h] BYREF
  float destination[3]; // [esp+48h] [ebp-18h] BYREF
  float out_vector[3]; // [esp+54h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector_subtract(&flt_18CD5E8, out_vector, rhs);
  scalar = rf_vector_dot(a4, out_vector);
  v4 = rf_vector_scale((float *)v13, 2.0, a4);
  v5 = rf_vector_multiply_scalar(v4, scaled_result, scalar);
  v6 = rf_vector_subtract(v5, v11, out_vector);
  rf_vector_copy(destination, copy_result, v6);
  rf_vector_normalize(destination);
  v7 = atan2f(destination[2], destination[0]);
  *a1 = (v7 * 0.318309873342514 + 1.0) * 0.5;
  *a2 = (1.0 - destination[1]) * 0.5;
  return a1;
}

