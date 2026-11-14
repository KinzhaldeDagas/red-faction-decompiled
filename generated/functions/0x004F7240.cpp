// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7240 rf_common_snapshot_record_construct_wrapper
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Call0x4F7340 on this and return pointer. Used by item/mover snapshot array construction; it does not initialize their specialized tails or zero entire80/96-byte records.
void *__thiscall rf_common_snapshot_record_construct_wrapper(void *this)
{
  rf_object_snapshot_common_record_construct((int)this);
  return this;
}

