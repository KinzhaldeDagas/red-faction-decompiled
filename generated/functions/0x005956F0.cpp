// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005956F0 rf_scene_point_definition180_destroy_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Only invokes verified no-op base destructor4580D0;no member writes or owned resource release. Used by180-byte point-definition array adapter5CE670. Does not free containing object.
void __thiscall rf_scene_point_definition180_destroy_noop(void *this)
{
  rf_shared_noop_destructor_4580d0();
}

