// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054D870 rf_polygon2_area_triangle_fan_heron
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Arguments vertexcount,contiguous8-byteXYarray. Triangulates fan aboutvertex0; for i1..count-2 computes threesidelengths and Heronradicand s*(s-a)*(s-b)*(s-c),clampsnegative0. If ANY fantriangle radicand==0,returns0 immediately,discarding accumulatedearlierarea. Otherwise sums square-rootareas andreturns floataccumulation inx87. Count<3returns0. Unsignedgeometricarea sum,notshoelaceororientationtest; concave/overlappingfan can overcount. No pointer/count/finite checks.
double __cdecl rf_polygon2_area_triangle_fan_heron(int a1, float *a2)
{
  double v3; // st7
  float v4[2]; // [esp+8h] [ebp-40h] BYREF
  float v5; // [esp+10h] [ebp-38h]
  float v6; // [esp+14h] [ebp-34h]
  float *v7; // [esp+18h] [ebp-30h]
  float v8; // [esp+1Ch] [ebp-2Ch]
  float v9[2]; // [esp+20h] [ebp-28h] BYREF
  float v10; // [esp+28h] [ebp-20h]
  float *v11; // [esp+2Ch] [ebp-1Ch]
  float v12; // [esp+30h] [ebp-18h]
  float v13[2]; // [esp+34h] [ebp-14h] BYREF
  int i; // [esp+3Ch] [ebp-Ch]
  float v15; // [esp+40h] [ebp-8h]
  float *v16; // [esp+44h] [ebp-4h]

  v16 = a2;
  v15 = 0.0;
  for ( i = 1; i < a1 - 1; ++i )
  {
    v11 = &a2[2 * i];
    v7 = &a2[2 * i + 2];
    rf_vector2_subtract_to_output(v16, v4, v11);
    rf_vector2_subtract_to_output(v16, v13, v7);
    rf_vector2_subtract_to_output(v11, v9, v7);
    v12 = rf_vector2_length(v4);
    v8 = rf_vector2_length(v13);
    v5 = rf_vector2_length(v9);
    v10 = (v12 + v8 + v5) / 2.0;
    v6 = (v10 - v12) * v10 * (v10 - v8) * (v10 - v5);
    if ( v6 < 0.0 )
      v6 = 0.0;
    if ( v6 == 0.0 )
      return 0.0;
    v3 = rf_sqrt_float(v6);
    v15 = v3 + v15;
  }
  return v15;
}

