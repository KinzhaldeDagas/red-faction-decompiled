// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00519210 rf_nav_node_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall node,flags low BYTE,RET4. Always calls4126C0 array-member destructor;flags&1 scalar-deletes node. Returns original pointer even if freed. No vector cookie handling,graph unlink or neighbor-object destruction. Existing type retained.
void **__thiscall rf_nav_node_scalar_deleting_destructor(void **this, char a2)
{
  rf_nav_node_destroy_array_members(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

