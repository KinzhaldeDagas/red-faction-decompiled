// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412F70 rf_dual_array_pose_block_construct_empty
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): Thiscall receiver,no stackargs. No-op vector constructors0/12 and matrix72. Initializes raw DWORD/pointer array headers at40 and112 with capacity0 (zeros count/capacity/base);writes BYTE52=0,then calls release-storage on BOTH newly empty arrays. Thus previous storage would already be overwritten if misused to reinitialize a live object;the release calls do not recover it. No other scalar/matrix/vector defaults. Returns receiverEAX;no owned pointee destruction or pointer guard. Original aggregate class identity unproven.
char *__thiscall rf_dual_array_pose_block_construct_empty(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 12);
  rf_dword_array_construct_capacity(this + 40, 0);
  rf_matrix3_construct(this + 72);
  rf_dword_array_construct_capacity(this + 112, 0);
  *(this + 52) = 0;
  rf_pointer_array_release_storage((void **)this + 10);
  rf_pointer_array_release_storage((void **)this + 28);
  return this;
}

