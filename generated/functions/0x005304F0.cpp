// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005304F0 rf_collision_face_cache_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): No args void. Set cached countDWORD D5556C=0 and bypassBYTE D55570=0. Does not erase cached pointer array, reset collision query serial/diagnostics, detach faces, or prove every owner balanced its build/clear. Leaves entries beyond count untouched.
void rf_collision_face_cache_clear()
{
  rf_collision_cached_face_count = 0;
  rf_collision_cache_bypass = 0;
}

