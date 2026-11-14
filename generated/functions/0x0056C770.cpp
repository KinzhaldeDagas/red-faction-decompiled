// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056C770 rf_aabb_point_outcode
// UNREALRED VERIFIED [trigger-geometry-20261020] AABB point outcode: max-X1,min-X2,max-Y4,min-Y8,min-Z0x10,max-Z0x20. Equal boundaries are inside. Used by56C450; the Z high/low bits have opposite ordering to a naive uniform two-bits-per-axis loop.
int __cdecl rf_aabb_point_outcode(float *a1, float *a2, float *a3)
{
  int v4; // [esp+0h] [ebp-4h]

  v4 = 0;
  if ( *a2 >= (double)*a3 )
  {
    if ( *a1 > (double)*a3 )
      v4 = 2;
  }
  else
  {
    v4 = 1;
  }
  if ( a2[1] >= (double)a3[1] )
  {
    if ( a1[1] > (double)a3[1] )
      v4 |= 8u;
  }
  else
  {
    v4 |= 4u;
  }
  if ( a2[2] < (double)a3[2] )
    return v4 | 0x20;
  if ( a1[2] > (double)a3[2] )
    return v4 | 0x10;
  return v4;
}

