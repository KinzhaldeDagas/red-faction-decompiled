// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040E950 rf_route_edge_classify_point_clearance
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required point pointer,radius FLOAT,required lhs/rhs route-node pointers,output squared-distance FLOAT pointer). Full EAX
// returns0 inner region,1 expanded-only region,2 outside; output written ONLY on1. Builds FLOAT32 midpoint from round32(lhs+rhs) then multiplyFLOAT0.5 and copy. Builds
// orientation55BF00 from FLOAT32 lhs-rhs; delegated normalization is unchecked, no own zero-length/finite guard. Full box dimensions are X=round32(2*minimum(lhs FLOAT+28,rhs
// FLOAT+28)-2*radius), Y=minimum(lhs FLOAT+32,rhs FLOAT+32), Z=round32(Euclidean distance(lhs,rhs)); minimum selects RHS on equality OR UNORDERED. X doubling/subtraction stays x87
// until final FLOAT store. Calls56ADD0 with FOUR actual stack args(point,center,orientation,dimensions), cleanup16. Its56AD40 containment delegate rejects only ordered local<min or
// local>max; each individual UNORDERED bound comparison passes, so NaN is NOT automatically outside. If returned AL==EXACT1, returnEAX0 leaving output untouched. Otherwise replace X
// with round32(DOUBLE4.0*radius+PREVIOUSLY ROUNDED X), retaining Y/Z; this is native operation order, not algebraic unrounded2*(minRadius+radius). Repeat box predicate; AL!=EXACT1
// returnsEAX2 leaving output untouched. Expanded hit calls56CBA0(point,lhs,rhs,localClosest), explicitly discards its ST0 projection return, computes squared
// distance(point,localClosest) via5598C0, stores FLOAT32 to required output, returnsEAX1. No output/null guard, clamp of negative dimensions, source mutation or own NaN rejection.
// Box/normalization delegates may alter their shared scratch.
int __cdecl rf_route_edge_classify_point_clearance(float *point, float a2, float *lhs, float *rhs, float *a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  double v8; // st7
  float out_vector[3]; // [esp+8h] [ebp-78h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-6Ch] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-60h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-54h] BYREF
  float closest_point[3]; // [esp+38h] [ebp-48h] BYREF
  float orientation[9]; // [esp+44h] [ebp-3Ch] BYREF
  float full_dimensions[3]; // [esp+68h] [ebp-18h] BYREF
  float destination[3]; // [esp+74h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  v5 = rf_vector_add(lhs, sum_result, rhs);
  v6 = rf_vector_multiply_scalar(v5, scaled_result, 0.5);
  rf_vector_copy(destination, copy_result, v6);
  rf_matrix3_construct((char *)orientation);
  v7 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_orientation_matrix_from_normalized_direction(orientation, v7);
  rf_vector3_default_construct_noop(full_dimensions);
  v8 = rf_float_minimum_two_values(lhs[7], rhs[7]);
  full_dimensions[0] = v8 + v8 - (a2 + a2);
  full_dimensions[1] = rf_float_minimum_two_values(lhs[8], rhs[8]);
  full_dimensions[2] = rf_vector_distance(lhs, rhs);
  if ( rf_oriented_box_contains_point(point, destination, orientation, full_dimensions) )
    return 0;
  full_dimensions[0] = a2 * 4.0 + full_dimensions[0];
  if ( !rf_oriented_box_contains_point(point, destination, orientation, full_dimensions) )
    return 2;
  rf_vector3_default_construct_noop(closest_point);
  rf_vector3_closest_point_on_segment(point, lhs, rhs, closest_point);
  *a5 = rf_vector_distance_squared(point, closest_point);
  return 1;
}

