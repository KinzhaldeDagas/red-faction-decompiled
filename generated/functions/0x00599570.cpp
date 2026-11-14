// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599570 rf_network_receive_channel_has_sequence_range
// UNREALRED VERIFIED [network-queues-20261028]: Signed channel0..2 only,otherwise-1. Returns1 if queue oldest+66820!=-1 AND SIGNED oldest<=newest+66824,else0. Does not scan96 records to prove oldest record exists,so may disagree with pop on missing sequence or wrap. Does not poll socket or mutate queue.
int __cdecl rf_network_receive_channel_has_sequence_range(unsigned int a1)
{
  if ( a1 > 2 )
    return -1;
  return unk_1BDB3D0[16707 * a1 + 16705] != -1 && unk_1BDB3D0[16707 * a1 + 16705] <= unk_1BDB3D0[16707 * a1 + 16706];
}

