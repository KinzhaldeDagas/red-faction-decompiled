// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437D80 rf_entity_has_model1410_and_runtime_flag200000
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): One cdecl entity pointer; canonical BOOL in AL only. NULL returns0; then require entity DWORD5136(+1410)
// nonzero and entity DWORD2064(+810) mask0x00200000 set. Returns1 only for both. Does not inspect model validity/type, class flags, draw outcome, liveness, player/attachment state or
// mutate anything. Upper EAX bits are incidental; this is not a model-pointer getter.
bool __cdecl rf_entity_has_model1410_and_runtime_flag200000(int a1)
{
  if ( !a1 )
    return 0;
  if ( *(_DWORD *)(a1 + 5136) )
    return (*(_DWORD *)(a1 + 2064) & 0x200000) != 0;
  return 0;
}

