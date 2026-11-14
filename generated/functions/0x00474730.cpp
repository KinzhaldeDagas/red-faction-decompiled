// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474730 rf_item_construct_members
// UNREALRED VERIFIED [item-pickups-20261028]: Calls common-object constructor0x4129A0(this), RF-string constructor at this+668, and Replicator constructor at this+688. Returns this. Does not explicitly initialize definition pointer,index,quantity,flags or rotation scalar in this body; spawn routine handles those.
int __thiscall rf_item_construct_members(int this)
{
  rf_common_object_construct_members((char *)this);
  rf_string_construct_empty((_DWORD *)(this + 668));
  rf_timestamp4_construct_invalid((int *)(this + 688));
  return this;
}

