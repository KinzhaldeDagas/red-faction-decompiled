// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052BA10 rf_geomod_face_bounds_overlap_aabb
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl face,boxMinXYZ,boxMaxXYZ ALbool. Same6 component comparisons as52B900 using facebounds16/28 andexplicitboxvectors. Reject ORDERED max<faceMin ormin>faceMax; equality and unorderedNaN admitted. No face-plane/normal eligibility or geometricvertex test, min/max reorder or tolerance.
bool __cdecl rf_geomod_face_bounds_overlap_aabb(float *a1, float *a2, float *a3)
{
  if ( *a3 < (double)a1[4] )
    return 0;
  if ( a3[1] < (double)a1[5] )
    return 0;
  if ( a3[2] < (double)a1[6] )
    return 0;
  if ( *a2 > (double)a1[7] )
    return 0;
  if ( a2[1] <= (double)a1[8] )
    return a2[2] <= (double)a1[9];
  return 0;
}

