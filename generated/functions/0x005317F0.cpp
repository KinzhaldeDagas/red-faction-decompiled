// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005317F0 rf_geomod_face_hit_near_boundary
// UNREALRED VERIFIED [combat-polygon-boundary-20261104]: Iterates every ordered edge and calls531890, stores returned squared distance asfloat, and admits ambiguity only for strict distanceSquared<9.999999051046871e-9 (float(0.0001f*0.0001f), not float(1e-8)). Distance is to the supporting LINE for nondegenerate edges, not a clamped segment. This positive-hit retry predicate is separate from finite projected polygon containment.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, boundary x87 failure reproduction, fixed stack ABI, line projection, exact PE thresholds and original bytes): Corrected bogus __userpurge incomingST0 signature to THISCALL(faceECX,queryPointPointer stack),RET4,returns AL boolean. No input x87 value read in original instructions. Walks circular corner ringFace+64,nextCorner+20,constructs currentXYZ,nextXYZ,queryXYZ by-value stack triples for531890. Returns1 on first distanceSquared STRICTLY<PE double9.99999905104687e-09,else0 after ring (empty ringfalse). Supporting-line metric can accept beyond finite edge endpoints;degenerate edge uses endpoint fallback. Threshold equality and unordered distance rejected. Does not test query within face plane/polygon or mutate source geometry. Signature fixes eliminate persistent Hex-Rays failure observed in pre-lightmap baseline and
// current DB.
unsigned __int8 __thiscall rf_geomod_face_hit_near_boundary(const void *this, const float *a2)
{
  float v3[3]; // [esp-24h] [ebp-40h] BYREF
  float v4[3]; // [esp-18h] [ebp-34h] BYREF
  float v5[3]; // [esp-Ch] [ebp-28h] BYREF
  int v6; // [esp+0h] [ebp-1Ch]
  _DWORD *v7; // [esp+4h] [ebp-18h]
  float v8; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  v7 = this;
  for ( i = *((_DWORD *)this + 16); i; i = v6 )
  {
    rf_vector3_copy_return_destination(v5, (float *)a2);
    rf_vector3_copy_return_destination(v4, **(float ***)(i + 20));
    rf_vector3_copy_return_destination(v3, *(float **)i);
    v8 = rf_geomod_point_to_face_edge_distance_squared(v3[0], v3[1], v3[2], v4[0], v4[1], v4[2], v5[0], v5[1], v5[2]);
    if ( v8 < 0.000000009999999051046871 )
      return 1;
    if ( *(_DWORD *)(i + 20) == v7[16] )
      v6 = 0;
    else
      v6 = *(_DWORD *)(i + 20);
  }
  return 0;
}

