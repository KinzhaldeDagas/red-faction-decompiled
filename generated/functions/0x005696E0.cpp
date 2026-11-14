// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005696E0 rf_segment_parallelogram_intersect_coordinates
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(segment6,baseAndEdgeU6,edgeV3,outPoint,outVFraction). Constructs plane from base,base+U,base+V; queries two-sided line fraction and for finite ordinary fractions requires inclusive[0,1]. Writes point before subsequent rectangle-coordinate rejection. W=U-V*(dot(U,V)/dot(V,V)); alpha=dot(point-base,W)/dot(W,W),requires inclusive[0,1]. Residual=point-(base+alpha*U); rejects dot(residual,V)<=0,so V=0 boundary is OPEN. Then stores beta=length(residual)/length(V),accepts inclusive beta[0,1]. U boundaries and V=1 included. No degenerate-edge,normalization/zero-denominator or pointer guards; all scratch local. Fraction output is beta alongV,not line fraction.
unsigned __int8 __cdecl rf_segment_parallelogram_intersect_coordinates(
        const float *segment,
        const float *base_and_edge_u,
        const float *edge_v,
        float *out_point,
        float *out_v_fraction)
{
  float *v5; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *scalar; // [esp+4h] [ebp-BCh]
  double v14; // [esp+Ch] [ebp-B4h]
  double v15; // [esp+14h] [ebp-ACh]
  float v16; // [esp+1Ch] [ebp-A4h]
  double v17; // [esp+20h] [ebp-A0h]
  float v18[3]; // [esp+28h] [ebp-98h] BYREF
  float v19[3]; // [esp+34h] [ebp-8Ch] BYREF
  float v20[3]; // [esp+40h] [ebp-80h] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-74h] BYREF
  float v22[3]; // [esp+58h] [ebp-68h] BYREF
  float scaled_result[3]; // [esp+64h] [ebp-5Ch] BYREF
  float v24[3]; // [esp+70h] [ebp-50h] BYREF
  float sum_result[3]; // [esp+7Ch] [ebp-44h] BYREF
  float v26[3]; // [esp+88h] [ebp-38h] BYREF
  float out_vector[3]; // [esp+94h] [ebp-2Ch] BYREF
  float v28; // [esp+A0h] [ebp-20h] BYREF
  float rhs[3]; // [esp+A4h] [ebp-1Ch] BYREF
  float v30[4]; // [esp+B0h] [ebp-10h] BYREF

  scalar = rf_vector_add(base_and_edge_u, sum_result, edge_v);
  v5 = rf_vector_add(base_and_edge_u, v24, base_and_edge_u + 3);
  rf_plane_construct_from_three_world_points(v30, (float *)base_and_edge_u, v5, scalar);
  if ( !sub_56BDB0((int)segment, v30, &v28) || v28 < 0.0 || v28 > 1.0 )
    return 0;
  v7 = rf_vector_multiply_scalar(segment + 3, scaled_result, v28);
  v8 = rf_vector_add(segment, v22, v7);
  rf_vector_copy(out_point, copy_result, v8);
  v17 = rf_vector_dot((float *)base_and_edge_u + 3, (float *)edge_v);
  v16 = v17 / rf_vector_dot((float *)edge_v, (float *)edge_v);
  v9 = rf_vector_scale(v20, v16, (float *)edge_v);
  rf_vector_subtract(base_and_edge_u + 3, out_vector, v9);
  v10 = rf_vector_subtract(out_point, v19, base_and_edge_u);
  v15 = rf_vector_dot(v10, out_vector);
  v28 = v15 / rf_vector_dot(out_vector, out_vector);
  if ( v28 < 0.0 || v28 > 1.0 )
    return 0;
  v11 = rf_vector_multiply_scalar(base_and_edge_u + 3, v18, v28);
  rf_vector_add(base_and_edge_u, rhs, v11);
  rf_vector_subtract(out_point, v26, rhs);
  if ( rf_vector_dot(v26, (float *)edge_v) <= 0.0 )
    return 0;
  v14 = rf_vector3_length(v26);
  *out_v_fraction = v14 / rf_vector3_length((float *)edge_v);
  return *out_v_fraction >= 0.0 && *out_v_fraction <= 1.0;
}

