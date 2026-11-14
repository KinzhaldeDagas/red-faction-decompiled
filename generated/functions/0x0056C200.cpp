// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056C200 rf_ray_aabb_hit_point_candidate_planes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl(min,max,origin,direction,outPoint),returnsbyte. Per axis classifies origin inside closed bounds or chooses nearest outside min/max candidate plane. If origin inside all axes,copies origin to out and returns1 regardless direction. Otherwise candidate t=(plane-origin)/direction for outside axes with direction!=0;inside/zero-direction axes get-1. Chooses maximum candidate t,strict> updates so ties prefer X thenY thenZ;negative maximum returns0 without output. Otherwise writes axes inXYZ order;selected coordinate is candidate boundary,others=origin+t*direction and immediately checked inside inclusive bounds. A failed coordinate check leaves partial output. No upper t bound,so this is a forward RAY test,not
// finite segment clipping. No normal/normalization,finite or pointer guard; zero ray outside rejects.
unsigned __int8 __cdecl rf_ray_aabb_hit_point_candidate_planes(
        const float *min_bounds,
        const float *max_bounds,
        const float *origin,
        const float *direction,
        float *out_point)
{
  float copy_result[3]; // [esp+0h] [ebp-50h] BYREF
  const float *v7; // [esp+Ch] [ebp-44h]
  float v8[3]; // [esp+10h] [ebp-40h]
  const float *v9; // [esp+1Ch] [ebp-34h]
  _DWORD v10[3]; // [esp+20h] [ebp-30h]
  const float *v11; // [esp+2Ch] [ebp-24h]
  float *v12; // [esp+30h] [ebp-20h]
  float v13[3]; // [esp+34h] [ebp-1Ch]
  int v14; // [esp+40h] [ebp-10h]
  int i; // [esp+44h] [ebp-Ch]
  int v16; // [esp+48h] [ebp-8h]
  const float *v17; // [esp+4Ch] [ebp-4h]

  v11 = origin;
  v9 = direction;
  v7 = min_bounds;
  v17 = max_bounds;
  v12 = out_point;
  v14 = 1;
  for ( i = 0; i < 3; ++i )
  {
    if ( v7[i] <= (double)v11[i] )
    {
      if ( v17[i] >= (double)v11[i] )
      {
        v10[i] = 1;
      }
      else
      {
        v10[i] = 0;
        v8[i] = v17[i];
        v14 = 0;
      }
    }
    else
    {
      v10[i] = 0;
      v8[i] = v7[i];
      v14 = 0;
    }
  }
  if ( v14 )
  {
    rf_vector_copy(out_point, copy_result, origin);
    return 1;
  }
  else
  {
    for ( i = 0; i < 3; ++i )
    {
      if ( v10[i] || v9[i] == 0.0 )
        v13[i] = -1.0;
      else
        v13[i] = (v8[i] - v11[i]) / v9[i];
    }
    v16 = 0;
    for ( i = 1; i < 3; ++i )
    {
      if ( v13[i] > (double)v13[v16] )
        v16 = i;
    }
    if ( v13[v16] >= 0.0 )
    {
      for ( i = 0; i < 3; ++i )
      {
        if ( v16 == i )
        {
          v12[i] = v8[i];
        }
        else
        {
          v12[i] = v13[v16] * v9[i] + v11[i];
          if ( v7[i] > (double)v12[i] || v17[i] < (double)v12[i] )
            return 0;
        }
      }
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

