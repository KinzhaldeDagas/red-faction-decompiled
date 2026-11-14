// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486DE0 rf_receiver_get_first_dword
// UNREALRED VERIFIED [trigger-airlock-20261022] Generic receiver DWORD0 getter; cached-room-pointer interpretation is specific to the following504B30 context. At504B30 this reads global player room and linked mover room; do not reinterpret as activator position lookup or portal-array count.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall receiver ECX, no stack arguments. Loads exactly DWORD[receiver+0] into fullEAX thenRET; no null/type/range validation or mutation. Generic rawDWORD
// getter, retaining library flag. Previous504B30 cached-room-pointer interpretation is caller-specific; current frontend/Extras inline arrays use this SAME native getter as live
// count. Do not assign universal room-pointer or universal array-count semantics to the method. Receiver/source context owns the meaning.
int __thiscall rf_receiver_get_first_dword(void *this)
{
  return *(_DWORD *)this;
}

