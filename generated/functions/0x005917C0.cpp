// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005917C0 rf_deadline_owner_construct_field36_only
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Thiscall receiver. Calls one-DWORD invalid-deadline constructor55F1B0 at receiver+36, which writes-1, then returns original receiver. No initialization of other receiver fields, allocation, vtable install or timer scheduling. Enclosing class role beyond this observed deadline field is not assigned here.
int *__thiscall rf_deadline_owner_construct_field36_only(int *this)
{
  rf_clock_deadline_construct_invalid(this + 9);
  return this;
}

