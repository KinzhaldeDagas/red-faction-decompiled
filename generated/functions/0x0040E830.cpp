// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040E830 sub_40E830
// UNREALRED VERIFIED [combat-panic-20261104]: Route node containment returns0 inside,1 annulus,2 outside. Copies base→working; grounded workingY=baseY-height*.5+agentHeight*.5; storesfullsquaredDistance. Vertical interval inclusive baseY±height*.5. Horizontal squaredDistance<nodeRadius²-agentRadius² gives0; >=nodeRadius²+agentRadius² gives2; middle1. Native boundary is NOT (nodeRadius±agentRadius)^2 or a fixed arrival radius.
int __cdecl sub_40E830(float *a1, float a2, float a3, char a4, float *source)
{
  float copy_result[3]; // [esp+0h] [ebp-28h] BYREF
  float v7; // [esp+Ch] [ebp-1Ch]
  float v8[3]; // [esp+10h] [ebp-18h] BYREF
  float v9; // [esp+1Ch] [ebp-Ch]
  float v10; // [esp+20h] [ebp-8h]
  float v11; // [esp+24h] [ebp-4h]

  v11 = source[8] * 0.5;
  rf_vector_copy(source + 3, copy_result, source);
  if ( a4 )
    source[4] = source[1] - v11 + a3 * 0.5;
  source[14] = rf_vector_distance_squared(a1, source + 3);
  if ( a1[1] > source[1] + v11 )
    return 2;
  if ( a1[1] < source[1] - v11 )
    return 2;
  v10 = source[7] * source[7];
  v7 = a2 * a2;
  rf_vector3_copy_return_destination(v8, source);
  v8[1] = a1[1];
  v9 = rf_vector_distance_squared(v8, a1);
  if ( v9 < v10 - v7 )
    return 0;
  if ( v9 >= v10 + v7 )
    return 2;
  return 1;
}

