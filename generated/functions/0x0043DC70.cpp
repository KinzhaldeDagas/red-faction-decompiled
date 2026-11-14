// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043DC70 rf_blood_surface_marks_advance_age
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Traverse active blood-mark circular ring and add rf_frame_delta_seconds to each age float+0. No clamping, maximum-age retirement, alpha fade or free-list mutation; old marks may instead be evicted by spawn or removed spatially.
int rf_blood_surface_marks_advance_age()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  result = dword_6E6254;
  for ( i = dword_6E6254; i; i = v1 )
  {
    result = i;
    *(float *)i = *(float *)i + rf_frame_delta_seconds;
    if ( *(_DWORD *)(i + 76) == dword_6E6254 )
    {
      v1 = 0;
    }
    else
    {
      result = i;
      v1 = *(_DWORD *)(i + 76);
    }
  }
  return result;
}

