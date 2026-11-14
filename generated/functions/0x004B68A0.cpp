// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B68A0 rf_server_apply_file_request_payload
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): Recovered [4B68A0,4B69B5). Native cdecl(filenamePayload,sourceEndpoint), TWO consumed stack args; no-argument decompiler
// inference would be false. Only runtime==1 AND authority==EXACT1. Scans unbounded NUL filename, retains LOW16 length, strncpy255 to local260-byte area then writes NUL at index254;
// computes unused wrapped16 cursor=length+1. Resolves source player by endpoint; if found unguardedly reads net4608+16 reliable handle and calls
// file_transfer_create_send_slot(handle,copiedName,global pathSelector88E430,0). No own payload length,null/net/handle-validity, filename/path traversal, transfer-result or
// sender-state gate. This pass records native behavior, without executing transfers or changing program bytes.
void __cdecl rf_server_apply_file_request_payload(const char *a1, void *a2)
{
  char Destination[260]; // [esp+14h] [ebp-110h] BYREF
  _DWORD *v3; // [esp+11Ch] [ebp-8h]
  int v4; // [esp+120h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v4 = 0;
    strncpy(Destination, a1, 0xFFu);
    Destination[254] = 0;
    v4 = (unsigned __int16)(v4 + strlen(a1) + 1);
    v3 = rf_player_find_by_network_endpoint((int)a2);
    if ( v3 )
      rf_file_transfer_create_send_slot(*(_DWORD *)(v3[1152] + 16), Destination, (void *)dword_88E430, 0);
  }
}

