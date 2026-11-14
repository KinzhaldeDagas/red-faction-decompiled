// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059BAB0 rf_network_send_broadcast_unreliable
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments WORD port,payload,size. Builds local endpoint with IPv4 DWORD0xFFFFFFFF and port WORD,forwards to0x59BAF0. Padding bytes not initialized. Returns forwarded0/1 result; does not enable broadcast option or poll receive queues here.
int __cdecl rf_network_send_broadcast_unreliable(__int16 a1, void *a2, size_t a3)
{
  int v4; // [esp+8h] [ebp-8h] BYREF
  __int16 v5; // [esp+Ch] [ebp-4h]

  v5 = a1;
  v4 = -1;
  return rf_network_send_unreliable((int)&v4, a2, a3);
}

