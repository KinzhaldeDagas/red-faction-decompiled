// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491940 rf_respawn_point_safety_score
// UNREALRED VERIFIED [respawn-decode]: Returns the minimum distance from a candidate respawn point to every other live player, starting from 1000000.
double __cdecl rf_respawn_point_safety_score(_DWORD *a1, float *a2, float *destination)
{
  _DWORD *v4; // [esp+0h] [ebp-20h]
  float copy_result[3]; // [esp+4h] [ebp-1Ch] BYREF
  float v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+14h] [ebp-Ch]
  float v8; // [esp+18h] [ebp-8h]
  _DWORD *i; // [esp+1Ch] [ebp-4h]

  v8 = 1000000.0;
  for ( i = (_DWORD *)dword_87C324; i; i = v4 )
  {
    if ( i != a1 )
    {
      v7 = rf_entity_resolve_handle(i[5]);
      if ( v7 )
      {
        v6 = rf_vector_distance_squared(a2, (const float *)(v7 + 60));
        if ( v8 > (double)v6 )
        {
          v8 = v6;
          if ( destination )
            rf_vector_copy(destination, copy_result, (const float *)(v7 + 60));
        }
      }
    }
    if ( *i == dword_87C324 )
      v4 = nullptr;
    else
      v4 = (_DWORD *)*i;
  }
  return v8;
}

