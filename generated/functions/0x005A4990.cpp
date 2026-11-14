// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4990 rf_bernstein_basis_factorial_pow
// UNREALRED VERIFIED [character-pipeline-20261029]: Arguments basis index i,degree n,float t; returns float-rounded Bernstein n!/(i!*(n-i)!)*pow(t,i)*pow(1-t,n-i). Factorials use0x5A4850; denominator multiplication occurs in32-bit integer arithmetic before floating division,so overflow can precede float conversion. Both powers are float wrappers0x573D50,NOT hypot. No i/n/range/overflow/zero-denominator check; t is not clamped to0..1. Stack inputs and direct power calls establish the formula.
double __stdcall rf_bernstein_basis_factorial_pow(int a1, int a2, float X)
{
  int v3; // esi
  float Y; // [esp+4h] [ebp-34h]
  float Ya; // [esp+4h] [ebp-34h]
  float v8; // [esp+10h] [ebp-28h]
  double v9; // [esp+1Ch] [ebp-1Ch]
  float v10; // [esp+2Ch] [ebp-Ch]
  float v11; // [esp+30h] [ebp-8h]
  float v12; // [esp+34h] [ebp-4h]

  v9 = (double)rf_integer_factorial_iterative(a2);
  v3 = rf_integer_factorial_iterative(a1);
  v12 = v9 / (double)(rf_integer_factorial_iterative(a2 - a1) * v3);
  Y = (float)a1;
  v11 = rf_pow_float_forward(X, Y);
  Ya = (float)(a2 - a1);
  v8 = 1.0 - X;
  v10 = rf_pow_float_forward(v8, Ya);
  return (float)(v12 * v11 * v10);
}

