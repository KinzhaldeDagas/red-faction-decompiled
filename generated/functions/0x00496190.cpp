// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496190 rf_respawn_record68_construct_string_and_transform
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required receiver, no stack arguments, plain RET; explicitly returns original receiver in EAX. Constructs empty8-byte RFString0, then invokes no-op
// default vector constructor at12 and matrix3 constructor at24. Matrix constructor itself invokes no-op vector constructors on its three rows, so NONE of vector12..23/matrix24..59 is
// initialized to zero/identity or otherwise changed. DWORD8 and all other scalar/padding fields remain supplied. No allocation, lookup, resource registration, clock query, old
// ownership release or validation. Shared one-state PE unwind map6594EC cleans completed RFString0 if a later step throws; normal success disables it. Fresh startup62C3F0 supplies
// this constructor and string-only destructor4873C0 for32 respawn records at757BC8 with68-byte stride, so DWORD8 and tail60/64 remain untouched. RFString plus transform-shaped layout
// and fresh startup owner prove the inherited Concurrency/NUMA type is false; no further object-class identity is assumed.
void *__thiscall rf_respawn_record68_construct_string_and_transform(void *self)
{
  rf_string_construct_empty(self);
  rf_vector3_default_construct_noop((char *)self + 12);
  rf_matrix3_construct((char *)self + 24);
  return self;
}

