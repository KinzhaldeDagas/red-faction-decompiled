// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C9580 rf_material_evaluate_texture_crossfade
// UNREALRED VERIFIED [material-animation-20260903]: Evaluates the two-texture material's crossfade curve from count/pointer +0x7C/+0x80 at frame=(time/15)*rate(+0x78), using adjacent-key linear interpolation, final-key hold, and [0,1] clamp. Material types 0 and 2 return zero; the consumer weights slot 0 by 1-value and slot 1 by value.
double __thiscall rf_material_evaluate_texture_crossfade(int *this, float a2)
{
  double v3; // st7
  int v4; // [esp+8h] [ebp-24h]
  float value; // [esp+10h] [ebp-1Ch]
  float v7; // [esp+1Ch] [ebp-10h]
  float v8; // [esp+1Ch] [ebp-10h]
  float v10; // [esp+20h] [ebp-Ch]
  int v11; // [esp+24h] [ebp-8h]
  float v12; // [esp+28h] [ebp-4h]

  v4 = *this;
  if ( !*this )
    return 0.0;
  if ( v4 == 1 )
  {
    value = a2 / 15.0 * (double)*(this + 30);
    v11 = (int)rf_floor_float(value);
    v12 = value - (double)v11;
    if ( v11 + 1 < *(this + 31) )
    {
      v10 = 1.0 - v12;
      v7 = *(float *)(*(this + 32) + 4 * v11) * v10 + *(float *)(*(this + 32) + 4 * (v11 + 1)) * v12;
      v3 = rf_float_minimum_two_values(v7, 1.0);
    }
    else
    {
      v3 = rf_float_minimum_two_values(*(float *)(*(this + 32) + 4 * *(this + 31) - 4), 1.0);
    }
    v8 = v3;
    return (float)rf_float_maximum_two_values(v8, 0.0);
  }
  else
  {
    if ( v4 == 2 )
      return 0.0;
    return 0.0;
  }
}

