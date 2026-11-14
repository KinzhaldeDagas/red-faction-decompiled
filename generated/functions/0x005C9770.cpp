// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C9770 rf_material_evaluate_alpha
// UNREALRED VERIFIED [material-animation-20260903]: Evaluates the material alpha curve from count/pointer +0xC0/+0xC4 at frame=(time/15)*rate(+0x78), using adjacent-key linear interpolation, final-key hold, and [0,1] clamp. Mesh submission multiplies this value into every base, crossfade, specular, and reflection pass alpha.
double __thiscall rf_material_evaluate_alpha(int *this, float a2)
{
  double v2; // st7
  float value; // [esp+Ch] [ebp-1Ch]
  float v6; // [esp+14h] [ebp-14h]
  float v7; // [esp+1Ch] [ebp-Ch]
  float v8; // [esp+1Ch] [ebp-Ch]
  float v10; // [esp+20h] [ebp-8h]
  int v11; // [esp+24h] [ebp-4h]

  value = a2 / 15.0 * (double)*(this + 30);
  v11 = (int)rf_floor_float(value);
  v10 = value - (double)v11;
  if ( v11 + 1 < *(this + 48) )
  {
    v6 = 1.0 - v10;
    v7 = *(float *)(*(this + 49) + 4 * v11) * v6 + *(float *)(*(this + 49) + 4 * (v11 + 1)) * v10;
    v2 = rf_float_minimum_two_values(v7, 1.0);
  }
  else
  {
    v2 = rf_float_minimum_two_values(*(float *)(*(this + 49) + 4 * *(this + 48) - 4), 1.0);
  }
  v8 = v2;
  return (float)rf_float_maximum_two_values(v8, 0.0);
}

