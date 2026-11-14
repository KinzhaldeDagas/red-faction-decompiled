// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A8F0 rf_matrix3_set_euler_sincos
// UNREALRED VERIFIED [mission-mover-runtime-20261013] For pitch=heading=0 and bank=angle, rows are (cos,sin,0),(-sin,cos,0),(0,0,1). Mover axis helper0x559BD0 uses inverse rotation by this bank matrix, establishing the angle sign independently of visual convention.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX matrix plus(sp,cp,sb,cb,sh,ch), RET24. Writes rows:(sp*sb*sh+cb*ch,sb*cp,sp*sb*ch-cb*sh);(sp*cb*sh-sb*ch,cb*cp,sp*cb*ch+sb*sh);(sh*cp,-sp,ch*cp). No trig or validation. For pitch=heading0, bank angle gives rows(cos,sin,0),(-sin,cos,0),(0,0,1). Returns matrix.
float *__thiscall rf_matrix3_set_euler_sincos(float *this, float a2, float a3, float a4, float a5, float a6, float a7)
{
  float v8; // [esp+4h] [ebp-10h]
  float v9; // [esp+8h] [ebp-Ch]
  float v10; // [esp+Ch] [ebp-8h]
  float v11; // [esp+10h] [ebp-4h]

  v10 = a4 * a6;
  v11 = a5 * a7;
  v8 = a5 * a6;
  v9 = a4 * a7;
  *this = a2 * v10 + v11;
  *(this + 5) = a2 * v11 + v10;
  *(this + 3) = a2 * v8 - v9;
  *(this + 2) = a2 * v9 - v8;
  *(this + 6) = a6 * a3;
  *(this + 1) = a4 * a3;
  *(this + 4) = a5 * a3;
  *(this + 8) = a7 * a3;
  *(this + 7) = -a2;
  return this;
}

