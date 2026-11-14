// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C8E30 rf_clip_polygon_against_planes
// UNREALRED VERIFIED [projected-shadow-receiver-20260903]: Generic convex-volume polygon clipper. It rejects input counts of 32 or more, ping-pongs the vertex list through each consecutive 16-byte plane via 0x005C8BD0, rejects as soon as fewer than three vertices survive, copies the final buffer when needed, and returns the surviving polygon count. Projected shadows call it with six planes.
int __cdecl rf_clip_polygon_against_planes(int a1, int a2, char *a3, int a4, int a5)
{
  float v6[3]; // [esp+0h] [ebp-1ACh] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-1A0h] BYREF
  int v8; // [esp+18h] [ebp-194h]
  char v9[388]; // [esp+1Ch] [ebp-190h] BYREF
  char *v10; // [esp+1A0h] [ebp-Ch]
  int i; // [esp+1A4h] [ebp-8h]
  char *v12; // [esp+1A8h] [ebp-4h]

  if ( a1 >= 32 )
    return 0;
  rf_vector_construct_no_unwind(v9, 0xCu, 32, rf_vector3_default_construct_noop);
  for ( i = 0; i < a1; ++i )
    rf_vector_copy((float *)&a3[12 * i], copy_result, (const float *)(a2 + 12 * i));
  v10 = a3;
  v12 = v9;
  for ( i = 0; i < a5; ++i )
  {
    a1 = rf_clip_polygon_against_plane(a1, (int)v10, (int)v12, (float *)(a4 + 16 * i));
    if ( a1 < 3 )
      return 0;
    v8 = (int)v10;
    v10 = v12;
    v12 = (char *)v8;
  }
  if ( v10 != a3 )
  {
    for ( i = 0; i < a1; ++i )
      rf_vector_copy((float *)&a3[12 * i], v6, (const float *)&v10[12 * i]);
  }
  return a1;
}

