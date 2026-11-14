// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00533940 rf_geomod_face_contains_shared_vertex
// UNREALRED VERIFIED [ordered-boundary-20261028] Tests circular face-corner membership by shared VERTEX POINTER identity only. No position comparison, collinearity test or global-output deduplication. Used independently for each divided boundary before insertion of sorted finite records.
char __thiscall rf_geomod_face_contains_shared_vertex(_DWORD *this, int a2)
{
  int v3; // [esp+0h] [ebp-14h]
  int i; // [esp+10h] [ebp-4h]

  for ( i = *(this + 16); i; i = v3 )
  {
    if ( **(_DWORD **)(i + 20) == a2 )
      return 1;
    if ( *(_DWORD *)(i + 20) == *(this + 16) )
      v3 = 0;
    else
      v3 = *(_DWORD *)(i + 20);
  }
  return 0;
}

