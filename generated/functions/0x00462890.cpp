// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462890 rf_join_pending_ipv4_set_from_endpoint
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl endpoint pointer,return same pointerEAX. Copy ONLY endpoint firstDWORD into pendingIPv4 global6F52DC;port/remaining bytes ignored. No
// NULL,length,byte-order,runtime check,timer arm or send. Complements previously verified pending IPv4 clear/query/match helpers462000/10/30;not a full endpoint snapshot.
int *__cdecl rf_join_pending_ipv4_set_from_endpoint(int *a1)
{
  unk_6F52DC = *a1;
  return a1;
}

