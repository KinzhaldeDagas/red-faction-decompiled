// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1660 rf_tracker_copy_bytes_forward_signed_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Cdecl(destination,source,signedCount). For signed index0..<count copy one BYTE source[index] ->destination[index], forward order. No NULL, capacity or overlap
// validation; destination>source overlap is not memmove-safe. Positive count returns EAX=count from final loop increment; count<=0 performs no access and leaves EAX unspecified (does
// not reliably return0). Used for unaligned wire DWORD/WORD copies.
int __cdecl rf_tracker_copy_bytes_forward_signed_count(int a1, int a2, int a3)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < a3; ++i )
  {
    *(_BYTE *)(i + a1) = *(_BYTE *)(i + a2);
    result = i + 1;
  }
  return result;
}

