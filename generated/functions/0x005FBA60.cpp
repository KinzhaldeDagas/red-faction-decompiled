// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBA60 rf_scene_named_reference_list_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 144-byte record:common scene-node init,sets nameBYTE0=0 again,count136=0,pointer140=NULL. Does not initialize whole names or allocate list. Owner132 cleared bybase helper.
void __thiscall rf_scene_named_reference_list_construct(_DWORD *this)
{
  rf_scene_node_clear_names_and_link(this);
  *(_BYTE *)this = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
}

