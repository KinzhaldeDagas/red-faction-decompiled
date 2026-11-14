// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBE60 rf_scene_material_binding_destruct_noop
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): No-argument-looking wrapper calls no-op0x4580D0. No writes,bitmap release,pool deletion or meaningful result;common base cleanup also does nothing.
void rf_scene_material_binding_destruct_noop()
{
  rf_shared_noop_destructor_4580d0();
}

