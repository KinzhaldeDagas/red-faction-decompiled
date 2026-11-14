// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059BC30 rf_reliable_udp_receive_in_order
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments unsigned peer index,destination. FIRST services reliable peers,even for invalid index. Index>=40 returns-1; states other than1connected or5pending return0. Searches75 receive pointers at record+900 for nonnull pointer whose WORD sequence at+1500 matches expected WORD+1662. Copies stored DWORD length+1200 WITHOUT destination capacity,deletes buffer,clears pointer/sequence,increments expected WORD with wrap,returns stored length. No matching packet returns0. Does not reset stored length or require global network enabled. Record base0x1BCA410 stride1727.
int __cdecl rf_reliable_udp_receive_in_order(unsigned int a1, void *a2)
{
  char Buffer[260]; // [esp+4h] [ebp-110h] BYREF
  int i; // [esp+10Ch] [ebp-8h]
  char *v5; // [esp+110h] [ebp-4h]

  v5 = nullptr;
  rf_reliable_udp_service_peers();
  if ( a1 < 0x28 )
  {
    v5 = (char *)&unk_1BCA410 + 1727 * a1;
    if ( *(_DWORD *)(v5 + 1658) == 1 || *(_DWORD *)(v5 + 1658) == 5 )
    {
      for ( i = 0; i < 75; ++i )
      {
        if ( *(unsigned __int16 *)&v5[2 * i + 1500] == *((unsigned __int16 *)v5 + 831) && *(_DWORD *)&v5[4 * i + 900] )
        {
          memcpy(a2, *(const void **)&v5[4 * i + 900], *(_DWORD *)&v5[4 * i + 1200]);
          operator delete(*(void **)&v5[4 * i + 900]);
          *(_DWORD *)&v5[4 * i + 900] = 0;
          *(_WORD *)&v5[2 * i + 1500] = 0;
          ++*((_WORD *)v5 + 831);
          return *(_DWORD *)&v5[4 * i + 1200];
        }
      }
      return 0;
    }
    else
    {
      sprintf(Buffer, "Can't receive packet because it isn't connected in nw_ReceiveReliable(). socket = %d\n", a1);
      return 0;
    }
  }
  else
  {
    sprintf(Buffer, "Invalid socket id passed to nw_NewReceiveReliable() -- %d\n", a1);
    return -1;
  }
}

