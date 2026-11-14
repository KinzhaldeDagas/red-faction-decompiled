// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056A270 rf_swept_sphere_plane_slab_interval
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(outPlanePoint,start,delta,radius,normal,planePoint,outEnter,outSpan). Stores d=-dot(N,planePoint),s=dot(N,start),v=dot(N,delta). If abs(float(v))<=double(1e-30) returns0 without output; no static-overlap fallback. t0=(-d-s+radius)/v,t1=(-d-s-radius)/v,stored floats then swapped if t0>t1. Writes outEnter=t0 even when no interval overlap. Writes projected contact point ONLY if0<t0<1: P=start+delta*t0,then559B70(out,P,N,planePoint); projection assumes unitN. Always writes outSpan=t1-t0 after nonparallel branch,unclipped to[0,1]. Returns t0<1 &&t1>0,strict interval endpoints. When start overlaps (t0<=0),can return1 with outPlanePoint untouched. Shared point scratch1809164 without locking; radius/normal validity
// unchecked.
bool __cdecl rf_swept_sphere_plane_slab_interval(
        float *output,
        float *lhs,
        float *vector,
        float a4,
        float *normal,
        float *plane_point,
        float *a7,
        float *a8)
{
  float *v9; // eax
  float *v10; // eax
  float v12; // [esp+Ch] [ebp-4Ch]
  float copy_result[3]; // [esp+10h] [ebp-48h] BYREF
  float sum_result[3]; // [esp+1Ch] [ebp-3Ch] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-30h] BYREF
  float v16; // [esp+34h] [ebp-24h]
  float v17; // [esp+38h] [ebp-20h]
  float scalar; // [esp+3Ch] [ebp-1Ch]
  float v19; // [esp+40h] [ebp-18h]
  float v20; // [esp+44h] [ebp-14h]
  float v21; // [esp+48h] [ebp-10h]
  int v22; // [esp+54h] [ebp-4h]

  v17 = -rf_vector_dot(normal, plane_point);
  v20 = rf_vector_dot(normal, lhs);
  v21 = rf_vector_dot(normal, vector);
  v12 = fabs(v21);
  if ( v12 <= 1.000000003171077e-30 )
    return 0;
  scalar = (-v17 - v20 + a4) / v21;
  v19 = (-v17 - v20 - a4) / v21;
  if ( scalar > (double)v19 )
  {
    v16 = scalar;
    scalar = v19;
    v19 = v16;
  }
  *a7 = scalar;
  if ( scalar > 0.0 && scalar < 1.0 )
  {
    if ( (dword_1809170 & 1) == 0 )
    {
      dword_1809170 |= 1u;
      rf_vector3_default_construct_noop(&dword_1809160[1]);
      v22 = -1;
    }
    v9 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
    v10 = rf_vector_add(lhs, sum_result, v9);
    rf_vector_copy((float *)&dword_1809160[1], copy_result, v10);
    rf_point_project_to_plane(output, (const float *)&dword_1809160[1], normal, plane_point);
  }
  *a8 = v19 - scalar;
  return scalar < 1.0 && v19 > 0.0;
}

