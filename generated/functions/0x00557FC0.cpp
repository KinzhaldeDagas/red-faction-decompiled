// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557FC0 rf_geomod_vertex_destroy_and_release_to_pool
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Releases vertex incident-face pointer array storage at32, then returns the vertex block to the global geomod vertex pool through raw pool release. Does not remove live references from faces, solid vertex arrays, or selection arrays; caller must unlink those first.
_DWORD *__cdecl rf_geomod_vertex_destroy_and_release_to_pool(int a1)
{
  rf_pointer_array_release_storage((void **)(a1 + 32));
  return rf_geomod_vertex_pool_release_raw(rf_geomod_vertex_pool_descriptor, (_DWORD *)a1);
}

