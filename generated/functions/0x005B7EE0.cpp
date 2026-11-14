// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B7EE0 rf_scene_definition_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall308-byte scene definition and flags byte,RET4. Always calls owning-pool destructor5CA7D0; if flags&1 then scalar operator delete(receiver). Returns original receiver bits even after free. No array cookie iteration,cache removal,refcount test,pointer clearing or retained-flag check here; parameter mask1 deletion decision is separate from scene flags304 mask2.
void *__thiscall rf_scene_definition_scalar_deleting_destructor(void *this, char a2)
{
  rf_scene_definition_destroy_owned_pools((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

