// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A20B0 rf_server_announce_joined_player_packet5
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(new player). Runtime mode1 and authority exactly1 only. Builds opcode5: player id BYTE3, net IPv4 DWORD4, port WORD8 (net+4 low16), net flags DWORD10, requested rate DWORD14
// from net+2492, player RFString+8 NUL-terminated name at18. With ordinary name length L,total=L+19,payload=L+16. Unbounded name scan, uint16 memcpy length/cursor and no
// packet-buffer bound check.
// Circular player list excludes new player AND local player. Other players require net connection handle+16!=-1, but no own net-null or state2 guard. Explicitly records outgoing
// opcode5 statistics at recipient net+28, then sends directly through reliable_udp_send_queued, bypassing aggregate buffer. Does not allocate player or wait for new peer handshake
// completion; return register is incidental.
int __cdecl rf_server_announce_joined_player_packet5(_DWORD *a1)
{
  int result; // eax
  const char *v2; // eax
  _DWORD *v3; // [esp+0h] [ebp-23Ch]
  unsigned __int16 v4; // [esp+4h] [ebp-238h]
  unsigned __int16 v5; // [esp+30h] [ebp-20Ch]
  char Src; // [esp+34h] [ebp-208h] BYREF
  __int16 Src_1; // [esp+35h] [ebp-207h]
  char Src_3; // [esp+37h] [ebp-205h]
  int v9; // [esp+38h] [ebp-204h]
  __int16 v10; // [esp+3Ch] [ebp-200h]
  int v11; // [esp+3Eh] [ebp-1FEh]
  int v12; // [esp+42h] [ebp-1FAh]
  __int16 v13; // [esp+46h] [ebp-1F6h] BYREF
  _DWORD *i; // [esp+238h] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    Src = 5;
    Src_3 = *(_BYTE *)(a1[1152] + 20);
    v9 = *(_DWORD *)a1[1152];
    v10 = *(_WORD *)(a1[1152] + 4);
    v11 = *(_DWORD *)(a1[1152] + 8);
    v12 = *(_DWORD *)(a1[1152] + 2492);
    v4 = strlen(rf_string_object_c_str_or_empty(a1 + 2));
    v2 = rf_string_object_c_str_or_empty(a1 + 2);
    memcpy(&v13, v2, v4);
    *(&Src + (unsigned __int16)(v4 + 18)) = 0;
    v5 = v4 + 19;
    Src_1 = v4 + 16;
    result = dword_87C324;
    for ( i = (_DWORD *)dword_87C324; i; i = v3 )
    {
      result = (int)i;
      if ( i != a1 && i != (_DWORD *)rf_local_fpgun_player )
      {
        result = i[1152];
        if ( *(_DWORD *)(result + 16) != -1 )
        {
          rf_net_statistics_record_packet((_DWORD *)(i[1152] + 28), v5, 1, 5);
          result = rf_reliable_udp_send_queued(*(_DWORD *)(i[1152] + 16), &Src, v5);
        }
      }
      if ( *i == dword_87C324 )
      {
        v3 = nullptr;
      }
      else
      {
        result = (int)i;
        v3 = (_DWORD *)*i;
      }
    }
  }
  return result;
}

