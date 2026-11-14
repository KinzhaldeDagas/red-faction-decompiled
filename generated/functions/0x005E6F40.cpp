// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6F40 rf_receiver_get_dword0_5E6F40
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required ECX receiver,no stack arguments, plainRET. Load and return full raw DWORD[receiver+0] in EAX. No NULL/type/alignment/bounds/ownership
// validation, pointer resolution, comparison, mutation, call or normalization. This is a DWORD-value getter, not receiver+0 address calculation or automatic pointer dereference
// beyond that one load. No broader field meaning or RF-specific source origin proved; existing library classification retained.
int __thiscall rf_receiver_get_dword0_5E6F40(void *this)
{
  return *(_DWORD *)this;
}

