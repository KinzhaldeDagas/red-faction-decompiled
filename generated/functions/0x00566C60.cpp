// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566C60 rf_model_container_set_reference_mesh_materials
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): ECX model container plus material pointer word,RET4. Follows reference mesh pointer144 and writes its DWORD136,returns container. No allocation, old-table release, bounds/ownership check or restore bookkeeping.
_DWORD *__thiscall rf_model_container_set_reference_mesh_materials(_DWORD *this, int a2)
{
  *(_DWORD *)(*(this + 36) + 136) = a2;
  return this;
}

