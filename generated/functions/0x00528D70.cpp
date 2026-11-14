// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528D70 rf_light_get_active_world_record_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Returns raw pointer from global active-world-light records[index],no bounds/count/NULL test. Previous decorated std::_Get_future_error_what name and constchar* return were false SDK recognition;actual opaque light record pointer used at fields80,etc by lightmap shadow processing. No exception,what-string lookup,allocation or active-list update. Prototype corrected to void*cdecl(int).
void *__cdecl rf_light_get_active_world_record_unchecked(int a1)
{
  return (void *)rf_light_active_world_records[a1];
}

