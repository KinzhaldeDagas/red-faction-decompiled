// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005346B0 rf_geomod_face_reverse_winding
// UNREALRED VERIFIED [geomod-lighting-20261027] Reverses the actual circular per-corner loop at face +0x40, then unconditionally calls 0x536080 at 0x534834. The face normal and plane scalar reverse with the corner order. This is coupled Boolean/source geometry orientation; a host raster winding adapter must preserve authoritative cavity-facing normals and projected corner UVs rather than reinterpret the source normal from a render backface.
float *__thiscall rf_geomod_face_reverse_winding(int this)
{
  int v2; // [esp+0h] [ebp-218h]
  int i; // [esp+8h] [ebp-210h]
  int v4; // [esp+Ch] [ebp-20Ch]
  _DWORD v5[129]; // [esp+10h] [ebp-208h]
  int j; // [esp+214h] [ebp-4h]

  v4 = 0;
  for ( i = *(_DWORD *)(this + 64); i; i = v2 )
  {
    v5[v4++] = i;
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(this + 64) )
      v2 = 0;
    else
      v2 = *(_DWORD *)(i + 20);
  }
  *(_DWORD *)(this + 64) = 0;
  for ( j = 0; j < v4; ++j )
  {
    if ( *(_DWORD *)(this + 64) )
    {
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 64) + 24) + 20) = v5[j];
      *(_DWORD *)(v5[j] + 24) = *(_DWORD *)(*(_DWORD *)(this + 64) + 24);
      *(_DWORD *)(*(_DWORD *)(this + 64) + 24) = v5[j];
      *(_DWORD *)(v5[j] + 20) = *(_DWORD *)(this + 64);
    }
    else
    {
      *(_DWORD *)(v5[j] + 20) = v5[j];
      *(_DWORD *)(v5[j] + 24) = v5[j];
    }
    *(_DWORD *)(this + 64) = v5[j];
  }
  return rf_geomod_face_plane_reverse((float *)this);
}

