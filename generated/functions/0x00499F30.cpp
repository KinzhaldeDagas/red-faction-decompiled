// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499F30 rf_server_send_entity_spawn_to_peer
// UNREALRED VERIFIED [death-respawn-decode]: Builds and sends variable packet type 44 with the fresh entity bootstrap payload to one supplied peer.
// Builds packet 44 entity-create bootstrap including entity name/type/transform, associated network player id, selected multiplayer character, and weapon indices.
int __cdecl rf_server_send_entity_spawn_to_peer(int a1, int a2)
{
  const char *v2; // eax
  unsigned __int16 v4; // [esp+0h] [ebp-278h]
  unsigned __int8 Src[516]; // [esp+68h] [ebp-210h] BYREF
  unsigned __int8 v6; // [esp+272h] [ebp-6h]
  unsigned __int8 v7; // [esp+273h] [ebp-5h]
  _DWORD *v8; // [esp+274h] [ebp-4h]

  v7 = *(_BYTE *)(a1 + 664);
  Src[0] = 44;
  v4 = strlen(rf_string_object_c_str_or_empty((const void *)(a1 + 24)));
  v2 = rf_string_object_c_str_or_empty((const void *)(a1 + 24));
  memcpy(&Src[3], v2, v4);
  Src[(unsigned __int16)(v4 + 3)] = 0;
  Src[(unsigned __int16)(v4 + 4)] = *(_BYTE *)(a1 + 40);
  Src[(unsigned __int16)(v4 + 5)] = v7;
  *(_DWORD *)&Src[(unsigned __int16)(v4 + 6)] = *(_DWORD *)(a1 + 44);
  *(_DWORD *)&Src[(unsigned __int16)(v4 + 10)] = *(_DWORD *)(a1 + 48);
  *(float *)&Src[(unsigned __int16)(v4 + 14)] = *(float *)(a1 + 60);
  *(float *)&Src[(unsigned __int16)(v4 + 18)] = *(float *)(a1 + 64);
  *(float *)&Src[(unsigned __int16)(v4 + 22)] = *(float *)(a1 + 68);
  *(float *)&Src[(unsigned __int16)(v4 + 26)] = *(float *)(a1 + 72);
  *(float *)&Src[(unsigned __int16)(v4 + 30)] = *(float *)(a1 + 76);
  *(float *)&Src[(unsigned __int16)(v4 + 34)] = *(float *)(a1 + 80);
  *(float *)&Src[(unsigned __int16)(v4 + 38)] = *(float *)(a1 + 84);
  *(float *)&Src[(unsigned __int16)(v4 + 42)] = *(float *)(a1 + 88);
  *(float *)&Src[(unsigned __int16)(v4 + 46)] = *(float *)(a1 + 92);
  *(float *)&Src[(unsigned __int16)(v4 + 50)] = *(float *)(a1 + 96);
  *(float *)&Src[(unsigned __int16)(v4 + 54)] = *(float *)(a1 + 100);
  *(float *)&Src[(unsigned __int16)(v4 + 58)] = *(float *)(a1 + 104);
  v8 = sub_4DD720(*(_DWORD *)(a1 + 44));
  if ( !v8 )
    return printf("Not telling players about an entity!\n");
  v6 = -1;
  v6 = *(_BYTE *)(v8[1152] + 20);
  Src[(unsigned __int16)(v4 + 62)] = v6;
  *(_DWORD *)&Src[(unsigned __int16)(v4 + 63)] = v8[983];
  *(_DWORD *)&Src[(unsigned __int16)(v4 + 67)] = *(_DWORD *)(a1 + 676);
  *(_DWORD *)&Src[(unsigned __int16)(v4 + 71)] = *(_DWORD *)(a1 + 680);
  *(_WORD *)&Src[1] = v4 + 72;
  return rf_multiplayer_queue_reliable_packet(a2, Src, (unsigned __int16)(v4 + 75), 0);
}

