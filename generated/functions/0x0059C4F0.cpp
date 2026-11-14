// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C4F0 rf_reliable_udp_close_peer
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments peer-index pointer,notify flag. Rejects signed negative or>=40 with diagnostic sprintf result. For75 slots,frees receive pointers+900 and send pointers+0,clears them. Both branches clear receive sequence WORD array+1500; send sequence array+300 is not cleared individually (whole memset later if enabled). Builds opcode4 close header,sequence322,length0; byte1/timestamp uninitialized. Clears global client index0x664810 when matching. If network enabled,optionally sends10-byte close packet channel1,zeros1727-byte record,restores minimum delay+1723=750,sets caller index=-1,returns index pointer. If disabled,returns0 after frees but retains state/other fields and caller index. Does not close shared OS socket.
_DWORD *__cdecl rf_reliable_udp_close_peer(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  char Src[2]; // [esp+8h] [ebp-370h] BYREF
  __int16 v4; // [esp+Ah] [ebp-36Eh]
  __int16 v5; // [esp+Ch] [ebp-36Ch]
  char Buffer[256]; // [esp+270h] [ebp-108h] BYREF
  int i; // [esp+374h] [ebp-4h]

  if ( *a1 >= 0x28u )
    return (_DWORD *)sprintf(Buffer, "Invalid socket id passed to nw_NewCloseSocket() -- %d\n", *a1);
  sprintf(Buffer, "Closing socket %d\n", *a1);
  for ( i = 0; i < 75; ++i )
  {
    if ( *(_DWORD *)((char *)&unk_1BCA794 + 1727 * *a1 + 4 * i) )
    {
      operator delete(*(void **)((char *)&unk_1BCA794 + 1727 * *a1 + 4 * i));
      *(_DWORD *)((char *)&unk_1BCA794 + 1727 * *a1 + 4 * i) = 0;
      *(_WORD *)((char *)&unk_1BCA9EC + 1727 * *a1 + 2 * i) = 0;
    }
    if ( *(_DWORD *)((char *)&unk_1BCA410 + 1727 * *a1 + 4 * i) )
    {
      operator delete(*(void **)((char *)&unk_1BCA410 + 1727 * *a1 + 4 * i));
      *(_DWORD *)((char *)&unk_1BCA410 + 1727 * *a1 + 4 * i) = 0;
      *(_WORD *)((char *)&unk_1BCA9EC + 1727 * *a1 + 2 * i) = 0;
    }
  }
  Src[0] = 4;
  v4 = 322;
  result = nullptr;
  v5 = 0;
  if ( *a1 == dword_664810 )
    dword_664810 = -1;
  if ( unk_1C0C3FC )
  {
    if ( a2 )
      rf_network_send_udp_channel_packet(Src, 0xAu, 0, (int)&unk_1BCAA92 + 1727 * *a1, 1);
    memset((char *)&unk_1BCA410 + 1727 * *a1, 0, 0x6BFu);
    *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * *a1) = 0;
    *(_DWORD *)((char *)&unk_1BCAACB + 1727 * *a1) = 750;
    *a1 = -1;
    return a1;
  }
  return result;
}

