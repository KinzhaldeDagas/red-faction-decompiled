// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569900 rf_segment_quad_hit_average_two_triangulations
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(segment6,A,B,C,D,outPoint,outEdgeFraction). Builds plane from triangle(A,B,C),tries569580; on failure tries(D,B,C). Separately tries(A,B,D),then(A,C,D). Requires one hit from EACH pair; these two triangulations share BC and AD diagonals respectively. Triangle query is two-sided and does NOT clamp line fractions. Final outPoint=start+delta*((tFirst+tSecond)/2). Fraction output=clamp01((dot(outPoint-A,C-A)/dot(C-A,C-A)+dot(outPoint-B,D-B)/dot(D-B,D-B))/2). This is averaging plane-hit fractions and edge projections,not exact bilinear surface solving. Earlier triangle probes may overwrite outPoint on eventual failure; final fraction only written after both pair hits. Shared vector scratch1809120/1809114 without
// locking; zero-length edges unchecked.
char __cdecl rf_segment_quad_hit_average_two_triangulations(
        float *a1,
        float *rhs,
        float *a3,
        float *a4,
        float *a5,
        float *lhs,
        float *a7)
{
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  double v14; // [esp+Ch] [ebp-D0h]
  double v15; // [esp+14h] [ebp-C8h]
  float scalar; // [esp+1Ch] [ebp-C0h]
  float v17[3]; // [esp+20h] [ebp-BCh] BYREF
  float v18[3]; // [esp+2Ch] [ebp-B0h] BYREF
  float v19[3]; // [esp+38h] [ebp-A4h] BYREF
  float v20[3]; // [esp+44h] [ebp-98h] BYREF
  float v21[3]; // [esp+50h] [ebp-8Ch] BYREF
  float v22[3]; // [esp+5Ch] [ebp-80h] BYREF
  float v23[3]; // [esp+68h] [ebp-74h] BYREF
  float out_vector[3]; // [esp+74h] [ebp-68h] BYREF
  float copy_result[3]; // [esp+80h] [ebp-5Ch] BYREF
  float sum_result[3]; // [esp+8Ch] [ebp-50h] BYREF
  float scaled_result[3]; // [esp+98h] [ebp-44h] BYREF
  float v28; // [esp+A4h] [ebp-38h] BYREF
  float v29; // [esp+A8h] [ebp-34h]
  float v30; // [esp+ACh] [ebp-30h] BYREF
  float v31; // [esp+B0h] [ebp-2Ch]
  float *v32; // [esp+B4h] [ebp-28h] BYREF
  float *v33; // [esp+B8h] [ebp-24h]
  float *v34; // [esp+BCh] [ebp-20h]
  float v35[4]; // [esp+C0h] [ebp-1Ch] BYREF
  int v36; // [esp+D8h] [ebp-4h]

  if ( (dword_180912C & 1) == 0 )
  {
    dword_180912C |= 1u;
    rf_vector3_default_construct_noop(unk_1809120);
    v36 = -1;
  }
  if ( (dword_180912C & 2) == 0 )
  {
    dword_180912C |= 2u;
    rf_vector3_default_construct_noop(unk_1809114);
    v36 = -1;
  }
  rf_vector_prefix_construct_noop(v35);
  v32 = rhs;
  v33 = a3;
  v34 = a4;
  rf_plane_set_from_three_world_points(v35, rhs, a3, a4);
  if ( !rf_segment_triangle_intersect_two_sided_plane(a1, (int *)&v32, v35, lhs, &v28) )
  {
    v32 = a5;
    rf_plane_set_from_three_world_points(v35, a5, v33, v34);
    if ( !rf_segment_triangle_intersect_two_sided_plane(a1, (int *)&v32, v35, lhs, &v28) )
      return 0;
  }
  v32 = rhs;
  v33 = a3;
  v34 = a5;
  rf_plane_set_from_three_world_points(v35, rhs, a3, a5);
  if ( !rf_segment_triangle_intersect_two_sided_plane(a1, (int *)&v32, v35, lhs, &v30) )
  {
    v33 = a4;
    rf_plane_set_from_three_world_points(v35, v32, a4, v34);
    if ( !rf_segment_triangle_intersect_two_sided_plane(a1, (int *)&v32, v35, lhs, &v30) )
      return 0;
  }
  scalar = (v28 + v30) / 2.0;
  v8 = rf_vector_multiply_scalar(a1 + 3, scaled_result, scalar);
  v9 = rf_vector_add(a1, sum_result, v8);
  rf_vector_copy(lhs, copy_result, v9);
  v10 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(unk_1809120, v23, v10);
  v11 = rf_vector_subtract(a4, v22, rhs);
  rf_vector_copy(unk_1809114, v21, v11);
  v15 = rf_vector_dot(unk_1809120, unk_1809114);
  v29 = v15 / rf_vector_dot(unk_1809114, unk_1809114);
  v12 = rf_vector_subtract(lhs, v20, a3);
  rf_vector_copy(unk_1809120, v19, v12);
  v13 = rf_vector_subtract(a5, v18, a3);
  rf_vector_copy(unk_1809114, v17, v13);
  v14 = rf_vector_dot(unk_1809120, unk_1809114);
  v31 = v14 / rf_vector_dot(unk_1809114, unk_1809114);
  *a7 = (v29 + v31) / 2.0;
  rf_float_clamp_in_place(a7, 0.0, 1.0);
  return 1;
}

