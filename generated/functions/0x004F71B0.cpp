// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F71B0 rf_entity_snapshot_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Call common60 subobject constructor0x4F7340, then default vectors at+364,+376,+400,+416,+472,+484,+496 and matrix+428. No inventory/history/AI flags/route-index/count reset or full536-byte clear.
char *__thiscall rf_entity_snapshot_record_construct(char *this)
{
  rf_object_snapshot_common_record_construct((int)this);
  rf_vector3_default_construct_noop(this + 364);
  rf_vector3_default_construct_noop(this + 376);
  rf_vector3_default_construct_noop(this + 400);
  rf_vector3_default_construct_noop(this + 416);
  rf_matrix3_construct(this + 428);
  rf_vector3_default_construct_noop(this + 472);
  rf_vector3_default_construct_noop(this + 484);
  rf_vector3_default_construct_noop(this + 496);
  return this;
}

