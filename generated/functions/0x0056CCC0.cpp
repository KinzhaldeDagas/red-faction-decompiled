// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056CCC0 rf_segment_sphere_intersection_length
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Cdecl segment endpoints A/B,sphere center,radius. Forms unit direction d=normalize(B-A),records length L,projection p=dot(d,center-A). If p>=-radius and p<L+radius,compute h2=radius^2-(lengthSquared(center-A)-p^2). Only h2>0 accepted;h=sqrt(h2),entry=clamp(p-h,0,L),exit=clamp(p+h,0,L),returns float(exit-entry) via ST0. Otherwise0. Tangency h2==0 gives0;finite segment length inside sphere,not ray hit fraction. Uses normalize helper behavior for degenerate segments;no own radius/finite checks.
double __cdecl rf_segment_sphere_intersection_length(float *rhs, float *lhs, float *a3, float a4)
{
  int v5; // [esp+8h] [ebp-3Ch] BYREF
  float v6; // [esp+Ch] [ebp-38h]
  int v7; // [esp+10h] [ebp-34h] BYREF
  float v8; // [esp+14h] [ebp-30h]
  float v9; // [esp+18h] [ebp-2Ch]
  float v10; // [esp+1Ch] [ebp-28h]
  float v11; // [esp+20h] [ebp-24h]
  float v12; // [esp+24h] [ebp-20h]
  float out_vector[3]; // [esp+28h] [ebp-1Ch] BYREF
  float v14[3]; // [esp+34h] [ebp-10h] BYREF
  float length; // [esp+40h] [ebp-4h]

  v11 = 0.0;
  rf_vector_subtract(lhs, out_vector, rhs);
  length = rf_vector_normalize_get_length(out_vector);
  rf_vector_subtract(a3, v14, rhs);
  v12 = rf_vector_dot(out_vector, v14);
  if ( v12 >= -a4 && v12 < length + a4 )
  {
    v9 = a4 * a4;
    v10 = rf_vector_dot(v14, v14);
    v8 = v9 - (v10 - v12 * v12);
    if ( v8 > 0.0 )
    {
      v6 = rf_sqrt_float(v8);
      *(float *)&v7 = v12 - v6;
      *(float *)&v5 = v12 + v6;
      rf_float_clamp_in_place((float *)&v7, 0.0, length);
      rf_float_clamp_in_place((float *)&v5, 0.0, length);
      return (float)(*(float *)&v5 - *(float *)&v7);
    }
  }
  return v11;
}

