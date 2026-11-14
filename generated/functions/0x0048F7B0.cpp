// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F7B0 rf_multiplayer_send_local_display_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Builds opcode13 packet: BYTE0=13,payload lengthWORD1,network player idBYTE3 from localPlayer.net4608+20,name Cstring from localPlayer.RFString8 atoffset4.
// Computes full strlen then truncates uint16 n BEFORE memcpy;cursor/length arithmetic also16-bit. NUL index=uint16(n+4),total=uint16(n+5),header payload=uint16(n+2). No local
// name-length/localPlayer/netNULL guard or source mutation.
// Only mode EXACT1 AND authority EXACT1 broadcasts packet(buffer,total,0). All OTHER combinations delegate4A0070(localPlayer,buffer,total,0),whose own admission/queueing applies. No
// automatic mode1 requirement at builder entry,rename notification or response check. Return helper artifact; dead XOR/JNZ loops run once.
int rf_multiplayer_send_local_display_name()
{
  const char *v0; // eax
  unsigned __int16 v2; // [esp+0h] [ebp-228h]
  unsigned __int16 v3; // [esp+1Ch] [ebp-20Ch]
  unsigned __int8 Src; // [esp+20h] [ebp-208h] BYREF
  __int16 v5; // [esp+21h] [ebp-207h]
  char v6; // [esp+23h] [ebp-205h]
  int v7; // [esp+24h] [ebp-204h] BYREF

  Src = 13;
  v6 = *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20);
  v2 = strlen(rf_string_object_c_str_or_empty((const void *)(rf_local_fpgun_player + 8)));
  v0 = rf_string_object_c_str_or_empty((const void *)(rf_local_fpgun_player + 8));
  memcpy(&v7, v0, v2);
  *(&Src + (unsigned __int16)(v2 + 4)) = 0;
  v3 = v2 + 5;
  v5 = v2 + 2;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    return rf_server_broadcast_packet(&Src, v3, 0);
  else
    return rf_multiplayer_queue_reliable_packet(rf_local_fpgun_player, &Src, v3, 0);
}

