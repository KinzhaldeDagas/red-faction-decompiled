// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B49D0 rf_replication_bind_server_id_to_local_handle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(server identifier,local handle). First writes table7B1538[serverId&FFFF]=localHandle, without -1 special-case, bounds or collision check. Then resolves local handle through
// rf_object_resolve_handle and UNCONDITIONALLY writes original FULL32-bit serverId to object DWORD+628; no null check if resolution fails. Does not check runtime/authority or clean
// previous mappings. Returns resolved object pointer in EAX; callers must supply a valid local handle. Table write precedes resolution and back-reference store.
int __cdecl rf_replication_bind_server_id_to_local_handle(int a1, int a2)
{
  int result; // eax

  unk_7B1538[(unsigned __int16)a1] = a2;
  result = rf_object_resolve_handle(a2);
  *(_DWORD *)(result + 628) = a1;
  return result;
}

