// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483BA0 rf_rfl_trigger_record_construct_string_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required receiver, no stack args, plain RET; explicitly returns original receiver in EAX. Constructs empty RFString0, invokes default vector at44,
// default matrix3 at56, default vector at92, then constructs empty RFString108. Verified vector/matrix constructors perform NO component writes: positions44/92 and matrix56 retain
// all prior bits, including uninitialized/NaN contents; no identity matrix or zero vectors are installed. All other scalar/padding fields remain supplied. No allocation, trigger
// registration, room lookup, prior ownership release or NULL guard. Shared one-state C++ unwind map6594EC cleans only completed first RFString0 if a later step throws; second
// string108 is last and has no own later unwind state. Fresh RFL triggers-section loader482D67 constructs this stack record before reading serialized entries. This is the RF loader
// record's partial member constructor, not a Concurrency class constructor.
void *__thiscall rf_rfl_trigger_record_construct_string_members(void *self)
{
  rf_string_construct_empty(self);
  rf_vector3_default_construct_noop((char *)self + 44);
  rf_matrix3_construct((char *)self + 56);
  rf_vector3_default_construct_noop((char *)self + 92);
  rf_string_construct_empty((_DWORD *)self + 27);
  return self;
}

