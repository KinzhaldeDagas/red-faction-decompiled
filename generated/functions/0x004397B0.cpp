// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004397B0 rf_entity_destroy_shared_jeep_model
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): No args. Only if global model DWORD681E80 nonNULL call566280 destroy adapter with that pointer, THEN clear
// global0. No explicit result: nonNULL path returns delegate EAX, NULL path leaves incoming EAX untouched (CMP memory does not load it). No object/model substitution, per-entity
// pointer cleanup or forced clear before destructor; exception leaves cache pointer retained. Global model is used by jeep-render path; no own reference-count or already-freed guard.
int rf_entity_destroy_shared_jeep_model()
{
  int result; // eax

  if ( unk_681E80 )
  {
    result = rf_model_handle_destroy_cdecl_adapter((_DWORD *)unk_681E80);
    unk_681E80 = 0;
  }
  return result;
}

