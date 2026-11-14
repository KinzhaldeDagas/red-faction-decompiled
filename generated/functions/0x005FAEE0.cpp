// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FAEE0 rf_scene_transform_track_definition_destruct_noop
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thincall destructor invokes no-op0x4580D0 only. No writes,frame-pool free,unlink or allocation deletion. Shared frame storage managed elsewhere;no meaningful result.
void __thiscall rf_scene_transform_track_definition_destruct_noop(void *this)
{
  rf_shared_noop_destructor_4580d0();
}

