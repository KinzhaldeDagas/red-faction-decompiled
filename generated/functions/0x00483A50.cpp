// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483A50 rf_rfl_moving_group_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall temporary moving-group record constructor, returns receiver. Constructs three empty12-byte DWORD vectors at+4,+16,+28 by capacity0 helper, then four8-byte RFStrings
// at+56,+64,+72,+80 using EH vector iterator. Does not initialize id0,scalar/flag bytes40..55 or any later fields. Partial-construction unwind destroys already constructed vector
// backing; string iterator owns its own partial unwind. Not a complete memset and no contained pointed-object allocation.
char *__thiscall rf_rfl_moving_group_construct(char *this)
{
  rf_dword_array_construct_capacity(this + 4, 0);
  rf_dword_array_construct_capacity(this + 16, 0);
  rf_dword_array_construct_capacity(this + 28, 0);
  `eh vector constructor iterator'(
    this + 56,
    8u,
    4,
    (void (__thiscall *)(void *))rf_string_construct_empty,
    rf_string_destroy_buffer);
  return this;
}

