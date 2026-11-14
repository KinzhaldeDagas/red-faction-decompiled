// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056A540 rf_swept_sphere_edge_or_start_vertex_contact
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Cdecl outContact,start,delta,radius,edgeStart,edgeEnd,outT,maxT. E=edgeEnd-edgeStart,W=start-edgeStart. Infinite-cylinder quadratic coefficients A=(E.dot(delta))^2-|E|^2*|delta|^2,B=2*(W.dot(E)*E.dot(delta)-W.dot(delta)*|E|^2),C=(W.dot(E))^2+radius^2*|E|^2-|W|^2*|E|^2. A0 selects endpoint fallback;discriminant<=0 rejects tangency. Sorts roots;near-negative earliest root[-0.05,0) becomes~1e-6. Acceptable time must be in[0,1] and STRICTLY<maxT. Projects impact center onto edge;projection outside[0,1] selects fallback. Fallback solves moving point vs radius sphere around EDGE START only,also rejects discriminant<=0 and out-of-range/noncloser roots (outer polygon loop supplies each vertex as edgeStart). Writes contact on edge or
// edgeStart,not center,then outT. Uses static scratch1809174/1809180 with unsynchronized init flags. Nonfinite values and negative radius are not rejected up front;coefficient/root tests above determine degenerate outcomes. This describes the actual implementation.
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Contact output is EdgeStart+EdgeVector*floatProjection for admitted cylinder branch, or exactly EdgeStart for endpoint fallback. It is NOT impact center. Both branches require T strictly below supplied maximum; cylinder near-negative nudge and discriminant/tangency rules remain as prior notes. Radius/normal output downstream depends on this actual point.
char __cdecl rf_swept_sphere_edge_or_start_vertex_contact(
        float *destination,
        float *a2,
        float *vector,
        float a4,
        float *rhs,
        float *lhs,
        float *a7,
        float a8)
{
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  double v12; // st7
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float v17[3]; // [esp+8h] [ebp-F4h] BYREF
  float v18[3]; // [esp+14h] [ebp-E8h] BYREF
  float v19[3]; // [esp+20h] [ebp-DCh] BYREF
  float v20[3]; // [esp+2Ch] [ebp-D0h] BYREF
  float v21[3]; // [esp+38h] [ebp-C4h] BYREF
  float v22[3]; // [esp+44h] [ebp-B8h] BYREF
  float v23[3]; // [esp+50h] [ebp-ACh] BYREF
  float v24[3]; // [esp+5Ch] [ebp-A0h] BYREF
  float v25[3]; // [esp+68h] [ebp-94h] BYREF
  float copy_result[3]; // [esp+74h] [ebp-88h] BYREF
  float sum_result[3]; // [esp+80h] [ebp-7Ch] BYREF
  float scaled_result[3]; // [esp+8Ch] [ebp-70h] BYREF
  float v29; // [esp+98h] [ebp-64h]
  int v30; // [esp+9Ch] [ebp-60h]
  float v31; // [esp+A0h] [ebp-5Ch]
  float scalar; // [esp+A4h] [ebp-58h]
  float v33; // [esp+A8h] [ebp-54h]
  float v34; // [esp+ACh] [ebp-50h]
  float v35[3]; // [esp+B0h] [ebp-4Ch] BYREF
  float v36; // [esp+BCh] [ebp-40h]
  float v37; // [esp+C0h] [ebp-3Ch]
  float v38; // [esp+C4h] [ebp-38h]
  float v39; // [esp+C8h] [ebp-34h]
  float v40; // [esp+CCh] [ebp-30h]
  float v41; // [esp+D0h] [ebp-2Ch]
  float v42; // [esp+D4h] [ebp-28h]
  float out_vector[3]; // [esp+D8h] [ebp-24h] BYREF
  float v44; // [esp+E4h] [ebp-18h]
  float v45; // [esp+E8h] [ebp-14h]
  float v46; // [esp+ECh] [ebp-10h]
  int v47; // [esp+F8h] [ebp-4h]

  if ( (dword_180918C & 1) == 0 )
  {
    dword_180918C |= 1u;
    rf_vector3_default_construct_noop(&flt_1809180);
    v47 = -1;
  }
  if ( (dword_180918C & 2) == 0 )
  {
    dword_180918C |= 2u;
    rf_vector3_default_construct_noop(&flt_1809174);
    v47 = -1;
  }
  v30 = 0;
  rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_subtract(a2, v35, rhs);
  v41 = rf_vector_dot(v35, out_vector);
  v40 = rf_vector_dot(v35, vector);
  v45 = rf_vector_length_squared(v35);
  v42 = rf_vector_dot(out_vector, vector);
  v46 = rf_vector_length_squared(out_vector);
  v36 = rf_vector_length_squared(vector);
  scalar = 0.0;
  v44 = 0.0;
  v31 = v42 * v42 - v46 * v36;
  v37 = (v41 * v42 - v40 * v46) * 2.0;
  v33 = v41 * v41 + a4 * a4 * v46 - v45 * v46;
  if ( v31 == 0.0 )
  {
    v30 = 1;
  }
  else
  {
    v34 = v37 * v37 - v31 * 4.0 * v33;
    if ( v34 <= 0.0 )
      return 0;
    v38 = rf_sqrt_float(v34);
    scalar = (v38 - v37) / (v31 * 2.0);
    v44 = (-v37 - v38) / (v31 * 2.0);
    if ( scalar > (double)v44 )
    {
      v39 = scalar;
      scalar = v44;
      v44 = v39;
    }
    if ( scalar >= -0.05000000074505806 && scalar < 0.0 )
      scalar = 0.000001;
    if ( scalar >= 0.0 && scalar <= 1.0 )
    {
      if ( a8 <= (double)scalar )
        return 0;
    }
    else
    {
      if ( scalar > 1.0 || v44 < 0.0 )
        return 0;
      v30 = 1;
    }
    if ( !v30 )
    {
      v9 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
      v10 = rf_vector_add(a2, sum_result, v9);
      rf_vector_copy(&flt_1809174, copy_result, v10);
      v11 = rf_vector_subtract(&flt_1809174, v25, rhs);
      v12 = rf_vector_dot(v11, out_vector);
      v29 = v12 / v46;
      if ( v29 >= 0.0 && v29 <= 1.0 )
      {
        v13 = rf_vector_multiply_scalar(out_vector, v24, v29);
        v14 = rf_vector_add(rhs, v23, v13);
        rf_vector_copy(&flt_1809180, v22, v14);
      }
      else
      {
        v30 = 1;
      }
    }
  }
  if ( v30 )
  {
    v31 = v36;
    v37 = v40 * 2.0;
    v33 = v45 - a4 * a4;
    v34 = v37 * v37 - v36 * 4.0 * v33;
    if ( v34 <= 0.0 )
      return 0;
    v38 = rf_sqrt_float(v34);
    scalar = (v38 - v37) / (v31 * 2.0);
    v44 = (-v37 - v38) / (v31 * 2.0);
    if ( v44 < (double)scalar )
    {
      v39 = scalar;
      scalar = v44;
      v44 = v39;
    }
    if ( scalar < 0.0 || scalar > 1.0 || a8 <= (double)scalar )
      return 0;
    v15 = rf_vector_multiply_scalar(vector, v21, scalar);
    v16 = rf_vector_add(a2, v20, v15);
    rf_vector_copy(&flt_1809174, v19, v16);
    rf_vector_copy(&flt_1809180, v18, rhs);
  }
  *a7 = scalar;
  rf_vector_copy(destination, v17, &flt_1809180);
  return 1;
}

