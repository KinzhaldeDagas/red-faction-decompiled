// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583780 rf_quaternion_s16_pure_exp_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered signed16 pure-quaternion exponential. Decodes xyz with0.00006103888154029846,r=sqrt(sumxyz2),factor1 for r<=~1e-10 else sin(r)/r. Outputs low16bits of truncated ORIGINAL signed xyz*factor and w=cos(r)*16383. Ignores input w,no exp(real-part) or saturation/normalization. Returns output;zero-vector input yields packed w16383,not default constructor w1.
__int16 *__thiscall rf_quaternion_s16_pure_exp_to_destination(const __int16 *this, __int16 *a2)
{
  int v3; // [esp+0h] [ebp-44h]
  float v4; // [esp+10h] [ebp-34h]
  float v5; // [esp+14h] [ebp-30h]
  float v6; // [esp+1Ch] [ebp-28h]
  float v7; // [esp+24h] [ebp-20h]
  float v9; // [esp+34h] [ebp-10h]
  float v10; // [esp+3Ch] [ebp-8h]

  v7 = (double)*this * 0.00006103888154029846;
  v6 = (double)*(this + 1) * 0.00006103888154029846;
  v5 = (double)*(this + 2) * 0.00006103888154029846;
  v4 = v7 * v7 + v6 * v6 + v5 * v5;
  v9 = rf_sqrt_float(v4);
  if ( v9 <= 1.000000013351432e-10 )
    v10 = 1.0;
  else
    v10 = rf_sin_float(v9) / v9;
  v3 = (int)(rf_cos_float(v9) * 16383.0);
  rf_short_quaternion_set_components(
    a2,
    (int)((double)*this * v10),
    (int)((double)*(this + 1) * v10),
    (int)((double)*(this + 2) * v10),
    v3);
  return a2;
}

