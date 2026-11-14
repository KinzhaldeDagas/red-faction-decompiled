// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059C7F0 rf_reliable_udp_get_peer_state
// UNREALRED VERIFIED [reliable-connections-20261028]: Unsigned peer index<40 returns DWORD state at0x1BCA410+1727*index+1658. Otherwise formats diagnostic and returns-1. Does not service network,check enabled flag or normalize states; no pointer return.
int __cdecl rf_reliable_udp_get_peer_state(unsigned int a1)
{
  char Buffer[260]; // [esp+0h] [ebp-108h] BYREF

  if ( a1 < 0x28 )
    return *(_DWORD *)((char *)&unk_1BCAA8A + 1727 * a1);
  sprintf(Buffer, "Invalid socket id passed to net_get_reliable_socket_status() -- %d\n", a1);
  return -1;
}

