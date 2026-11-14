// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A9F70 sub_4A9F70
// UNREALRED VERIFIED [lan-killfeed-20261028] Authority-only death packet39 sends dead entity handle, health and Entity+0x270 attacker network-id byte (plus victim network-id and optional death entity records). Death feed text is not serialized here: clients reconstruct per-viewer presentation through death admission. Unreal transport adapters must preserve per-viewer formatting without claiming this native wire format.
int __cdecl sub_4A9F70(int a1, int a2, int a3)
{
  int result; // eax
  const char *v4; // eax
  const char *v5; // eax
  int v6; // [esp+0h] [ebp-2E8h]
  unsigned __int16 v7; // [esp+4h] [ebp-2E4h]
  unsigned __int16 v8; // [esp+14h] [ebp-2D4h]
  unsigned __int16 v9; // [esp+D4h] [ebp-214h]
  unsigned __int16 v10; // [esp+D4h] [ebp-214h]
  unsigned __int8 Src[7]; // [esp+D8h] [ebp-210h] BYREF
  float v12; // [esp+DFh] [ebp-209h]
  char v13; // [esp+E3h] [ebp-205h]
  char v14; // [esp+E4h] [ebp-204h]
  __int16 v15; // [esp+E5h] [ebp-203h]
  char v16; // [esp+E7h] [ebp-201h]
  int v17; // [esp+E8h] [ebp-200h] BYREF
  int i; // [esp+2DCh] [ebp-Ch]
  _DWORD *v19; // [esp+2E0h] [ebp-8h]
  char v20; // [esp+2E6h] [ebp-2h]
  char v21; // [esp+2E7h] [ebp-1h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v21 = -1;
    v19 = sub_4DD720(*(_DWORD *)(a1 + 44));
    if ( v19 )
      v21 = *(_BYTE *)(v19[1152] + 20);
    Src[0] = 39;
    *(_DWORD *)&Src[3] = *(_DWORD *)(a1 + 44);
    v12 = *(float *)(a1 + 52);
    v13 = *(_BYTE *)(a1 + 624);
    v14 = v21;
    if ( *(_DWORD *)(a1 + 36) )
      v15 = -1;
    else
      v15 = *(_WORD *)(a1 + 2084);
    v20 = 0;
    if ( a2 )
      v20 |= 1u;
    if ( a3 )
      v20 |= 2u;
    v16 = v20;
    v9 = 16;
    if ( (v20 & 1) != 0 )
    {
      v8 = strlen(rf_string_object_c_str_or_empty((const void *)(a2 + 668)));
      v4 = rf_string_object_c_str_or_empty((const void *)(a2 + 668));
      memcpy(&v17, v4, v8);
      Src[(unsigned __int16)(v8 + 16)] = 0;
      Src[(unsigned __int16)(v8 + 17)] = *(_BYTE *)(a2 + 40);
      *(_DWORD *)&Src[(unsigned __int16)(v8 + 18)] = *(_DWORD *)(a2 + 664);
      *(_DWORD *)&Src[(unsigned __int16)(v8 + 22)] = *(_DWORD *)(a2 + 684);
      *(_DWORD *)&Src[(unsigned __int16)(v8 + 26)] = *(_DWORD *)(a2 + 676);
      *(_DWORD *)&Src[(unsigned __int16)(v8 + 30)] = *(_DWORD *)(a2 + 44);
      *(float *)&Src[(unsigned __int16)(v8 + 34)] = *(float *)(a2 + 60);
      *(float *)&Src[(unsigned __int16)(v8 + 38)] = *(float *)(a2 + 64);
      *(float *)&Src[(unsigned __int16)(v8 + 42)] = *(float *)(a2 + 68);
      *(float *)&Src[(unsigned __int16)(v8 + 46)] = *(float *)(a2 + 72);
      *(float *)&Src[(unsigned __int16)(v8 + 50)] = *(float *)(a2 + 76);
      *(float *)&Src[(unsigned __int16)(v8 + 54)] = *(float *)(a2 + 80);
      *(float *)&Src[(unsigned __int16)(v8 + 58)] = *(float *)(a2 + 84);
      *(float *)&Src[(unsigned __int16)(v8 + 62)] = *(float *)(a2 + 88);
      *(float *)&Src[(unsigned __int16)(v8 + 66)] = *(float *)(a2 + 92);
      *(float *)&Src[(unsigned __int16)(v8 + 70)] = *(float *)(a2 + 96);
      *(float *)&Src[(unsigned __int16)(v8 + 74)] = *(float *)(a2 + 100);
      *(float *)&Src[(unsigned __int16)(v8 + 78)] = *(float *)(a2 + 104);
      v9 = v8 + 82;
    }
    if ( (v20 & 2) != 0 )
    {
      v7 = strlen(rf_string_object_c_str_or_empty((const void *)(a3 + 668)));
      v5 = rf_string_object_c_str_or_empty((const void *)(a3 + 668));
      memcpy(&Src[v9], v5, v7);
      v10 = v7 + v9;
      Src[v10++] = 0;
      Src[v10++] = *(_BYTE *)(a3 + 40);
      *(_DWORD *)&Src[v10] = *(_DWORD *)(a3 + 664);
      v10 += 4;
      *(_DWORD *)&Src[v10] = *(_DWORD *)(a3 + 684);
      v10 += 4;
      *(_DWORD *)&Src[v10] = *(_DWORD *)(a3 + 676);
      v10 += 4;
      *(_DWORD *)&Src[v10] = *(_DWORD *)(a3 + 44);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 60);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 64);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 68);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 72);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 76);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 80);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 84);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 88);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 92);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 96);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 100);
      v10 += 4;
      *(float *)&Src[v10] = *(float *)(a3 + 104);
      v9 = v10 + 4;
    }
    *(_WORD *)&Src[1] = v9 - 3;
    result = 0;
    for ( i = dword_87C324; i; i = v6 )
    {
      if ( i != rf_local_fpgun_player && *(_DWORD *)(i + 4608) && *(_DWORD *)(*(_DWORD *)(i + 4608) + 12) == 2 )
        rf_multiplayer_queue_reliable_packet(i, Src, v9, 0);
      if ( *(_DWORD *)i == dword_87C324 )
        v6 = 0;
      else
        v6 = *(_DWORD *)i;
      result = v6;
    }
  }
  return result;
}

