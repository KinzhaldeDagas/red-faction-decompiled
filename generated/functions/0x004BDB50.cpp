// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDB50 rf_trigger_runtime_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Thiscall type5 trigger receiver, returns receiver. Calls common member ctor, invalidates timestamps664,736,744,756,764 to-1, constructs empty RFString692/696, invokes NO-WRITE vec3 ctor712, constructs capacity0 DWORD array724/728/732. Effective common writes are RFString24/28 and physics array388/392/396. Does not zero remaining780-byte trigger layout, set trigger flags/class/links, or allocate array backing for capacity0. Object allocator type5 explicitly allocates0x30C and invokes this constructor.
char *__thiscall rf_trigger_runtime_construct_members(char *this)
{
  rf_common_object_construct_members(this);
  rf_timestamp4_construct_invalid((int *)this + 166);
  rf_string_construct_empty((_DWORD *)this + 173);
  rf_vector3_default_construct_noop(this + 712);
  rf_dword_array_construct_capacity(this + 724, 0);
  rf_timestamp4_construct_invalid((int *)this + 184);
  rf_timestamp4_construct_invalid((int *)this + 186);
  rf_timestamp4_construct_invalid((int *)this + 189);
  rf_timestamp4_construct_invalid((int *)this + 191);
  return this;
}

