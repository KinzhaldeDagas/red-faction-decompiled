// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464AD0 rf_browser_queue_all_server_queries
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Clear cancel,arm UIhold57DC1000. Fill query-order array6F52D0 with all favorite-flagged raw rows FIRST in raw-row order,then all other raw rows;independent of visible
// filter/sort indices. Zero failed6F52C0,succeeded6F52C4,completed6F5190. First k<signed simultaneous661F98 AND k<liveCount rows:OR queued40000000,reset retryBYTE100=0. Store
// nextcursor6F51B0=k,or-1 if k>=liveCount. No immediate send,allocation,index buffer check,clear of other queued/awaiting flags or reset of retry bytes on not-yet-activated rows.
// Scheduler's later queue activation does not reset their old retry bytes.
int rf_browser_queue_all_server_queries()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]
  int k; // [esp+4h] [ebp-4h]

  v1 = 0;
  unk_6F51A1 = 0;
  rf_clock_deadline_set_wrapped_offset(&dword_6F57DC, 1000);
  for ( i = 0; i < dword_6F51A8; ++i )
  {
    if ( *((int *)dword_6F52CC + 27 * i + 26) < 0 )
      *(_DWORD *)(unk_6F52D0 + 4 * v1++) = i;
  }
  for ( j = 0; j < dword_6F51A8; ++j )
  {
    if ( *((int *)dword_6F52CC + 27 * j + 26) >= 0 )
      *(_DWORD *)(unk_6F52D0 + 4 * v1++) = j;
  }
  unk_6F52C0 = 0;
  unk_6F52C4 = 0;
  unk_6F5190 = 0;
  for ( k = 0; k < *(int *)&dword_661F98 && k < dword_6F51A8; ++k )
  {
    *((_DWORD *)dword_6F52CC + 27 * *(_DWORD *)(unk_6F52D0 + 4 * k) + 26) |= 0x40000000u;
    *((_BYTE *)dword_6F52CC + 108 * *(_DWORD *)(unk_6F52D0 + 4 * k) + 100) = 0;
  }
  unk_6F51B0 = k;
  result = k;
  if ( k >= dword_6F51A8 )
    unk_6F51B0 = -1;
  return result;
}

