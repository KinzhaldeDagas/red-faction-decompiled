// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A26C0 rf_server_send_join_accept_packet3
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(destination endpoint,new player), runtime1/authority exactly1. Opcode3 contains level string6FC31C+NUL, cached CRC DWORD6FC3A8, raw game mode DWORD704ED4, game flags DWORD,
// shared seconds clock float6FC428, float704EE4, assigned id BYTE and player net flags DWORD+8. Normal level name length L gives total=L+29,payload=L+26. Name scan/memcpy lengths and
// cursor are uint16 without buffer bound checks; floats serialize through x87 single-precision temporaries.
// If CRC cache is zero computes rf_vfile_raw_crc32_or_zero(levelName) before serialization. Zero CRC/failure leaves sentinel zero, causing another computation next call. Direct
// unreliable send to endpoint, no own player/net-null validation or reliable connection creation. Only CRC cache is modified here.
int __cdecl rf_server_send_join_accept_packet3(int a1, int a2)
{
  int result; // eax
  const char *v3; // eax
  char *v4; // eax
  unsigned __int16 v5; // [esp+0h] [ebp-240h]
  _BYTE v6[516]; // [esp+38h] [ebp-208h] BYREF

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v6[0] = 3;
    v5 = strlen(rf_string_object_c_str_or_empty(unk_6FC31C));
    v3 = rf_string_object_c_str_or_empty(unk_6FC31C);
    memcpy(&v6[3], v3, v5);
    v6[(unsigned __int16)(v5 + 3)] = 0;
    if ( !dword_6FC3A8 )
    {
      v4 = (char *)rf_string_object_c_str_or_empty(unk_6FC31C);
      dword_6FC3A8 = rf_vfile_raw_crc32_or_zero(v4);
    }
    *(_DWORD *)&v6[(unsigned __int16)(v5 + 4)] = dword_6FC3A8;
    *(_DWORD *)&v6[(unsigned __int16)(v5 + 8)] = unk_704ED4;
    *(_DWORD *)&v6[(unsigned __int16)(v5 + 12)] = rf_multiplayer_game_flags;
    *(_DWORD *)&v6[(unsigned __int16)(v5 + 16)] = dword_6FC428;
    *(_DWORD *)&v6[(unsigned __int16)(v5 + 20)] = dword_704EE4;
    v6[(unsigned __int16)(v5 + 24)] = *(_BYTE *)(*(_DWORD *)(a2 + 4608) + 20);
    *(_DWORD *)&v6[(unsigned __int16)(v5 + 25)] = *(_DWORD *)(*(_DWORD *)(a2 + 4608) + 8);
    *(_WORD *)&v6[1] = v5 + 26;
    return rf_network_send_unreliable(a1, v6, (unsigned __int16)(v5 + 29));
  }
  return result;
}

