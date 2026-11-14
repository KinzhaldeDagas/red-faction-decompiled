// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052B900 rf_geomod_face_bounds_overlap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl faceA,faceB ALbool. Check B.max28/32/36 againstA.min16/20/24 thenB.min16/20/24 againstA.max28/32/36. Reject only ORDERED separation (< forfirst3,> forlast3); inclusive touching and unorderedNaN comparisons pass. Raw firstTESTAH5/JP andlastTESTAH41/JNZ confirmthis rather than pseudocode final<=. No epsilon expansion, plane/corner test,min<=max or finite check, mutation.
bool __cdecl rf_geomod_face_bounds_overlap(float *a1, float *a2)
{
  if ( a2[7] < (double)a1[4] )
    return 0;
  if ( a2[8] < (double)a1[5] )
    return 0;
  if ( a2[9] < (double)a1[6] )
    return 0;
  if ( a2[4] > (double)a1[7] )
    return 0;
  if ( a2[5] <= (double)a1[8] )
    return a2[6] <= (double)a1[9];
  return 0;
}

