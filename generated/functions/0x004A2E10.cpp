// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A2E10 rf_multiplayer_send_join_request_packet2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Logical cdecl(endpoint,by-value suppliedName RFString8,by-value password RFString8,requestedRate DWORD), native24 argument bytes represented by existing six-DWORD prototype. Uses
// shared two-RFString prefix constructor, not a distinct allocation of weapon records. No own runtime/authority/local-player-null guard. If local player name length<1 assigns
// Default. Serializes LOCAL name regardless of suppliedName argument; suppliedName is consumed/destroyed but otherwise unused. Copies password into temporary record and reads raw
// local player DWORD+24.
// Opcode2 payload: protocol BYTE89h,local name+NUL,raw player+24 DWORD,password+NUL,requestedRate DWORD, then interleaved signature words A0,B0,A1,B1 from88E674[0..1]/88E67C[0..1].
// Normal name/password lengths N/P give total=N+P+30,payload=N+P+27. Unbounded string scans, uint16 lengths/cursor, no packet bound check. Direct unreliable send to endpoint.
// Destroys temporary string prefix and both by-value string arguments, including SEH paths; does not set pending join IP or wait for response.
void __cdecl rf_multiplayer_send_join_request_packet2(int a1, int a2, int a3, int a4, int a5, int a6)
{
  const char *v6; // eax
  const char *v7; // eax
  unsigned __int16 v8; // [esp+4h] [ebp-280h]
  unsigned __int16 v9; // [esp+14h] [ebp-270h]
  unsigned __int16 v10; // [esp+44h] [ebp-240h]
  unsigned __int16 v11; // [esp+44h] [ebp-240h]
  unsigned __int16 v12; // [esp+44h] [ebp-240h]
  _BYTE v13[516]; // [esp+48h] [ebp-23Ch] BYREF
  _DWORD self[2]; // [esp+250h] [ebp-34h] BYREF
  _DWORD v15[2]; // [esp+258h] [ebp-2Ch] BYREF
  int v16; // [esp+260h] [ebp-24h]
  int i; // [esp+274h] [ebp-10h]
  int v18; // [esp+280h] [ebp-4h]

  v18 = 1;
  rf_two_rfstring_prefix_construct(self);
  LOBYTE(v18) = 2;
  if ( (int)rf_string_length_from_cstr((const char **)(rf_local_fpgun_player + 8)) < 1 )
    rf_string_assign_from_cstr((_DWORD *)(rf_local_fpgun_player + 8), "Default");
  rf_string_assign_from_object(v15, rf_local_fpgun_player + 8);
  rf_string_assign_from_object(self, (int)&a4);
  v16 = *(_DWORD *)(rf_local_fpgun_player + 24);
  v13[0] = 2;
  v13[3] = -119;
  v9 = strlen(rf_string_object_c_str_or_empty(v15));
  v6 = rf_string_object_c_str_or_empty(v15);
  memcpy(&v13[4], v6, v9);
  v13[(unsigned __int16)(v9 + 4)] = 0;
  *(_DWORD *)&v13[(unsigned __int16)(v9 + 5)] = v16;
  v8 = strlen(rf_string_object_c_str_or_empty(self));
  v7 = rf_string_object_c_str_or_empty(self);
  memcpy(&v13[(unsigned __int16)(v9 + 9)], v7, v8);
  v10 = v8 + v9 + 9;
  v13[v10++] = 0;
  *(_DWORD *)&v13[v10] = a6;
  v11 = v10 + 4;
  for ( i = 0; i < 2; ++i )
  {
    *(_DWORD *)&v13[v11] = unk_88E674[i];
    v12 = v11 + 4;
    *(_DWORD *)&v13[v12] = unk_88E67C[i];
    v11 = v12 + 4;
  }
  *(_WORD *)&v13[1] = v11 - 3;
  rf_network_send_unreliable(a1, v13, v11);
  LOBYTE(v18) = 1;
  rf_two_rfstring_prefix_destroy((char *)self);
  LOBYTE(v18) = 0;
  rf_string_destroy_buffer(&a2);
  v18 = -1;
  rf_string_destroy_buffer(&a4);
}

