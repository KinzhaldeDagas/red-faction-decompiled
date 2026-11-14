// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F050 rf_multiplayer_remote_statistics_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Traverses circular player list head87C324 via nextDWORD0,terminating when next==current global head. Skips local player entirely. Nonlocal with net pointer4608
// nonnull calls4A6BD0(this=net+28,player),updating statistics windows/request timing. Separately,authority BYTE EXACT1 computes integer sample-average via4A6F50(net+28),stores
// netDWORD1452,and calls reliable_udp_seed_rtt_before_ten_samples(peer net16,value).
// Authority branch is OUTSIDE preceding netNULL guard; authority1 with nonlocal netNULL dereferencesNULL. Does not itself check runtime mode or peer!=-1. Next pointer read AFTER
// helpers,not snapshotted before calls. Return register incidental,not player count.
_DWORD *rf_multiplayer_remote_statistics_update()
{
  _DWORD *result; // eax
  _DWORD *v1; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = (_DWORD *)dword_87C324;
  for ( i = (_DWORD *)dword_87C324; i; i = v1 )
  {
    result = i;
    if ( i != (_DWORD *)rf_local_fpgun_player )
    {
      if ( i[1152] )
        result = (_DWORD *)rf_net_statistics_tick_and_probe((_DWORD *)(i[1152] + 28), (int)i);
      if ( rf_multiplayer_server_authority == 1 )
      {
        *(_DWORD *)(i[1152] + 1452) = rf_net_statistics_sample_mean((int *)(i[1152] + 28));
        result = (_DWORD *)rf_reliable_udp_seed_rtt_before_ten_samples(
                             *(_DWORD *)(i[1152] + 16),
                             *(_DWORD *)(i[1152] + 1452));
      }
    }
    if ( *i == dword_87C324 )
    {
      v1 = nullptr;
    }
    else
    {
      result = i;
      v1 = (_DWORD *)*i;
    }
  }
  return result;
}

