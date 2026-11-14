// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A44A0 rf_cubic_bezier_bernstein_basis
// UNREALRED VERIFIED [cutscene-playback-20261028]: For basis index0..3 returns float-rounded Bernstein weight: (1-t)^3,3*t*(1-t)^2,3*t^2*(1-t),t^3 respectively; invalid index returns0. No clamp of t to[0,1], so polynomial extrapolation is allowed. Uses x87 intermediates and explicit float stores.
double __cdecl rf_cubic_bezier_bernstein_basis(int a1, float a2)
{
  double result; // st7
  float v3; // [esp+0h] [ebp-18h]
  float v4; // [esp+4h] [ebp-14h]
  float v5; // [esp+8h] [ebp-10h]
  float v6; // [esp+Ch] [ebp-Ch]
  float v7; // [esp+14h] [ebp-4h]
  float v8; // [esp+14h] [ebp-4h]
  float v9; // [esp+14h] [ebp-4h]

  switch ( a1 )
  {
    case 0:
      v7 = 1.0 - a2;
      v6 = v7 * v7 * v7;
      result = v6;
      break;
    case 1:
      v8 = 1.0 - a2;
      v5 = a2 * 3.0 * v8 * v8;
      result = v5;
      break;
    case 2:
      v9 = 1.0 - a2;
      v4 = a2 * 3.0 * a2 * v9;
      result = v4;
      break;
    case 3:
      v3 = a2 * a2 * a2;
      result = v3;
      break;
    default:
      result = 0.0;
      break;
  }
  return result;
}

