// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B2390 rf_record_zero_dword0_construct_5B2390
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required ECX storage,no stack arguments, plainRET. Write EXACT DWORD[receiver+0]=0 then explicitly reload ORIGINAL receiver into EAX. No other bytes
// initialized; no class/vtable, buffer ownership, allocation, NULL check or helper call. NULL receiver faults at store; EAX is receiver bits on normal completion despite nominal void
// declaration. Used as a value constructor callback by RF scene-definition loading, but this generic one-DWORD initialization does not uniquely identify source ownership; library
// flag retained. No prototype change inferred solely from incidental constructor EAX.
void __thiscall rf_record_zero_dword0_construct_5B2390(_DWORD *this)
{
  *this = 0;
}

