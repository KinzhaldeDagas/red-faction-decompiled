// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1F70 rf_tracker_pop_endpoint_and_status
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Cdecl(outputEndpoint,outLatestTotal). If inactive return-3 BEFORE touching outputs. Active first set *outLatestTotal=-1. If timeout-latch7B4998 nonzero clear latch and
// return-2, even if endpoints remain queued (queue retained). If active list empty return0 while query7B2640 nonzero, else-1. Otherwise pop active HEAD: output host-order
// IPv4DWORD=ntohl(nodeDWORD0),portWORD at+4=ntohs(nodeWORD4); leave output+6 padding untouched. Unlink/zero links, append consumed node to free TAIL. Set *outLatestTotal=shared7B49AC
// from MOST RECENT parsed reply, not metadata retained per endpoint. Return1. No NULL output/initialized-list/capacity guard, receive polling, duplicate suppression or allocation.
// Accepted endpoint FIFO under valid list; explicit terminal statuses differ from transport errors.
int __cdecl rf_tracker_pop_endpoint_and_status(int a1, _DWORD *a2)
{
  _DWORD *v3; // [esp+0h] [ebp-4h]

  if ( !dword_7B4DB8 )
    return -3;
  *a2 = -1;
  if ( unk_7B4998 )
  {
    unk_7B4998 = 0;
    return -2;
  }
  else if ( dword_7B2630 == (_DWORD *)&unk_7B2628 )
  {
    return (unk_7B2640 != 0) - 1;
  }
  else
  {
    v3 = dword_7B2630;
    *(_DWORD *)a1 = ntohl(*dword_7B2630);
    *(_WORD *)(a1 + 4) = ntohs(*((_WORD *)v3 + 2));
    *(_DWORD *)(v3[3] + 8) = v3[2];
    *(_DWORD *)(v3[2] + 12) = v3[3];
    v3[2] = 0;
    v3[3] = 0;
    v3[3] = unk_7B49A8;
    v3[2] = &unk_7B499C;
    *(_DWORD *)(unk_7B49A8 + 8) = v3;
    unk_7B49A8 = v3;
    *a2 = dword_7B49AC;
    return 1;
  }
}

