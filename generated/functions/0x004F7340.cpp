// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7340 rf_object_snapshot_common_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Construct raw short quaternion at common snapshot+26 and invoke no-op vector constructor at+44. Does not initialize stable ids, packed life/armor/position/velocity, flags, association slot or all60 bytes. Default quaternion is raw(0,0,0,1).
_WORD *__thiscall rf_object_snapshot_common_record_construct(_WORD *this)
{
  rf_short_quaternion_construct_0001(this + 13);
  rf_vector3_default_construct_noop(this + 22);
  return this;
}

