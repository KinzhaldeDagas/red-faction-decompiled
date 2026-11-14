// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C8F0 rf_network_flush_all_receive_queues
// UNREALRED VERIFIED [reliable-connections-20261028]: First drains channel0 through0x59BC00 until return<=0. Then for channels0..2,loops while range helper0x599570 says data,calling0x599480 into global0x1C0CF60 (nominal capacity610 ignored by wrapper). Does NOT poll OS socket or reset sequence counters/peer buffers. Can spin if oldest<=newest but matching queue record missing,because has-range remains true and failed pop does not advance. Return is incidental last helper result,not discarded count.
int rf_network_flush_all_receive_queues()
{
  int result; // eax
  _BYTE v1[680]; // [esp+0h] [ebp-2C0h] BYREF
  int v2; // [esp+2ACh] [ebp-14h]
  int i; // [esp+2B0h] [ebp-10h]
  int v4; // [esp+2B4h] [ebp-Ch]
  int v5[2]; // [esp+2B8h] [ebp-8h] BYREF

  v2 = 0;
  v4 = 0;
  do
    result = rf_network_receive_unreliable(v1, v5);
  while ( result > 0 );
  for ( i = 0; i < 3; ++i )
  {
    do
    {
      result = rf_network_receive_channel_has_sequence_range(i);
      v4 = result;
      v2 = 0;
      if ( result )
      {
        result = rf_network_receive_channel_pop(&unk_1C0CF60, 610, 0, v5, i);
        v2 = result;
      }
    }
    while ( v4 );
  }
  return result;
}

