// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005839C0 rf_quaternion_s16_unit_log_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered in-place signed16 logarithm. Decodes xyz/w tofloat,computes atan2(r,w)/r for r>0 else0;scales original signed xyz words byfactor via integer truncation/low16stores,sets w0,returns receiver. No real log(norm) term,saturation or input normalization.
__int16 *__thiscall rf_quaternion_s16_unit_log_in_place(__int16 *this)
{
  float v2; // [esp+14h] [ebp-40h]
  float Y; // [esp+18h] [ebp-3Ch]
  float v4; // [esp+20h] [ebp-34h]
  float v5; // [esp+28h] [ebp-2Ch]
  float v6; // [esp+30h] [ebp-24h]
  float v8; // [esp+3Ch] [ebp-18h]
  float X; // [esp+48h] [ebp-Ch]

  v6 = (double)*this * 0.00006103888154029846;
  v5 = (double)*(this + 1) * 0.00006103888154029846;
  v4 = (double)*(this + 2) * 0.00006103888154029846;
  Y = (double)*(this + 3) * 0.00006103888154029846;
  v2 = v6 * v6 + v5 * v5 + v4 * v4;
  X = rf_sqrt_float(v2);
  if ( X > 0.0 )
  {
    v8 = atan2f(X, Y);
    X = v8 / X;
  }
  *this = (int)((double)*this * X);
  *(this + 1) = (int)((double)*(this + 1) * X);
  *(this + 2) = (int)((double)*(this + 2) * X);
  *(this + 3) = 0;
  return this;
}

