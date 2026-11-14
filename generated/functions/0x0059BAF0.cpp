// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059BAF0 rf_network_send_unreliable
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments endpoint,payload,size. Enabled flag0x1C0C3FC must be nonzero and endpoint port WORD+4 nonzero. Polls socket writability0x5994E0; nonpositive returns0. Sends through0x5995D0 flags0,channel0. Sender-1 or-2 returns0; any other result returns1 without checking exact size. Error diagnostics only formatted into unused local buffer. No payload size validation,queueing,retry or endpoint null check.
int __cdecl rf_network_send_unreliable(int a1, void *a2, size_t a3)
{
  int v4; // [esp+4h] [ebp-114h]
  char Buffer[260]; // [esp+8h] [ebp-110h] BYREF
  size_t Size; // [esp+110h] [ebp-8h]
  int v7; // [esp+114h] [ebp-4h]

  if ( !unk_1C0C3FC )
    return 0;
  if ( *(_WORD *)(a1 + 4) )
  {
    Size = a3;
    v7 = rf_network_socket_poll_writable();
    if ( v7 >= 0 )
    {
      if ( v7 )
      {
        v4 = rf_network_send_udp_channel_packet(a2, Size, 0, a1, 0);
        if ( v4 == -2 )
        {
          return 0;
        }
        else if ( v4 == -1 )
        {
          sprintf(Buffer, "Couldn't send data! (%d)\n", -1);
          return 0;
        }
        else
        {
          return 1;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      sprintf(Buffer, "Error on blocking select for write %d\n", v7);
      return 0;
    }
  }
  else
  {
    sprintf(Buffer, "Network ==> destination port %d invalid in psnet_send\n", *(unsigned __int16 *)(a1 + 4));
    return 0;
  }
}

