// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A540 rf_point2_distance_squared_to_infinite_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(point,A,B). Letd=B-A,v=point-A:returns float(|v|^2-dot(v,d)^2/|d|^2) throughST0. No parameter clamp, closest output, zero-length-line guard, or nonnegative clamp after cancellation. This is supporting LINE distance, not segment distance.
double __cdecl rf_point2_distance_squared_to_infinite_line(const float *a1, const float *a2, const float *a3)
{
  double v5; // [esp+4h] [ebp-28h]
  double v6; // [esp+Ch] [ebp-20h]
  float v7[2]; // [esp+14h] [ebp-18h] BYREF
  float v8[2]; // [esp+1Ch] [ebp-10h] BYREF
  float v9; // [esp+24h] [ebp-8h]
  float v10; // [esp+28h] [ebp-4h]

  rf_vector2_subtract_to_output((float *)a3, v8, (float *)a2);
  rf_vector2_subtract_to_output((float *)a1, v7, (float *)a2);
  v10 = v7[0] * v8[0];
  v9 = v7[1] * v8[1];
  v6 = rf_vector2_length_squared_x87(v7);
  v5 = (v10 + v9) * (v10 + v9);
  return (float)(v6 - v5 / rf_vector2_length_squared_x87(v8));
}

