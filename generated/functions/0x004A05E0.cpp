// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A05E0 rf_multiplayer_send_item_apply_packet40
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(optional peer,item server id,entity server id,index,valueA,valueB). Builds fixed23-byte opcode40 packet: header payload WORD1=20; five raw DWORDs at3/7/11/15/19 in argument
// order. No own runtime/authority guard or identifier translation. Nonnull peer delegates reliable queue(peer,packet,23,0) without an explicit active-state check in this sender. Null
// peer manually traverses circular player list, UNCONDITIONALLY excludes local player, requires net DWORD+4608 nonnull and net state DWORD+12 EXACTLY2, then queues with
// require-active0. This broadcast policy differs from common server_broadcast_packet.
// Matched receiver interprets index/valueA/valueB as weapon-index-dependent entity state updates after pickup dispatch. Sender performs no pickup, object deletion or state mutation
// itself. Declared __int16 return is incidental AX from header/delegate/traversal, not acknowledgement; preserve existing ABI.
__int16 __cdecl rf_multiplayer_send_item_apply_packet40(int a1, int a2, int a3, int a4, int a5, int a6)
{
  _DWORD *v6; // eax
  _DWORD *v8; // [esp+0h] [ebp-22Ch]
  _DWORD *i; // [esp+4h] [ebp-228h]
  unsigned __int8 Src[7]; // [esp+24h] [ebp-208h] BYREF
  int v11; // [esp+2Bh] [ebp-201h]
  int v12; // [esp+2Fh] [ebp-1FDh]
  int v13; // [esp+33h] [ebp-1F9h]
  int v14; // [esp+37h] [ebp-1F5h]

  Src[0] = 40;
  *(_DWORD *)&Src[3] = a2;
  v11 = a3;
  v12 = a4;
  v13 = a5;
  v14 = a6;
  LOWORD(v6) = 20;
  *(_WORD *)&Src[1] = 20;
  if ( a1 )
  {
    LOWORD(v6) = rf_multiplayer_queue_reliable_packet(a1, Src, 0x17u, 0);
  }
  else
  {
    for ( i = (_DWORD *)dword_87C324; i; i = v8 )
    {
      if ( i != (_DWORD *)rf_local_fpgun_player && i[1152] && *(_DWORD *)(i[1152] + 12) == 2 )
        rf_multiplayer_queue_reliable_packet((int)i, Src, 0x17u, 0);
      LOWORD(v6) = (_WORD)i;
      if ( *i == dword_87C324 )
      {
        v8 = nullptr;
      }
      else
      {
        v6 = (_DWORD *)*i;
        v8 = (_DWORD *)*i;
      }
    }
  }
  return (__int16)v6;
}

