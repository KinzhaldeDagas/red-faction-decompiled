// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059BC00 rf_network_receive_unreliable
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments destination,endpoint output. Pops channel0 queue at0x1BDB3D0 through0x599840; returns payload length on success,0 when empty/missing sequence. Does not poll socket,check enabled flag or accept/enforce destination capacity. Zero-length datagram and no data share return0.
int __cdecl rf_network_receive_unreliable(void *a1, _DWORD *a2)
{
  int v2; // ecx
  int v4; // [esp+0h] [ebp-4h] BYREF

  v4 = v2;
  if ( rf_network_receive_queue_pop((int)unk_1BDB3D0, a1, &v4, a2) )
    return v4;
  else
    return 0;
}

