// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0B40 rf_multiplayer_send_item_create_packet45
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Cdecl(item,optional peer,raw16 slot). No own runtime/authority/item null guard. Builds opcode45 in a512-byte stack buffer with uint16 cursor and header payload=total-3. Starts with
// NUL-terminated bytes of item RFString+668: unbounded source scan, truncates strlen to uint16 for memcpy, appends explicit NUL. No own512-byte buffer/length bound; all subsequent
// cursor increments wrap16 bits. For ordinary unwrapped string length L, total=L+72 and payload=L+69.
// After name: item BYTE+40; DWORD+664; DWORD+684; DWORD+676; object identifier DWORD+44; raw slot WORD; inactive state BYTE h(104) if rf_object_has_respawn_inactive_flag, otherwise
// u(117);3 position floats and9 matrix floats. Instance flags DWORD+700 mask20 has PRIORITY and selects saved RED CTF home position/matrix; otherwise mask40 selects saved BLUE home,
// otherwise uses live common position+60/matrix+72. Home getters use shared runtime fallback data if CTF uninitialized. All branches serialize12 floats with native x87
// single-precision temporaries; no current/predicted/physical transform payload. Nonnull peer queues reliable(packet,total,0), null peer delegates common fanout; no direct state
// mutation or immediate queue flush.
int __cdecl rf_multiplayer_send_item_create_packet45(int a1, int a2, __int16 a3)
{
  const char *v3; // eax
  float v5[3]; // [esp+74h] [ebp-2C0h] BYREF
  float v6[21]; // [esp+80h] [ebp-2B4h] BYREF
  float v7; // [esp+D4h] [ebp-260h] BYREF
  float v8; // [esp+D8h] [ebp-25Ch]
  float v9; // [esp+DCh] [ebp-258h]
  float v10; // [esp+E0h] [ebp-254h] BYREF
  float v11; // [esp+E4h] [ebp-250h]
  float v12; // [esp+E8h] [ebp-24Ch]
  float v13; // [esp+ECh] [ebp-248h]
  float v14; // [esp+F0h] [ebp-244h]
  float v15; // [esp+F4h] [ebp-240h]
  float v16; // [esp+F8h] [ebp-23Ch]
  float v17; // [esp+FCh] [ebp-238h]
  float v18; // [esp+100h] [ebp-234h]
  unsigned __int8 v19; // [esp+107h] [ebp-22Dh]
  __int16 v20; // [esp+108h] [ebp-22Ch]
  int v21; // [esp+10Ch] [ebp-228h]
  int v22; // [esp+110h] [ebp-224h]
  int v23; // [esp+114h] [ebp-220h]
  int v24; // [esp+118h] [ebp-21Ch]
  unsigned __int8 v25; // [esp+11Fh] [ebp-215h]
  unsigned __int16 v26; // [esp+120h] [ebp-214h]
  unsigned __int16 v27; // [esp+124h] [ebp-210h]
  unsigned __int8 v28; // [esp+12Bh] [ebp-209h]
  unsigned __int8 Src[512]; // [esp+12Ch] [ebp-208h] BYREF
  __int16 v30; // [esp+330h] [ebp-4h]

  Src[0] = 45;
  v26 = strlen(rf_string_object_c_str_or_empty((const void *)(a1 + 668)));
  v3 = rf_string_object_c_str_or_empty((const void *)(a1 + 668));
  memcpy(&Src[3], v3, v26);
  v27 = v26 + 3;
  Src[v27++] = 0;
  v25 = *(_BYTE *)(a1 + 40);
  Src[v27++] = v25;
  v24 = *(_DWORD *)(a1 + 664);
  *(_DWORD *)&Src[v27] = v24;
  v27 += 4;
  v23 = *(_DWORD *)(a1 + 684);
  *(_DWORD *)&Src[v27] = v23;
  v27 += 4;
  v22 = *(_DWORD *)(a1 + 676);
  *(_DWORD *)&Src[v27] = v22;
  v27 += 4;
  v21 = *(_DWORD *)(a1 + 44);
  *(_DWORD *)&Src[v27] = v21;
  v27 += 4;
  v30 = a3;
  v20 = a3;
  *(_WORD *)&Src[v27] = a3;
  v27 += 2;
  if ( rf_object_has_respawn_inactive_flag(a1) )
    v28 = 104;
  else
    v28 = 117;
  v19 = v28;
  Src[v27++] = v28;
  if ( (*(_DWORD *)(a1 + 700) & 0x20) != 0 )
  {
    rf_ctf_red_home_position_copy(&v7);
    rf_ctf_red_home_matrix_copy((int)&v10);
    v6[20] = v7;
    *(float *)&Src[v27] = v7;
    v27 += 4;
    v6[19] = v8;
    *(float *)&Src[v27] = v8;
    v27 += 4;
    v6[18] = v9;
    *(float *)&Src[v27] = v9;
    v27 += 4;
    v6[17] = v10;
    *(float *)&Src[v27] = v10;
    v27 += 4;
    v6[16] = v11;
    *(float *)&Src[v27] = v11;
    v27 += 4;
    v6[15] = v12;
    *(float *)&Src[v27] = v12;
    v27 += 4;
    v6[14] = v13;
    *(float *)&Src[v27] = v13;
    v27 += 4;
    v6[13] = v14;
    *(float *)&Src[v27] = v14;
    v27 += 4;
    v6[12] = v15;
    *(float *)&Src[v27] = v15;
    v27 += 4;
    v6[11] = v16;
    *(float *)&Src[v27] = v16;
    v27 += 4;
    v6[10] = v17;
    *(float *)&Src[v27] = v17;
    v27 += 4;
    v6[9] = v18;
    *(float *)&Src[v27] = v18;
    v27 += 4;
  }
  else
  {
    if ( (*(_DWORD *)(a1 + 700) & 0x40) != 0 )
    {
      rf_ctf_blue_home_position_copy(v5);
      rf_ctf_blue_home_matrix_copy((int)v6);
      *(float *)&Src[v27] = v5[0];
      v27 += 4;
      *(float *)&Src[v27] = v5[1];
      v27 += 4;
      *(float *)&Src[v27] = v5[2];
      v27 += 4;
      *(float *)&Src[v27] = v6[0];
      v27 += 4;
      *(float *)&Src[v27] = v6[1];
      v27 += 4;
      *(float *)&Src[v27] = v6[2];
      v27 += 4;
      *(float *)&Src[v27] = v6[3];
      v27 += 4;
      *(float *)&Src[v27] = v6[4];
      v27 += 4;
      *(float *)&Src[v27] = v6[5];
      v27 += 4;
      *(float *)&Src[v27] = v6[6];
      v27 += 4;
      *(float *)&Src[v27] = v6[7];
      v27 += 4;
      *(float *)&Src[v27] = v6[8];
    }
    else
    {
      *(float *)&Src[v27] = *(float *)(a1 + 60);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 64);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 68);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 72);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 76);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 80);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 84);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 88);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 92);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 96);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 100);
      v27 += 4;
      *(float *)&Src[v27] = *(float *)(a1 + 104);
    }
    v27 += 4;
  }
  *(_WORD *)&Src[1] = v27 - 3;
  if ( a2 )
    return rf_multiplayer_queue_reliable_packet(a2, Src, v27, 0);
  else
    return rf_server_broadcast_packet(Src, v27, 0);
}

