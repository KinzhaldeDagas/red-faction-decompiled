// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048BE10 rf_aabb_overlap_strict_ordered
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Cdecl minA,maxA,minB,maxB ALnormalizedbool. Require ALL six ORDERED strict comparisons: maxB.xyz>minA.xyz and minB.xyz<maxA.xyz. Equality/touching on any axis and unorderedNaN reject. First three TEST AH41/JNZ, last three TEST AH5/JP confirm strictness; this differs from inclusive helpers used for other world/Boolean tests. No epsilon, min/max normalization, geometry mutation or pointer checks.
bool __cdecl rf_aabb_overlap_strict_ordered(float *a1, float *a2, float *a3, float *a4)
{
  return *a4 > (double)*a1
      && a4[1] > (double)a1[1]
      && a4[2] > (double)a1[2]
      && *a3 < (double)*a2
      && a3[1] < (double)a2[1]
      && a3[2] < (double)a2[2];
}

