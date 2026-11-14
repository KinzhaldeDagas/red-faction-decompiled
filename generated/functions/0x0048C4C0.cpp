// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048C4C0 rf_rcon_command_packet
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl source Cstring; identical native serializer/control logic to48C070 except packet opcode51(0x33). Requires mode EXACT1 and authority0. Full strlen truncated uint16 n; copies n
// bytes at packet+3,NUL at uint16(3+n),header payload length uint16(n+1),total uint16(n+4); delegates4A0070(local player,packet,total,0). No own sourceNULL/length guard; console
// wrapper separately accepts0..256 characters. Does not execute command, authenticate password, parse kick/level arguments or wait for reply. No stable Boolean return.
int __cdecl rf_rcon_command_packet(const char *Src)
{
  int result; // eax
  unsigned __int16 v2; // [esp+0h] [ebp-224h]
  unsigned __int8 v3; // [esp+1Ch] [ebp-208h] BYREF
  __int16 v4; // [esp+1Dh] [ebp-207h]
  char v5; // [esp+1Fh] [ebp-205h] BYREF

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v3 = 51;
    v2 = strlen(Src);
    memcpy(&v5, Src, v2);
    *(&v3 + (unsigned __int16)(v2 + 3)) = 0;
    v4 = v2 + 1;
    return rf_multiplayer_queue_reliable_packet(rf_local_fpgun_player, &v3, (unsigned __int16)(v2 + 4), 0);
  }
  return result;
}

