// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA870 rf_rfa_remap_key_alpha_ease
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Cdecl float t,easeOut,easeIn; returns ST0 value. Exact t0/t1 or ease sum0 returns t. If sum>1 scales both easing values by sum. k=1/(2-easeOut-easeIn). For t<easeOut returns k*t*t/easeOut; for t>=1-easeIn returns1-k*(1-t)^2/easeIn; otherwise returns(2*t-easeOut)*k. Float intermediate rounding is present. No input clamp, finite check or guarantee easing bytes are nonnegative; caller converts SIGNED bytes /127.
double __cdecl rf_rfa_remap_key_alpha_ease(float a1, float a2, float a3)
{
  float v7; // [esp+Ch] [ebp-8h]
  float v8; // [esp+10h] [ebp-4h]
  float v9; // [esp+1Ch] [ebp+8h]

  if ( a1 == 0.0 || a1 == 1.0 )
    return a1;
  v8 = a2 + a3;
  if ( v8 == 0.0 )
    return a1;
  if ( v8 > 1.0 )
  {
    a2 = a2 / v8;
    a3 = a3 / v8;
  }
  v7 = 1.0 / (2.0 - a2 - a3);
  if ( a2 <= (double)a1 )
  {
    if ( a1 >= 1.0 - a3 )
    {
      v9 = 1.0 - a1;
      return (float)(1.0 - v7 / a3 * v9 * v9);
    }
    else
    {
      return (float)((a1 * 2.0 - a2) * v7);
    }
  }
  else
  {
    return (float)(v7 / a2 * a1 * a1);
  }
}

