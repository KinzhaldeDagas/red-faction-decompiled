// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6E70 rf_record_clear_dwords12_and16
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required writable receiver, no stack arguments, plain RET. Saves ECX, loads receiver into EAX, stores DWORD+12=0, then stores DWORD+16=0 in that
// order. No other object/global writes, free/release, lock/critical-region API, callbacks, validation, pointer dereference through those field values or return-status normalization.
// Declared void; incidental full EAX retains receiver bits. Native xref snapshot has no callers, so these two fields' meaning/ownership and any application-specific class remain
// unproved. Generic void-pointer receiver removes the unsupported SDK ContextBase type; library classification is retained because simple field clearing alone cannot establish game
// ownership.
void __thiscall rf_record_clear_dwords12_and16(void *self)
{
  *((_DWORD *)self + 3) = 0;
  *((_DWORD *)self + 4) = 0;
}

