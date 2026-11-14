// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0580 rf_server_item_sync_slot_find
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(object identifier). Only runtime mode EXACTLY1 and authority EXACTLY1 scans signed index0..<DWORD78C248 and compares the FULL identifier against DWORD78BF28[index]; returns
// FIRST matching index, otherwise-1. Guard rejection also returns-1. No game-mode check, fixed200 clamp, array-null guard or identifier translation. Read-only linear search used to
// omit already indexed items from peer bootstrap duplicate sends.
int __cdecl rf_server_item_sync_slot_find(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority != 1 )
    return -1;
  for ( i = 0; i < dword_78C248; ++i )
  {
    if ( a1 == dword_78BF28[i] )
      return i;
  }
  return -1;
}

