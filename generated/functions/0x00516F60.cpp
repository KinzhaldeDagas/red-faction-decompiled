// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00516F60 rf_geomod_face_portal_side_vote
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Cdecl sourceFace,referencePlaneFace,caller pops8. Visit ordered circular corners64 through corner.next20; classify each vertex against reference face plane via native epsilon classifier. Count class1 front,class2 coplanar,class3 back,total; repeated vertex entries each vote. If coplanarCount!=total return normalized AL(frontCount>backCount), so ties arefalse and coplanar entries cast no majority vote. If ALL entries coplanar (also empty ring0==0),compute F32-stored dot(reference normal0,source normal0),return ORDERED dot>=0; equality true,negative or unorderedNaN false (TEST AH1/JNZ). Does not require shared edge,containment,intersecting polygons,closed volume or
// normalized normals; no writes.
bool __cdecl rf_geomod_face_portal_side_vote(int a1, float *a2)
{
  int v3; // [esp+0h] [ebp-24h]
  int v4; // [esp+4h] [ebp-20h]
  float v5; // [esp+8h] [ebp-1Ch]
  int i; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h]
  int v10; // [esp+1Ch] [ebp-8h]
  int v11; // [esp+20h] [ebp-4h]

  v7 = 0;
  v8 = 0;
  v11 = 0;
  v10 = 0;
  for ( i = *(_DWORD *)(a1 + 64); i; i = v4 )
  {
    v3 = rf_geomod_point_classify_against_face_plane(*(const float **)i, a2);
    switch ( v3 )
    {
      case 1:
        ++v11;
        break;
      case 2:
        ++v8;
        break;
      case 3:
        ++v10;
        break;
    }
    ++v7;
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a1 + 64) )
      v4 = 0;
    else
      v4 = *(_DWORD *)(i + 20);
  }
  if ( v8 != v7 )
    return v11 > v10;
  v5 = rf_vector_dot(a2, (float *)a1);
  return v5 >= 0.0;
}

