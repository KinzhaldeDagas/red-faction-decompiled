// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056C450 rf_segment_intersects_aabb
// UNREALRED VERIFIED [trigger-geometry-20261020] Finite-segment/AABB predicate: either endpoint with outcode0 is admitted; a shared outside bit rejects. Otherwise test the start point boundary in X,Y,Z order, with float delta/numerator stores and closed comparisons on the other axes. This is not a center-only box check or an expanded entity capsule/AABB intersection.
bool __cdecl rf_segment_intersects_aabb(float *a1, float *a2, float *source, float *a4, float *destination)
{
  bool result; // al
  float v6[3]; // [esp+0h] [ebp-38h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-2Ch] BYREF
  float v8; // [esp+18h] [ebp-20h]
  float v9; // [esp+1Ch] [ebp-1Ch]
  float v10; // [esp+20h] [ebp-18h]
  float v11; // [esp+24h] [ebp-14h]
  float v12; // [esp+28h] [ebp-10h]
  float v13; // [esp+2Ch] [ebp-Ch]
  int v14; // [esp+30h] [ebp-8h]
  int v15; // [esp+34h] [ebp-4h]

  v15 = rf_aabb_point_outcode(a1, a2, source);
  if ( v15 )
  {
    v14 = rf_aabb_point_outcode(a1, a2, a4);
    if ( v14 )
    {
      if ( (v14 & v15) != 0 )
      {
        return 0;
      }
      else if ( (v15 & 3) != 0
             && ((v15 & 1) == 0 ? (*destination = *a1) : (*destination = *a2),
                 (v12 = *a4 - *source,
                  v13 = *destination - *source,
                  destination[1] = (a4[1] - source[1]) * v13 / v12 + source[1],
                  destination[2] = (a4[2] - source[2]) * v13 / v12 + source[2],
                  a2[1] >= (double)destination[1])
              && a1[1] <= (double)destination[1]
              && a2[2] >= (double)destination[2]
              && a1[2] <= (double)destination[2]) )
      {
        return 1;
      }
      else if ( (v15 & 0xC) != 0
             && ((v15 & 4) == 0 ? (destination[1] = a1[1]) : (destination[1] = a2[1]),
                 (v10 = a4[1] - source[1],
                  v11 = destination[1] - source[1],
                  *destination = (*a4 - *source) * v11 / v10 + *source,
                  destination[2] = (a4[2] - source[2]) * v11 / v10 + source[2],
                  *a2 >= (double)*destination)
              && *a1 <= (double)*destination
              && a2[2] >= (double)destination[2]
              && a1[2] <= (double)destination[2]) )
      {
        return 1;
      }
      else
      {
        result = false;
        if ( (v15 & 0x30) != 0 )
        {
          destination[2] = (v15 & 0x20) != 0 ? a2[2] : a1[2];
          v8 = a4[2] - source[2];
          v9 = destination[2] - source[2];
          *destination = (*a4 - *source) * v9 / v8 + *source;
          destination[1] = (a4[1] - source[1]) * v9 / v8 + source[1];
          if ( *a2 >= (double)*destination
            && *a1 <= (double)*destination
            && a2[1] >= (double)destination[1]
            && a1[1] <= (double)destination[1] )
          {
            return true;
          }
        }
      }
    }
    else
    {
      rf_vector_copy(destination, v6, a4);
      return 1;
    }
  }
  else
  {
    rf_vector_copy(destination, copy_result, source);
    return 1;
  }
  return result;
}

