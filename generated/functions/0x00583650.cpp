// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583650 rf_quaternion_s16_unit_log_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Decodes signed16 xyz/w with exact1/16383-like literal0.00006103888154029846,computes r and atan2(r,w)/r when r>0,else factor0. Multiplies ORIGINAL signed words xyz by factor,truncates toint/low16bits,w=0. Retains fixed-point scaling;does not output floats,normalize or include real log(norm). Returns output;no overflow/saturation/finite guards.
_WORD *__thiscall rf_quaternion_s16_unit_log_to_destination(__int16 *this, _WORD *a2)
{
  float v3; // [esp+14h] [ebp-40h]
  float Y; // [esp+18h] [ebp-3Ch]
  float v5; // [esp+20h] [ebp-34h]
  float v6; // [esp+28h] [ebp-2Ch]
  float v7; // [esp+30h] [ebp-24h]
  float v9; // [esp+3Ch] [ebp-18h]
  float X; // [esp+48h] [ebp-Ch]

  v7 = (double)*this * 0.00006103888154029846;
  v6 = (double)*(this + 1) * 0.00006103888154029846;
  v5 = (double)*(this + 2) * 0.00006103888154029846;
  Y = (double)*(this + 3) * 0.00006103888154029846;
  v3 = v7 * v7 + v6 * v6 + v5 * v5;
  X = rf_sqrt_float(v3);
  if ( X > 0.0 )
  {
    v9 = atan2f(X, Y);
    X = v9 / X;
  }
  rf_short_quaternion_set_components(
    a2,
    (int)((double)*this * X),
    (int)((double)*(this + 1) * X),
    (int)((double)*(this + 2) * X),
    0);
  return a2;
}

