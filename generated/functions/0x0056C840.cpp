// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056C840 rf_unit_direction_segment_sphere_hit_fraction
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(outPoint,outFraction,ray6,length,sphereCenter,radius),six stack args. Ray6=startXYZ+UNITdirectionXYZ; caller4D23C2 normalizes direction and supplies original length. Exact length0 returns0. w=center-start,q=float(dot(direction,w)); rejects q<=0 or radius<q-length BEFORE checking whether start is inside sphere,so an inside/boundary start with center behind/perpendicular can still reject. If float(w.w)<=float(radius*radius),copies start,stores fraction0,returns1 after those initial checks. Otherwise h2=radius²-(w.w-q²);h2<0 rejects,exact tangency h2==0 accepted. Writes outFraction=q-sqrt(h2) as DISTANCE,then rejects if distance>length;failure leaves that unnormalized distance but outPoint unchanged. Success
// writes start+direction*distance and divides outFraction bylength. Radius/negative-length/finite/normalization validity not checked; all vector scratch local.
char __cdecl rf_unit_direction_segment_sphere_hit_fraction(
        float *destination,
        float *a2,
        float *rhs,
        float a4,
        float *lhs,
        float a6)
{
  float *v7; // eax
  float *v8; // eax
  float v9[3]; // [esp+4h] [ebp-4Ch] BYREF
  float sum_result[3]; // [esp+10h] [ebp-40h] BYREF
  float scaled_result[3]; // [esp+1Ch] [ebp-34h] BYREF
  float copy_result[3]; // [esp+28h] [ebp-28h] BYREF
  float v13; // [esp+34h] [ebp-1Ch]
  float v14; // [esp+38h] [ebp-18h]
  float out_vector[3]; // [esp+3Ch] [ebp-14h] BYREF
  float v16; // [esp+48h] [ebp-8h]
  float v17; // [esp+4Ch] [ebp-4h]

  if ( a4 == 0.0 )
    return 0;
  rf_vector_subtract(lhs, out_vector, rhs);
  v13 = rf_vector_dot(rhs + 3, out_vector);
  if ( v13 <= 0.0 || a6 < v13 - a4 )
    return 0;
  v16 = rf_vector_dot(out_vector, out_vector);
  v17 = a6 * a6;
  if ( v17 < (double)v16 )
  {
    v14 = v17 - (v16 - v13 * v13);
    if ( v14 >= 0.0 )
    {
      *a2 = v13 - rf_sqrt_float(v14);
      if ( a4 >= (double)*a2 )
      {
        v7 = rf_vector_multiply_scalar(rhs + 3, scaled_result, *a2);
        v8 = rf_vector_add(rhs, sum_result, v7);
        rf_vector_copy(destination, v9, v8);
        *a2 = *a2 / a4;
        return 1;
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
    rf_vector_copy(destination, copy_result, rhs);
    *a2 = 0.0;
    return 1;
  }
}

