// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7300 rf_corpse_snapshot_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Construct common60 prefix,13 subrecords stride24 starting+72 through0x491340, and matrix+400. Does not zero entire532-byte corpse snapshot or establish packed animation-field validity.
char *__thiscall rf_corpse_snapshot_record_construct(char *this)
{
  rf_object_snapshot_common_record_construct((int)this);
  rf_vector_construct_no_unwind(this + 72, 0x18u, 13, rf_vector_prefix_construct_noop);
  rf_matrix3_construct(this + 400);
  return this;
}

