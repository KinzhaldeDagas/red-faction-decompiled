// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7260 rf_decal_snapshot_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Call default vector at+0, matrix at+12 and default vector+48. No filename+60, packed flags+92 or scalar+96 initialization in body; no full100-byte clear.
char *__thiscall rf_decal_snapshot_record_construct(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_matrix3_construct(this + 12);
  rf_vector3_default_construct_noop(this + 48);
  return this;
}

