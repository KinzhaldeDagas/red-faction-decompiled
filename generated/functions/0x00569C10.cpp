// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569C10 rf_segment_sphere_intersection
// [UnrealRed physical spheres 2026-11-12; verified ASM] Segment/sphere is not closest finite-segment distance: nonzeroL normalizes delta, q must be in[-r,L+r], infinite-line perpendicular distance h must be STRICTLY <r. Computes entry=q-sqrt(r*r-h*h); out=start+dir*entry only if0<=entry<=L, else out=start and STILL returns1. Thus tangent misses and an outside-segment entry can hit. DegenerateL<=0 writes out=start even on miss, returns distance(start,center)<r. Ordinary misses preserve out. Native no finite/radius validation; host finite domain and sqrt/x87 differences must remain explicit.
bool __cdecl rf_segment_sphere_intersection(float *destination, float *rhs, float *lhs, float *a4, float a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float v12; // [esp+8h] [ebp-C0h]
  float v13[3]; // [esp+10h] [ebp-B8h] BYREF
  float v14[3]; // [esp+1Ch] [ebp-ACh] BYREF
  float v15[3]; // [esp+28h] [ebp-A0h] BYREF
  float v16[3]; // [esp+34h] [ebp-94h] BYREF
  float v17[3]; // [esp+40h] [ebp-88h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-7Ch] BYREF
  float scaled_result[3]; // [esp+58h] [ebp-70h] BYREF
  float v20[3]; // [esp+64h] [ebp-64h] BYREF
  float v21[3]; // [esp+70h] [ebp-58h] BYREF
  float v22[3]; // [esp+7Ch] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+88h] [ebp-40h] BYREF
  float out_vector[3]; // [esp+94h] [ebp-34h] BYREF
  float v25; // [esp+A0h] [ebp-28h]
  float v26; // [esp+A4h] [ebp-24h]
  float v27; // [esp+A8h] [ebp-20h]
  float scalar; // [esp+ACh] [ebp-1Ch]
  float v29; // [esp+B0h] [ebp-18h]
  float v30; // [esp+B4h] [ebp-14h]
  float v31; // [esp+B8h] [ebp-10h]
  int v32; // [esp+C4h] [ebp-4h]

  if ( (dword_1809160[0] & 1) == 0 )
  {
    dword_1809160[0] |= 1u;
    rf_vector3_default_construct_noop(&flt_1809154);
    v32 = -1;
  }
  if ( (dword_1809160[0] & 2) == 0 )
  {
    dword_1809160[0] |= 2u;
    rf_vector3_default_construct_noop(&flt_1809148);
    v32 = -1;
  }
  if ( (dword_1809160[0] & 4) == 0 )
  {
    dword_1809160[0] |= 4u;
    rf_vector3_default_construct_noop(unk_180913C);
    v32 = -1;
  }
  if ( (dword_1809160[0] & 8) == 0 )
  {
    dword_1809160[0] |= 8u;
    rf_vector3_default_construct_noop(&flt_1809130);
    v32 = -1;
  }
  v5 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(&flt_1809154, copy_result, v5);
  v6 = rf_vector_subtract(a4, v22, rhs);
  rf_vector_copy(unk_180913C, v21, v6);
  v30 = rf_vector3_length(&flt_1809154);
  if ( v30 > 0.0 )
  {
    flt_1809148 = flt_1809154 / v30;
    unk_180914C = unk_1809158 / v30;
    unk_1809150 = unk_180915C / v30;
    scalar = rf_vector_dot(&flt_1809148, unk_180913C);
    if ( scalar >= -a5 )
    {
      if ( scalar <= v30 + a5 )
      {
        v8 = rf_vector_multiply_scalar(&flt_1809148, scaled_result, scalar);
        v9 = rf_vector_add(rhs, sum_result, v8);
        rf_vector_copy(&flt_1809130, v17, v9);
        v29 = rf_vector_distance(&flt_1809130, a4);
        if ( a5 <= (double)v29 )
        {
          return 0;
        }
        else
        {
          v26 = v29 * v29;
          v25 = a5 * a5;
          v12 = v25 - v26;
          v27 = rf_sqrt_float(v12);
          v31 = scalar - v27;
          if ( v30 >= (double)v31 && v31 >= 0.0 )
          {
            v10 = rf_vector_multiply_scalar(&flt_1809148, v15, v31);
            v11 = rf_vector_add(rhs, v14, v10);
            rf_vector_copy(destination, v13, v11);
            return 1;
          }
          else
          {
            rf_vector_copy(destination, v16, rhs);
            return 1;
          }
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    v31 = rf_vector3_length(unk_180913C);
    rf_vector_copy(destination, v20, rhs);
    return a5 > (double)v31;
  }
}

