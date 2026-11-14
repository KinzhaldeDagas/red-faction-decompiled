// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBAA0 rf_scene_named_reference_list_destruct_noop
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls no-op0x4580D0 only. Does not free shared8-byte reference entries,unlink or delete record;no meaningful return.
void __thiscall rf_scene_named_reference_list_destruct_noop(void *this)
{
  rf_shared_noop_destructor_4580d0();
}

