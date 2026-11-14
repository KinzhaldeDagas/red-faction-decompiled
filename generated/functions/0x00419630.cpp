// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419630 rf_physical_debris_construct_common_and_timer_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly and original startup call0x629A88): Thiscall physical-debris receiver, not glare. Calls common-object member constructor0x4129A0, then writes invalid timestamp -1 ONLY at+676 via0x55EF40; returns receiver. No other debris-specific initialization, including voice+684, flags+668, effect+672, counter+680, solid+660 or list links. Common constructor effectively initializes RFString+24 and physics-array header+388; vector/matrix components remain untouched. Original startup0x629A83 supplies physical-debris static sentinel and0x629A88 calls this function. Prior glare label corrected; actual glare constructor0x41CBB0 initializes common members and invokes no-write vector constructors+704/+724/+736.
char *__thiscall rf_physical_debris_construct_common_and_timer_members(char *this)
{
  rf_common_object_construct_members(this);
  rf_timestamp4_construct_invalid((int *)this + 169);
  return this;
}

