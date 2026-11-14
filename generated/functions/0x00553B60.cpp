// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553B60 rf_solid_triangulate_face_if_nonplanar
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Recomputes face geometry with finalize(face,0,0), ignoring its status, then classifies every corner position against that face plane. If coplanar classification2 count differs from total, fan-triangulates with null starting corner and selectDerived=0. Empty ring counts equal and is left alone. Positive/negative counts are computed but not used.
void __thiscall rf_solid_triangulate_face_if_nonplanar(void *this, _DWORD *a2)
{
  int v2; // [esp+0h] [ebp-20h]
  int v3; // [esp+4h] [ebp-1Ch]
  int i; // [esp+Ch] [ebp-14h]
  int v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+14h] [ebp-Ch]
  int v8; // [esp+18h] [ebp-8h]
  int v9; // [esp+1Ch] [ebp-4h]

  rf_geomod_face_finalize_geometry((int)a2, nullptr, 0);
  v6 = 0;
  v7 = 0;
  v9 = 0;
  v8 = 0;
  for ( i = a2[16]; i; i = v3 )
  {
    v2 = rf_geomod_point_classify_against_face_plane(*(const float **)i, a2);
    switch ( v2 )
    {
      case 1:
        ++v9;
        break;
      case 2:
        ++v7;
        break;
      case 3:
        ++v8;
        break;
    }
    ++v6;
    if ( *(_DWORD *)(i + 20) == a2[16] )
      v3 = 0;
    else
      v3 = *(_DWORD *)(i + 20);
  }
  if ( v7 != v6 )
    rf_solid_triangulate_face_fan_from_corner(this, a2, nullptr, 0);
}

