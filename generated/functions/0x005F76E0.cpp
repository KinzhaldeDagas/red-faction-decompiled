// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F76E0 rf_keytrack_remap_ease_parameter
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl float t,easeOut a,easeIn b. Returns t immediately for exact t0/1 or a+b==0. If sum>1,normalizes a and b by float sum. k=float(1/(2-a-b));t<a ->float(k/a*t*t);otherwise t>=1-b ->float(1-k/b*(1-t)^2);middle ->float((2*t-a)*k). Float intermediates/x87 returns. No clamp for t,a,b,negative values,NaN or singular denominators;valid nonnegative ease fractions give quadratic/linear/quadratic timing curve. Signed ease bytes can supply negative values.
double __cdecl rf_keytrack_remap_ease_parameter(float a1, float a2, float a3)
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

