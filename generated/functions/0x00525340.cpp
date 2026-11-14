// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525340 rf_face_update_flag8_decal_base_uvs
// UNREALRED VERIFIED [decal-face-links-20261028]: Collects at most25 same-face polygon pointers whose parent decal flags contain8 via0x525920. For each, walks ORIGINAL face vertex loop+64 and writes temporary UV pairs at polygon+8*i: U=-signed_distance(parent plane+172,vertex)/parent width+48; V=-distance(plane+92)/height+52. No UV clamp/tile shift or lightmap update. No vertex-count<=25 or zero-dimension guard; extra context argument passed to collector is unused there. Returns polygon count processed.
int __cdecl rf_face_update_flag8_decal_base_uvs(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-84h]
  float *v4; // [esp+4h] [ebp-80h]
  int v5; // [esp+8h] [ebp-7Ch]
  int j; // [esp+Ch] [ebp-78h]
  int v7; // [esp+10h] [ebp-74h]
  int i; // [esp+14h] [ebp-70h]
  int v9; // [esp+18h] [ebp-6Ch] BYREF
  _DWORD v10[26]; // [esp+1Ch] [ebp-68h] BYREF

  v9 = 25;
  rf_world_decal_collect_face_polygons_by_flags(a2, a1, (int)v10, &v9, 8, 0);
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= v9 )
      break;
    v5 = v10[i];
    v4 = *(float **)(v5 + 1316);
    v7 = 0;
    for ( j = *(_DWORD *)(a2 + 64); j; j = v3 )
    {
      *(float *)(v5 + 8 * v7) = -rf_plane_point_signed_distance(v4 + 43, (float *)*(_DWORD *)j) / v4[12];
      *(float *)(v5 + 8 * v7++ + 4) = -rf_plane_point_signed_distance(v4 + 23, (float *)*(_DWORD *)j) / v4[13];
      if ( *(_DWORD *)(j + 20) == *(_DWORD *)(a2 + 64) )
        v3 = 0;
      else
        v3 = *(_DWORD *)(j + 20);
    }
  }
  return result;
}

