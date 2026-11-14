// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A000 rf_renderer_compute_nonworld_diffuse_rgb8
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Produces non-world ambient/diffuse RGB8. It optionally seeds ambient RGB, accumulates all active light types, max-channel normalizes values above one, then applies the caller scale. Scale <= 1 floors each channel at ambient; scale > 1 caps each at one. Finally it multiplies by 255 and truncates toward zero.
int __cdecl rf_renderer_compute_nonworld_diffuse_rgb8(
        _BYTE *a1,
        _BYTE *a2,
        _BYTE *a3,
        char a4,
        float *a5,
        float *a6,
        float a7)
{
  int result; // eax
  float v8; // [esp+4h] [ebp-1Ch]
  float v9; // [esp+8h] [ebp-18h]
  float v10; // [esp+Ch] [ebp-14h]
  float v11; // [esp+10h] [ebp-10h]
  float v12; // [esp+14h] [ebp-Ch] BYREF
  float v13; // [esp+18h] [ebp-8h] BYREF
  float v14; // [esp+1Ch] [ebp-4h] BYREF

  if ( a4 )
  {
    v14 = flt_663B1C;
    v13 = flt_663B20;
    v12 = flt_663B24;
  }
  else
  {
    v12 = 0.0;
    v13 = 0.0;
    v14 = 0.0;
  }
  rf_renderer_accumulate_active_light_rgb(&v14, &v13, &v12, a5, a6, 0, 0, nullptr);
  v9 = v12;
  v8 = rf_float_maximum_two_values(v14, v13);
  v11 = rf_float_maximum_two_values(v8, v9);
  if ( v11 > 1.0 )
  {
    v10 = 1.0 / v11;
    v14 = v14 * v10;
    v13 = v13 * v10;
    v12 = v12 * v10;
  }
  if ( a7 >= 0.0 )
  {
    v14 = v14 * a7;
    v13 = v13 * a7;
    v12 = v12 * a7;
    if ( a7 <= 1.0 )
    {
      v14 = rf_float_maximum_two_values(v14, flt_663B1C);
      v13 = rf_float_maximum_two_values(v13, flt_663B20);
      v12 = rf_float_maximum_two_values(v12, flt_663B24);
    }
    else
    {
      v14 = rf_float_minimum_two_values(v14, 1.0);
      v13 = rf_float_minimum_two_values(v13, 1.0);
      v12 = rf_float_minimum_two_values(v12, 1.0);
    }
  }
  *a1 = (int)(v14 * 255.0);
  *a2 = (int)(v13 * 255.0);
  result = (int)(v12 * 255.0);
  *a3 = result;
  return result;
}

