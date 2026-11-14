// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00498590 rf_ctf_send_flag_state_packet33
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(optional peer). Requires game mode1 and nonzero initialized77D6E2; has no own runtime/authority guard. Builds opcode33 plus uint16 little-endian payload-length header.
// Serializes RED state then BLUE state, with no capture counters. Each flag record is: one raw carrier network-id BYTE if carrier and its DWORD+4608 net pointer are nonnull (net id
// at+20); otherwise FF sentinel followed by home BYTE. Home bit is instance DWORD+700 mask200. At home emits FF,1 (2 bytes); away emits FF,0 then common position+60 (3 floats) and
// common matrix+72 (9 floats), 50 bytes total. Carrier path is one byte only and takes precedence over home bit; a carrier lacking net data uses flag pose fallback instead. Raw idFF
// is not reserved/validated here although receiver interprets FF as no-carrier sentinel.
// Payload size is sum of record sizes1/2/50; total packet size ranges5..103 bytes, uint16 cursor, header payload=total-3. Native float serialization uses x87 load/store temporary
// single precision. No flag/pose pointer null guards on fallback paths; initialized after just one flag registration does not ensure both pointers. Nonnull peer delegates to
// reliable-packet queue4A0070(peer,buffer,total,0), null peer to server_broadcast_packet(buffer,total,0). Native call4AF3A0 sends this during initial peer world-state
// synchronization; this function itself changes no carrier, timer, home pose or capture score. Return EAX is transport/guard artifact.
int __cdecl rf_ctf_send_flag_state_packet33(int a1)
{
  int result; // eax
  unsigned __int16 v2; // [esp+74h] [ebp-218h]
  unsigned __int16 v3; // [esp+74h] [ebp-218h]
  unsigned __int16 v4; // [esp+74h] [ebp-218h]
  unsigned __int16 v5; // [esp+74h] [ebp-218h]
  unsigned __int8 Src; // [esp+7Ch] [ebp-210h] BYREF
  __int16 Src_1; // [esp+7Dh] [ebp-20Fh]
  char Src_3; // [esp+7Fh] [ebp-20Dh]
  char v9; // [esp+80h] [ebp-20Ch]
  float v10; // [esp+81h] [ebp-20Bh]
  float v11; // [esp+85h] [ebp-207h]
  float v12; // [esp+89h] [ebp-203h]
  float v13; // [esp+8Dh] [ebp-1FFh]
  float v14; // [esp+91h] [ebp-1FBh]
  float v15; // [esp+95h] [ebp-1F7h]
  float v16; // [esp+99h] [ebp-1F3h]
  float v17; // [esp+9Dh] [ebp-1EFh]
  float v18; // [esp+A1h] [ebp-1EBh]
  float v19; // [esp+A5h] [ebp-1E7h]
  float v20; // [esp+A9h] [ebp-1E3h]
  float v21; // [esp+ADh] [ebp-1DFh]
  int v22; // [esp+284h] [ebp-8h]
  int v23; // [esp+288h] [ebp-4h]

  result = rf_multiplayer_game_mode_get();
  if ( result == 1 )
  {
    result = (unsigned __int8)byte_77D6E2;
    if ( byte_77D6E2 )
    {
      Src = 33;
      v22 = rf_ctf_red_carrier_get();
      v23 = rf_ctf_blue_carrier_get();
      if ( v22 && *(_DWORD *)(v22 + 4608) )
      {
        Src_3 = *(_BYTE *)(*(_DWORD *)(v22 + 4608) + 20);
        v2 = 4;
      }
      else
      {
        Src_3 = -1;
        if ( (*(_DWORD *)(dword_77D6E4 + 700) & 0x200) != 0 )
        {
          v9 = 1;
          v2 = 5;
        }
        else
        {
          v9 = 0;
          v10 = *(float *)(dword_77D6E4 + 60);
          v11 = *(float *)(dword_77D6E4 + 64);
          v12 = *(float *)(dword_77D6E4 + 68);
          v13 = *(float *)(dword_77D6E4 + 72);
          v14 = *(float *)(dword_77D6E4 + 76);
          v15 = *(float *)(dword_77D6E4 + 80);
          v16 = *(float *)(dword_77D6E4 + 84);
          v17 = *(float *)(dword_77D6E4 + 88);
          v18 = *(float *)(dword_77D6E4 + 92);
          v19 = *(float *)(dword_77D6E4 + 96);
          v20 = *(float *)(dword_77D6E4 + 100);
          v21 = *(float *)(dword_77D6E4 + 104);
          v2 = 53;
        }
      }
      if ( v23 && *(_DWORD *)(v23 + 4608) )
      {
        *(&Src + v2) = *(_BYTE *)(*(_DWORD *)(v23 + 4608) + 20);
        v3 = v2 + 1;
      }
      else
      {
        *(&Src + v2) = -1;
        v4 = v2 + 1;
        if ( (*(_DWORD *)(dword_77D6E8 + 700) & 0x200) != 0 )
        {
          *(&Src + v4) = 1;
          v3 = v4 + 1;
        }
        else
        {
          *(&Src + v4) = 0;
          v5 = v4 + 1;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 60);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 64);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 68);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 72);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 76);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 80);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 84);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 88);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 92);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 96);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 100);
          v5 += 4;
          *(float *)(&Src + v5) = *(float *)(dword_77D6E8 + 104);
          v3 = v5 + 4;
        }
      }
      Src_1 = v3 - 3;
      if ( a1 )
        return rf_multiplayer_queue_reliable_packet(a1, &Src, v3, 0);
      else
        return rf_server_broadcast_packet(&Src, v3, 0);
    }
  }
  return result;
}

