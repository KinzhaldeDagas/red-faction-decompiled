// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564D40 rf_model_handle_find_root_bone_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl handle forwards561F40. Tag2 searches source bone order and returns first signed-negative parent index; other tags/no root-1. Not generic scene root index or geometry average.
int __cdecl rf_model_handle_find_root_bone_adapter(_DWORD *a1)
{
  return sub_561F40(a1);
}

