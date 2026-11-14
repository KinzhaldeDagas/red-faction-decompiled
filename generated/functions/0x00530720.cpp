// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530720 rf_geomod_corner_release
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Cdecl raw corner pointer. Pass it and global pool to5363B0; return pool descriptor EAX, NOT corner or release status. Pushes record onto free chain and updates counts; does not destroy vertex, remove face incidence/ring membership, clear attributes or operator-delete spill storage. Caller must unlink first.
_DWORD *__cdecl rf_geomod_corner_release(_DWORD *a1)
{
  return rf_geomod_corner_pool_release_raw(rf_geomod_corner_pool_descriptor, a1);
}

