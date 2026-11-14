// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583B00 rf_quaternion_s16_pure_exp_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered in-place signed16 pure exponential:decodes original xyz,computes r and sinc(r) with tiny-r factor1,scales original signed words and sets w=trunc(cos(r)*16383) low16bits. Ignores original w. EAX returns FULL converted integer w,not receiver pointer (WORD store may wrap independently). No saturation,finite check or normalization.
int __thiscall rf_quaternion_s16_pure_exp_in_place(__int16 *this)
{
  int result; // eax
  float v2; // [esp+10h] [ebp-34h]
  float v3; // [esp+14h] [ebp-30h]
  float v4; // [esp+1Ch] [ebp-28h]
  float v5; // [esp+24h] [ebp-20h]
  float v7; // [esp+34h] [ebp-10h]
  float v8; // [esp+3Ch] [ebp-8h]

  v5 = (double)*this * 0.00006103888154029846;
  v4 = (double)*(this + 1) * 0.00006103888154029846;
  v3 = (double)*(this + 2) * 0.00006103888154029846;
  v2 = v5 * v5 + v4 * v4 + v3 * v3;
  v7 = rf_sqrt_float(v2);
  if ( v7 <= 1.000000013351432e-10 )
    v8 = 1.0;
  else
    v8 = rf_sin_float(v7) / v7;
  *this = (int)((double)*this * v8);
  *(this + 1) = (int)((double)*(this + 1) * v8);
  *(this + 2) = (int)((double)*(this + 2) * v8);
  result = (int)(rf_cos_float(v7) * 16383.0);
  *(this + 3) = result;
  return result;
}

