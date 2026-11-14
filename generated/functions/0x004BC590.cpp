// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC590 rf_object_store_room_pointer_only
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Thiscall receiver plus room DWORD,RET4. Only writes receiver DWORD0=supplied value and returns receiver pointer. Common-object callers copy another object room DWORD0 here. Unlike0x4BC210, does not cache position+4 or update audio/dirty state; no validation or allocation.
_DWORD *__thiscall rf_object_store_room_pointer_only(_DWORD *this, int a2)
{
  *this = a2;
  return this;
}

