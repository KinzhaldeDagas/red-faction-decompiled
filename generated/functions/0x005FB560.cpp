// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FB560 rf_scene_transform_range_definition_destruct_noop
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls no-op0x4580D0 only;does not free shared frame pointer144,clear fields or delete record. No meaningful return.
void __thiscall rf_scene_transform_range_definition_destruct_noop(void *this)
{
  rf_shared_noop_destructor_4580d0();
}

