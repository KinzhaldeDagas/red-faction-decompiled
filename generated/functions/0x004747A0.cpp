// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004747A0 rf_item_destroy_members
// UNREALRED VERIFIED [item-pickups-20261028]: Destroys RF string at item+668 then calls rf_common_object_destroy_embedded_members(item). Does not itself unlink item, free allocation, or destroy a separate Replicator member.
void __thiscall rf_item_destroy_members(int this)
{
  rf_string_destroy_buffer((void *)(this + 668));
  rf_common_object_destroy_embedded_members(this);
}

