// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599480 rf_network_receive_channel_pop
// UNREALRED VERIFIED [network-queues-20261028]: Arguments destination,unused arg2,unused arg3,endpoint output,signed channel. Rejects channel<0 or>=3 with-1. Calls0x599840 for queue0x1BDB3D0+66828*channel,returns stored payload length on success,-1 if empty/missing sequence. Does not poll socket or enforce caller buffer capacity; ignored arguments do not limit copy size.
int __cdecl rf_network_receive_channel_pop(void *a1, int a2, int a3, _DWORD *a4, unsigned int a5)
{
  int v6; // [esp+4h] [ebp-8h] BYREF

  if ( a5 > 2 )
    return -1;
  if ( rf_network_receive_queue_pop((int)&unk_1BDB3D0[16707 * a5], a1, &v6, a4) )
    return v6;
  else
    return -1;
}

