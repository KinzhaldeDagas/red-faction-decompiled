// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C9690 rf_material_evaluate_self_illumination
// UNREALRED VERIFIED [self-illumination-20260903]: Evaluates the material self-illumination curve. It computes frame=(time/15)*Material[+0x78], linearly interpolates adjacent float keys from count/pointer +0xB8/+0xBC, holds the final key past the curve end, and clamps the result to [0,1].
double __thiscall rf_material_evaluate_self_illumination(int *this, float a2)
{
  double v2; // st7
  float v5; // [esp+Ch] [ebp-1Ch]
  float v6; // [esp+Ch] [ebp-1Ch]
  float value; // [esp+10h] [ebp-18h]
  float v9; // [esp+1Ch] [ebp-Ch]
  int v10; // [esp+20h] [ebp-8h]
  float v11; // [esp+24h] [ebp-4h]

  value = a2 / 15.0 * (double)*(this + 30);
  v10 = (int)rf_floor_float(value);
  v11 = value - (double)v10;
  if ( v10 + 1 < *(this + 46) )
  {
    v9 = 1.0 - v11;
    v5 = *(float *)(*(this + 47) + 4 * v10) * v9 + *(float *)(*(this + 47) + 4 * (v10 + 1)) * v11;
    v2 = rf_float_minimum_two_values(v5, 1.0);
  }
  else
  {
    v2 = rf_float_minimum_two_values(*(float *)(*(this + 47) + 4 * *(this + 46) - 4), 1.0);
  }
  v6 = v2;
  return (float)rf_float_maximum_two_values(v6, 0.0);
}

