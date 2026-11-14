// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052CD70 rf_geomod_candidate_pair_remove
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl16-byte pairnode void. Fields endpoints0/4,next8,prev12. Splice prev.next=node.next andnext.prev=node.prev, zero ownnext/prev, operator-delete node, THEN decrementglobalpaircount. Does not free/relink faceendpoints,validate sentinel/count/null or scanforidentity. Removing sentinel would corruptstate; caller suppliesrealnode. Survivorordering preserved.
void __cdecl rf_geomod_candidate_pair_remove(_DWORD *a1)
{
  *(_DWORD *)(a1[3] + 8) = a1[2];
  *(_DWORD *)(a1[2] + 12) = a1[3];
  a1[2] = 0;
  a1[3] = 0;
  operator delete(a1);
  --rf_geomod_candidate_pair_count;
}

