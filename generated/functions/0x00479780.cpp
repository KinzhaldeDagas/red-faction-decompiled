// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479780 rf_texture_scaled_uv_edge_length
// UNREALRED VERIFIED [level-lifecycle-20261028]: Actual result is x87 floating return despite void prototype. Computes x=(u1-u0)*signed integer texture_width and y=(v1-v0)*signed texture_height, rounds components through float, returns sqrt(x*x+y*y) through0x558A90. No coordinate clamp or texture dimension validation; used for texel-space triangle areas.
void __cdecl rf_texture_scaled_uv_edge_length(int a1, int a2, float a3, float a4, float a5, float a6)
{
  float v6; // [esp+8h] [ebp-10h]
  float v7; // [esp+Ch] [ebp-Ch]
  float v8[2]; // [esp+10h] [ebp-8h] BYREF

  v7 = (a6 - a4) * (double)a2;
  v6 = (a5 - a3) * (double)a1;
  rf_vector2_assign_components(v8, v6, v7);
  rf_vector2_length(v8);
}

