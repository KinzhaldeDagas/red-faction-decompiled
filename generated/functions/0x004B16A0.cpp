// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B16A0 rf_tracker_append_endpoint_reply_records
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Cdecl payload, no length. First byte is SIGNED count:128..255 are negative and skip endpoint loop. Always copy raw four-byte value at payload+1 to shared
// latest-total7B49AC BEFORE count admission; no byte-order conversion for this value. Start cursor5; each positive-count record consumes raw IPv4DWORD and portWORD (6 bytes). Clear8
// local scratch bytes independent of data; no packet-bound check. If free sentinel has a node, unlink free HEAD, zero links8/12, copy endpoint DWORD0/WORD4 (padding6 remains old),
// append to ACTIVE TAIL7B2628. If pool empty still read/consume record, silently drop it; no eviction, allocation, duplicate suppression or error count. Preserves arrival order among
// accepted records. No initialized/source/sequence/runtime validation, reply completion flag or timer update in this function; caller handles those. Return EAX incidental, not number
// appended.
int __cdecl rf_tracker_append_endpoint_reply_records(char *a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-24h]
  __int16 v3; // [esp+6h] [ebp-1Eh] BYREF
  _DWORD v4[3]; // [esp+8h] [ebp-1Ch] BYREF
  int v5; // [esp+18h] [ebp-Ch]
  int i; // [esp+1Ch] [ebp-8h]
  char v7; // [esp+23h] [ebp-1h]

  v7 = *a1;
  rf_tracker_copy_bytes_forward_signed_count((int)&dword_7B49AC, (int)(a1 + 1), 4);
  result = dword_7B49AC;
  v5 = 5;
  for ( i = 0; i < 8; ++i )
  {
    result = i;
    *((_BYTE *)&v4[1] + i) = 0;
  }
  for ( i = 0; i < v7; ++i )
  {
    rf_tracker_copy_bytes_forward_signed_count((int)v4, (int)&a1[v5], 4);
    v5 += 4;
    result = rf_tracker_copy_bytes_forward_signed_count((int)&v3, (int)&a1[v5], 2);
    v5 += 2;
    if ( (_UNKNOWN *)unk_7B49A4 != &unk_7B499C )
    {
      v2 = unk_7B49A4;
      *(_DWORD *)(*(_DWORD *)(unk_7B49A4 + 12) + 8) = *(_DWORD *)(unk_7B49A4 + 8);
      *(_DWORD *)(*(_DWORD *)(v2 + 8) + 12) = *(_DWORD *)(v2 + 12);
      *(_DWORD *)(v2 + 8) = 0;
      *(_DWORD *)(v2 + 12) = 0;
      *(_DWORD *)v2 = v4[0];
      *(_WORD *)(v2 + 4) = v3;
      *(_DWORD *)(v2 + 12) = unk_7B2634;
      *(_DWORD *)(v2 + 8) = &unk_7B2628;
      *(_DWORD *)(unk_7B2634 + 8) = v2;
      result = v2;
      unk_7B2634 = v2;
    }
  }
  return result;
}

