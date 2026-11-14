// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048C070 rf_rcon_request_password_packet
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl source Cstring. Only multiplayer mode BYTE EXACT1 and authority BYTE0 builds packet; other paths return incidental mode/previous EAX. Packet byte0=50(0x32),little-endian
// payload lengthWORD1,and NUL-terminated source starting3. Native computes full strlen then truncates to uint16 n BEFORE memcpy(packet+3,source,n). Cursor arithmetic also uint16: NUL
// written at(3+n)mod65536,total=(4+n)mod65536,payload length=(n+1)mod65536. Calls4A0070(local player,packet,total,0), which queues reliable data through player network state. No
// local sourceNULL guard, upper bound or source mutation; console caller enforces16 characters separately. Does not authenticate locally, check response or guarantee network send
// success. Return delegate artifact on build path; dead XOR/JNZ loops run once.
int __cdecl rf_rcon_request_password_packet(const char *Src)
{
  int result; // eax
  unsigned __int16 v2; // [esp+0h] [ebp-224h]
  unsigned __int8 v3; // [esp+1Ch] [ebp-208h] BYREF
  __int16 v4; // [esp+1Dh] [ebp-207h]
  char v5; // [esp+1Fh] [ebp-205h] BYREF

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v3 = 50;
    v2 = strlen(Src);
    memcpy(&v5, Src, v2);
    *(&v3 + (unsigned __int16)(v2 + 3)) = 0;
    v4 = v2 + 1;
    return rf_multiplayer_queue_reliable_packet(rf_local_fpgun_player, &v3, (unsigned __int16)(v2 + 4), 0);
  }
  return result;
}

