// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417370 rf_clutter_class_construct_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required receiver, no stack arguments, plain RET; normal EAX explicitly returns original receiver. In order constructs empty8-byte RFStrings
// at0,8,16,24,32; constructs raw DWORD-array header at40 with capacity0 (count/capacity/backing0); invokes no-op vector constructor at100; writes timestampDWORD112=-1; clears ONLY
// embedded-array countDWORD132; constructs108-byte-skin-record array header at200 with capacity0; then constructs DWORD-array header at212 with capacity0. Vector components100..111,
// scalar/padding/other embedded payload and every other field remain as supplied; not a whole-record memset or identity transform. No heap receiver allocation, clock query,
// parameter/range/NULL check, pre-existing storage release or success test here. Reusing a live receiver does not preserve/free old header/string ownership. Second chunk contains
// eight C++ unwind actions: completed skin-array200, count-only-array132(no-op destructor), DWORD-array40, then RFStrings32/24/16/8/0 in reverse construction order according to
// state; final212 array is not an own unwind entry because it is last. Constructor failure leaves delegate/previously written scalar state, with only mapped completed members
// cleaned. Original PE unwind map658290 verifies this chain; fresh startup629A00 passes this constructor and clutter destructor417460 for450 records of232-byte stride at667000;
// bytes224..231 also remain untouched. No Concurrency/NUMA behavior is present.
void *__thiscall rf_clutter_class_construct_members(void *self)
{
  rf_string_construct_empty(self);
  rf_string_construct_empty((_DWORD *)self + 2);
  rf_string_construct_empty((_DWORD *)self + 4);
  rf_string_construct_empty((_DWORD *)self + 6);
  rf_string_construct_empty((_DWORD *)self + 8);
  rf_dword_array_construct_capacity((char *)self + 40, 0);
  rf_vector3_default_construct_noop((char *)self + 100);
  rf_timestamp4_construct_invalid((int *)self + 28);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 33);
  rf_clutter_skin_array_construct_capacity((char *)self + 200, 0);
  rf_dword_array_construct_capacity((char *)self + 212, 0);
  return self;
}

