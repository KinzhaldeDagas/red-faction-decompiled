// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2AA0 rf_model_container_get_reference_mesh_materials
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): ECX model container plus outCount,outMaterials,RET8. Follows reference mesh pointer144,writes mesh DWORD132 to outCount and DWORD136 to outMaterials,returns outMaterials. Both outputs written unconditionally. This verifies renderer5642A0 stack-output aliases at EBP-8+4*i and EBP-68h+4*i.
_DWORD *__thiscall rf_model_container_get_reference_mesh_materials(_DWORD *this, _DWORD *a2, _DWORD *a3)
{
  *a2 = *(_DWORD *)(*(this + 36) + 132);
  *a3 = *(_DWORD *)(*(this + 36) + 136);
  return a3;
}

