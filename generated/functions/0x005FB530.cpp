// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FB530 rf_scene_transform_range_definition_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 148-byte record:common scene-node initializer clears name0,name65,owner132;sets frames pointer144=NULL. Does NOT initialize start136,end140 or remaining name bytes. No allocation or default Unknown name here.
void __thiscall rf_scene_transform_range_definition_construct(_DWORD *this)
{
  rf_scene_node_clear_names_and_link(this);
  *(this + 36) = 0;
}

