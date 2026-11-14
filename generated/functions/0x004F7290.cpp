// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7290 rf_projectile_snapshot_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Construct common60 prefix, default vector+76, matrix+88 and vector+140. Does not zero projectile definition, reference ids, mode byte, remaining scalar tail or full152-byte payload.
char *__thiscall rf_projectile_snapshot_record_construct(char *this)
{
  rf_object_snapshot_common_record_construct((int)this);
  rf_vector3_default_construct_noop(this + 76);
  rf_matrix3_construct(this + 88);
  rf_vector3_default_construct_noop(this + 140);
  return this;
}

