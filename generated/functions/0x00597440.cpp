// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00597440 rf_file_transfer_dispatch_packet
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments packet pointer,peer. Reads opcode BYTE and wire-ID WORD. Opcode2 parses DWORD name length into fixed256-byte name buffer, total DWORD, CRC DWORD and calls0x5971D0. Opcode3 parses WORD chunk length into fixed604-byte buffer. Other opcodes use3-byte header. Non-offer lookup uses send direction for opcodes0/1, receive for3/4, then dispatches ACK,reject,data,finish respectively. Returns consumed bytes even if lookup fails; unknown opcode also returns3. No packet length parameter, bounds checking or name/chunk capacity validation in this routine.
int __cdecl rf_file_transfer_dispatch_packet(char *a1, int a2)
{
  size_t Size; // [esp+8h] [ebp-384h]
  char v4[256]; // [esp+Ch] [ebp-380h] BYREF
  int v5; // [esp+10Ch] [ebp-280h]
  __int16 v6; // [esp+110h] [ebp-27Ch]
  char v7; // [esp+117h] [ebp-275h]
  int peer_wire_id; // [esp+118h] [ebp-274h]
  unsigned __int16 v9; // [esp+11Ch] [ebp-270h]
  int v10; // [esp+120h] [ebp-26Ch]
  int v11; // [esp+124h] [ebp-268h]
  int v12; // [esp+128h] [ebp-264h]
  _BYTE Buffer[604]; // [esp+12Ch] [ebp-260h] BYREF

  v9 = 0;
  v12 = -1;
  v5 = 0;
  v10 = 0;
  v11 = 1;
  v7 = *a1;
  v10 = 1;
  v6 = *(_WORD *)(a1 + 1);
  v10 = 3;
  switch ( v7 )
  {
    case 2:
      Size = *(_DWORD *)&a1[v10];
      v10 += 4;
      memcpy(v4, &a1[v10], Size);
      v10 += Size;
      v4[Size] = 0;
      v12 = *(_DWORD *)&a1[v10];
      v10 += 4;
      v5 = *(_DWORD *)&a1[v10];
      v10 += 4;
      break;
    case 3:
      v9 = *(_WORD *)&a1[v10];
      v10 += 2;
      memcpy(Buffer, &a1[v10], v9);
      v10 += v9;
      v11 = 0;
      break;
    case 4:
      v11 = 0;
      break;
  }
  peer_wire_id = 0;
  if ( v7 != 2 )
  {
    peer_wire_id = 0;
    peer_wire_id = (int)rf_file_transfer_find_peer_wire_id(a2, v6, v11);
    if ( !peer_wire_id )
      return v10;
  }
  switch ( v7 )
  {
    case 0:
      rf_file_transfer_handle_ack((char *)peer_wire_id);
      break;
    case 1:
      rf_file_transfer_handle_reject(peer_wire_id);
      break;
    case 2:
      rf_file_transfer_accept_offer((int)Buffer, a2, v6, v4, v12, v5);
      break;
    case 3:
      rf_file_transfer_handle_data_chunk(peer_wire_id, Buffer, v9);
      break;
    case 4:
      rf_file_transfer_finish_received_file(peer_wire_id);
      break;
    default:
      return v10;
  }
  return v10;
}

