// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B15B0 rf_tracker_initialize_static_endpoint_pool
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Noarg. Self-link free sentinel7B499C (next8/prev12) and active sentinel7B2628. For500 fixed16-byte nodes at7B2858, append each in address order to free tail by writes
// node.prev12,lasttail.next8,node.next8=sentinel,freeTail=node. Does not allocate, memset IP DWORD0/portWORD4/padding6, reset latest-total7B49AC or initialize packet/query flags.
// Reinitializing disconnects previously queued endpoints. Normal return EAX0 from final XOR; no runtime/initialized guard or failure path.
int rf_tracker_initialize_static_endpoint_pool()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_7B49A4 = &unk_7B499C;
  unk_7B49A8 = &unk_7B499C;
  result = 0;
  unk_7B2630 = &unk_7B2628;
  unk_7B2634 = &unk_7B2628;
  for ( i = 0; i < 500; ++i )
  {
    unk_7B2864[4 * i] = unk_7B49A8;
    unk_7B2860[4 * i] = (int)&unk_7B499C;
    *(_DWORD *)(unk_7B49A8 + 8) = (char *)&unk_7B2858 + 16 * i;
    unk_7B49A8 = (char *)&unk_7B2858 + 16 * i;
    result = 0;
  }
  return result;
}

