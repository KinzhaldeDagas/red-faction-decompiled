// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4A40 rf_bezier20_evaluate_position
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall20-point object,destination,float t. Nonnull destination zeroed,then sums each stored control vector times0x5A4990(i,count-1,t) for signed count iterations. No count<=20 or t range check,derivative,normalization or allocation. Destination aliasing controls can alter input before calculation. Null destination leaves incidental uninitialized return; count<=0 returns destination after zeroing; positive count leaves loop index in EAX rather than destination. Inspect output instead of relying on inferred pointer return.
float *__thiscall rf_bezier20_evaluate_position(float *this, float *a2, float a3)
{
  float *result; // eax
  float v5; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  if ( a2 )
  {
    result = a2;
    *a2 = 0.0;
    a2[1] = 0.0;
    a2[2] = 0.0;
    for ( i = 0; i < *((_DWORD *)this + 60); ++i )
    {
      v5 = rf_bernstein_basis_factorial_pow(i, *((_DWORD *)this + 60) - 1, a3);
      *a2 = *(this + 3 * i) * v5 + *a2;
      a2[1] = *(this + 3 * i + 1) * v5 + a2[1];
      a2[2] = *(this + 3 * i + 2) * v5 + a2[2];
      result = (float *)(i + 1);
    }
  }
  return result;
}

