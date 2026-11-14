// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBE30 rf_scene_material_binding_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Common scene-node initializer clears names andowner132;material indexDWORD136=-1. Returns this. Does not allocate material or set name Unknown.
int __thiscall rf_scene_material_binding_construct(int this)
{
  rf_scene_node_clear_names_and_link((_BYTE *)this);
  *(_DWORD *)(this + 136) = -1;
  return this;
}

