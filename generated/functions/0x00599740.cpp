// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00599740 rf_network_receive_queue_append
// UNREALRED VERIFIED [system-progress-20261028]: Arguments queue base,payload,size,8-byte endpoint pointer. Queue has96 records stride696: signed sequence marker+0=-1 means unused,payload length+4,endpoint DWORDs+8/+12,payload+16. Finds first unused,memcpy payload without capacity check,stores length and endpoint. Writes sequence from queue+66816, copies to newest+66824,increments sequence,sets oldest+66820 if previously-1. Full queue silently drops without mutation. Does not dequeue,validate endpoint,size,sequence wrap or lock; return incidental pointer/integer differs by branch. Queue total66828 bytes,matching3 poller channel bases.
_DWORD *__cdecl rf_network_receive_queue_append(_DWORD *a1, void *Src, size_t Size, _DWORD *a4)
{
  _DWORD *result; // eax
  int v5; // edx
  int i; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  v7 = 0;
  for ( i = 0; i < 96; ++i )
  {
    if ( a1[174 * i] == -1 )
    {
      v7 = 1;
      break;
    }
    result = (_DWORD *)(i + 1);
  }
  if ( v7 )
  {
    memcpy(&a1[174 * i + 4], Src, Size);
    a1[174 * i + 1] = Size;
    v5 = 174 * i;
    a1[v5 + 2] = *a4;
    a1[v5 + 3] = a4[1];
    a1[174 * i] = a1[16704];
    a1[16706] = a1[16704];
    result = (_DWORD *)(a1[16704] + 1);
    a1[16704] = result;
    if ( a1[16705] == -1 )
    {
      a1[16705] = a1[16706];
      return a1;
    }
  }
  return result;
}

