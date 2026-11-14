// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A9A0 rf_matrix3_set_euler_angles
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): Corrected stale stdcall(float,float,float) to ECX destination plus3float stack args(pitch,bank,heading), RET12. Computes sin/cos of each in that order, then calls55A8F0 with(sp,cp,sb,cb,sh,ch), returns matrix. No degree conversion, clamp or angle wrapping.
float *__thiscall rf_matrix3_set_euler_angles(float *this, float a2, float a3, float a4)
{
  float v6; // [esp+1Ch] [ebp-18h]
  float v7; // [esp+20h] [ebp-14h]
  float v8; // [esp+24h] [ebp-10h]
  float v9; // [esp+28h] [ebp-Ch]
  float v10; // [esp+2Ch] [ebp-8h]
  float v11; // [esp+30h] [ebp-4h]

  v6 = rf_sin_float(a2);
  v8 = rf_cos_float(a2);
  v10 = rf_sin_float(a3);
  v11 = rf_cos_float(a3);
  v7 = rf_sin_float(a4);
  v9 = rf_cos_float(a4);
  return rf_matrix3_set_euler_sincos(this, v6, v8, v10, v11, v7, v9);
}

