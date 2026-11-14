// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412EB0 rf_dual_pose_aggregate_construct_invalid_timestamps
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Thiscall receiver,no stackargs. Constructs124-byte dual-array pose blocks at28 and152 via412F70;sets4-byte timestamps284 and308 toDWORD-1;calls no-op vector constructors312/332/356/372. Consequently persistent writes are empty array headers68/140/192/264 (three DWORDs each),BYTE80/BYTE204=0,andtimestamps284/308=-1. All other fields remain untouched;does not clear whole aggregate. Returns receiverEAX;no allocation for capacity0 or pointer validation.
char *__thiscall rf_dual_pose_aggregate_construct_invalid_timestamps(char *this)
{
  rf_dual_array_pose_block_construct_empty(this + 28);
  rf_dual_array_pose_block_construct_empty(this + 152);
  rf_timestamp4_construct_invalid((int *)this + 71);
  rf_timestamp4_construct_invalid((int *)this + 77);
  rf_vector3_default_construct_noop(this + 312);
  rf_vector3_default_construct_noop(this + 332);
  rf_vector3_default_construct_noop(this + 356);
  rf_vector3_default_construct_noop(this + 372);
  return this;
}

