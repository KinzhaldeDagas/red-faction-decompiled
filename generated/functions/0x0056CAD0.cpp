// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056CAD0 rf_point_project_onto_unit_direction_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(point,line6,outClosest),floating ST0 result. Shared scratch180928C=point-line.start;distanceAlong=float(dot(scratch,line.direction));writes outClosest=line.start+line.direction*distanceAlong,returns stored float distanceAlong throughST0. No division by direction lengthSquared or clamping to0/1/segment length,so closest-point geometry assumes unit direction and allows either side of origin. Direction not normalized here; shared scratch/static flag1809298 without lock. No pointer/alias or finite validation.
double __cdecl rf_point_project_onto_unit_direction_line(float *lhs, float *rhs, float *destination)
{
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v7[3]; // [esp+8h] [ebp-4Ch] BYREF
  float sum_result[3]; // [esp+14h] [ebp-40h] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-28h] BYREF
  float out_vector[3]; // [esp+38h] [ebp-1Ch] BYREF
  float scalar; // [esp+44h] [ebp-10h]
  int v13; // [esp+50h] [ebp-4h]

  if ( (dword_1809298[0] & 1) == 0 )
  {
    dword_1809298[0] |= 1u;
    rf_vector3_default_construct_noop(unk_180928C);
    v13 = -1;
  }
  v3 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(unk_180928C, copy_result, v3);
  scalar = rf_vector_dot(unk_180928C, rhs + 3);
  v4 = rf_vector_multiply_scalar(rhs + 3, scaled_result, scalar);
  v5 = rf_vector_add(rhs, sum_result, v4);
  rf_vector_copy(destination, v7, v5);
  return scalar;
}

