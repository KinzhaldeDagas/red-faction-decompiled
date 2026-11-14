// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051D8B0 rf_solid_triangulate_faces_with_off_plane_corners
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Recovered original51D8B0..51D9B0. Thiscall solid, no stack args, plainRET. Cache next solid face112 BEFORE possible mutation. For every circular face corner classify vertexXYZ against its own face plane via530740; count positive1,coplanar2,negative3 and total. If coplanarCount!=total, call existing fan triangulator(solid ECX,face,NULL,0). Does not require vertices on BOTH plane sides; any noncoplanar vertex triggers. Empty ring has equal0 counts and is not triangulated; plane classifier regards NaN distance coplanar2. No fresh plane calculation or polygon convexity test before classification. EAX residue ends at cached NULL next, normally0, not triangulation count. No baseline code xrefs.
int __thiscall rf_solid_triangulate_faces_with_off_plane_corners(void *solid)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-28h]
  int v3; // [esp+4h] [ebp-24h]
  int link; // [esp+Ch] [ebp-1Ch]
  int j; // [esp+10h] [ebp-18h]
  int v7; // [esp+14h] [ebp-14h]
  int v8; // [esp+18h] [ebp-10h]
  int v9; // [esp+1Ch] [ebp-Ch]
  int v10; // [esp+20h] [ebp-8h]
  _DWORD *i; // [esp+24h] [ebp-4h]

  result = rf_receiver_get_first_dword((char *)solid + 112);
  for ( i = (_DWORD *)result; i; i = (_DWORD *)link )
  {
    link = rf_solid_face_next_link((int)i);
    v7 = 0;
    v8 = 0;
    v10 = 0;
    v9 = 0;
    for ( j = i[16]; j; j = v3 )
    {
      v2 = rf_geomod_point_classify_against_face_plane(*(const float **)j, i);
      switch ( v2 )
      {
        case 1:
          ++v10;
          break;
        case 2:
          ++v8;
          break;
        case 3:
          ++v9;
          break;
      }
      ++v7;
      if ( *(_DWORD *)(j + 20) == i[16] )
        v3 = 0;
      else
        v3 = *(_DWORD *)(j + 20);
    }
    if ( v8 != v7 )
      rf_solid_triangulate_face_fan_from_corner(solid, i, nullptr, 0);
    result = link;
  }
  return result;
}

