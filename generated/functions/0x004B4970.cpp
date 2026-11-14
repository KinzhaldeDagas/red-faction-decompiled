// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4970 rf_replication_server_id_to_local_handle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(server identifier). Full32-bit input EXACTLY-1 returns-1 immediately. Every other value indexes DWORD table7B1538 by input low16; high16 generation bits are ignored and there
// is no explicit table-size/local-handle validity check or runtime/authority gate. Other negative values are still indexed. Returns stored raw local handle with no object lookup or
// mutation. This mapping differs from direct object UID lookup used by packet43 receiver.
int __cdecl rf_replication_server_id_to_local_handle(int a1)
{
  if ( a1 == -1 )
    return -1;
  else
    return unk_7B1538[(unsigned __int16)a1];
}

