// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055AA50 rf_matrix3_set_axis_angle_unchecked_axis
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX matrix plus axisXYZ and angleRadians, RET8. Forms quaternion xyz=axis*sin(angle/2),w=cos(angle/2), then standard row-vector quaternion3x3 polynomial with diagonal1-2otherSquares and signed cross terms. Does NOT normalize axis or quaternion, so nonunit axis generally yields nonorthonormal matrix. Returns receiver, no degenerate checks.
float *__thiscall rf_matrix3_set_axis_angle_unchecked_axis(float *this, float *a2, float a3)
{
  float v4; // [esp+8h] [ebp-40h]
  float v6; // [esp+10h] [ebp-38h]
  float v7; // [esp+14h] [ebp-34h]
  float v8; // [esp+18h] [ebp-30h]
  float v9; // [esp+1Ch] [ebp-2Ch]
  float v10; // [esp+20h] [ebp-28h]
  float v11; // [esp+24h] [ebp-24h]
  float v12; // [esp+28h] [ebp-20h]
  float v13; // [esp+2Ch] [ebp-1Ch]
  float v14; // [esp+30h] [ebp-18h]
  float v15; // [esp+34h] [ebp-14h]
  float v16; // [esp+38h] [ebp-10h]
  float v17; // [esp+3Ch] [ebp-Ch]
  float v18; // [esp+40h] [ebp-8h]
  float v19; // [esp+44h] [ebp-4h]

  v4 = a3 * 0.5;
  v7 = rf_sin_float(v4);
  v16 = *a2 * v7;
  v10 = a2[1] * v7;
  v8 = a2[2] * v7;
  v14 = rf_cos_float(v4);
  v19 = v16 * v16;
  v12 = v10 * v10;
  v17 = v8 * v8;
  v13 = v16 * v10;
  v9 = v16 * v8;
  v18 = v10 * v8;
  v11 = v14 * v16;
  v15 = v14 * v10;
  v6 = v14 * v8;
  *this = 1.0 - v12 * 2.0 - v17 * 2.0;
  *(this + 1) = v13 * 2.0 + v6 * 2.0;
  *(this + 2) = v9 * 2.0 - v15 * 2.0;
  *(this + 3) = v13 * 2.0 - v6 * 2.0;
  *(this + 4) = 1.0 - v19 * 2.0 - v17 * 2.0;
  *(this + 5) = v18 * 2.0 + v11 * 2.0;
  *(this + 6) = v9 * 2.0 + v15 * 2.0;
  *(this + 7) = v18 * 2.0 - v11 * 2.0;
  *(this + 8) = 1.0 - v19 * 2.0 - v12 * 2.0;
  return this;
}

