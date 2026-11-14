// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A7800 rf_multiplayer_queue_weapon_fire_packet48
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(shooterEntity,position,matrix,weapon,mode LOW BYTE). Opcode decimal48, little-endian payload WORD, unsigned16 cursor; queue UNRELIABLE. Client
// path runtime1/authority0: packet header3 + weapon LOW BYTE + flagsBYTE (bit0 iff mode==EXACT1; bit1 iff unchecked weapon flag0x800), then3 positionFLOAT32 and3 low16 trunc(matrix
// floats[6..8]*32767.0), total23. Position transfers use native FLD/FSTP, not guaranteed signaling-NaN bit copy. Flag2 appends hit-samples4A71B0 (caller also passes ignored entity),
// length1+3*n. Writes payload total-3 and queues to local player. Other path: lookup owning player by shooter handle44; require owner/net nonnull. Walk circular player list, skip
// local and owner; recipient net unguarded then state12==2. Per peer flags bit0 plus bit2(value4) from4A7700. Header3+weaponBYTE+flagsBYTE+OWNER netID BYTE20 ->6 bytes; if flag4
// clear append same18 pose bytes ->24. If flag4 set omit all pose bytes. No hit list in relay. Reads next after queue callback, no saved-next protection, capacity/result aggregation
// or own weapon bounds. Does not create projectile itself; return incidental.
_DWORD *__cdecl rf_multiplayer_queue_weapon_fire_packet48(int a1, float *a2, float *a3, int a4, char a5)
{
  _DWORD *result; // eax
  int v6; // [esp+0h] [ebp-46Ch]
  unsigned __int16 v7; // [esp+28h] [ebp-444h]
  char v8; // [esp+2Ch] [ebp-440h] BYREF
  __int16 v9; // [esp+2Dh] [ebp-43Fh]
  char v10; // [esp+2Fh] [ebp-43Dh]
  char v11; // [esp+30h] [ebp-43Ch]
  char v12; // [esp+31h] [ebp-43Bh]
  float v13; // [esp+32h] [ebp-43Ah]
  float v14; // [esp+36h] [ebp-436h]
  float v15; // [esp+3Ah] [ebp-432h]
  __int16 v16; // [esp+3Eh] [ebp-42Eh]
  __int16 v17; // [esp+40h] [ebp-42Ch]
  __int16 v18; // [esp+42h] [ebp-42Ah]
  char v19; // [esp+233h] [ebp-239h]
  int i; // [esp+234h] [ebp-238h]
  _DWORD *v21; // [esp+238h] [ebp-234h]
  __int16 v22; // [esp+23Ch] [ebp-230h]
  __int16 v23; // [esp+244h] [ebp-228h]
  __int16 v24; // [esp+248h] [ebp-224h]
  __int16 v25; // [esp+24Ch] [ebp-220h]
  float v26; // [esp+250h] [ebp-21Ch]
  float v27; // [esp+254h] [ebp-218h]
  float v28; // [esp+258h] [ebp-214h]
  char v29; // [esp+25Eh] [ebp-20Eh]
  char v30; // [esp+25Fh] [ebp-20Dh]
  unsigned __int16 v31; // [esp+260h] [ebp-20Ch]
  char Src; // [esp+264h] [ebp-208h] BYREF
  __int16 Src_1; // [esp+265h] [ebp-207h]
  char Src_3; // [esp+267h] [ebp-205h]
  char v35; // [esp+268h] [ebp-204h]
  float v36; // [esp+269h] [ebp-203h]
  float v37; // [esp+26Dh] [ebp-1FFh]
  float v38; // [esp+271h] [ebp-1FBh]
  __int16 v39; // [esp+275h] [ebp-1F7h]
  __int16 v40; // [esp+277h] [ebp-1F5h]
  __int16 v41; // [esp+279h] [ebp-1F3h]
  char v42; // [esp+46Ah] [ebp-2h]
  char v43; // [esp+46Bh] [ebp-1h]

  v43 = a4;
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
  {
    result = sub_4DD720(*(_DWORD *)(a1 + 44));
    v21 = result;
    if ( result && v21[1152] )
    {
      result = (_DWORD *)dword_87C324;
      for ( i = dword_87C324; i; i = v6 )
      {
        result = (_DWORD *)i;
        if ( i != rf_local_fpgun_player && (_DWORD *)i != v21 )
        {
          result = *(_DWORD **)(i + 4608);
          if ( result[3] == 2 )
          {
            v19 = a5 == 1;
            if ( rf_multiplayer_weapon_fire_omit_pose_for_peer(a1, i, a4, a5) )
              v19 |= 4u;
            v8 = 48;
            v10 = v43;
            v11 = v19;
            v12 = *(_BYTE *)(v21[1152] + 20);
            v7 = 6;
            if ( (v19 & 4) == 0 )
            {
              v13 = *a2;
              v14 = a2[1];
              v15 = a2[2];
              v16 = (int)(a3[6] * 32767.0);
              v17 = (int)(a3[7] * 32767.0);
              v18 = (int)(a3[8] * 32767.0);
              v7 = 24;
            }
            v9 = v7 - 3;
            result = (_DWORD *)rf_network_queue_unreliable_player_packet(i, &v8, v7);
          }
        }
        if ( *(_DWORD *)i == dword_87C324 )
        {
          v6 = 0;
        }
        else
        {
          result = (_DWORD *)i;
          v6 = *(_DWORD *)i;
        }
      }
    }
  }
  else
  {
    v42 = a5 == 1;
    if ( (rf_weapon_records_flags2[340 * a4] & 0x800) != 0 )
      v42 |= 2u;
    Src = 48;
    v30 = v43;
    Src_3 = v43;
    v29 = v42;
    v35 = v42;
    v31 = 5;
    v28 = *a2;
    v36 = v28;
    v31 = 9;
    v27 = a2[1];
    v37 = v27;
    v31 = 13;
    v26 = a2[2];
    v38 = v26;
    v31 = 17;
    v25 = (int)(a3[6] * 32767.0);
    v24 = v25;
    v39 = v25;
    v31 = 19;
    v25 = (int)(a3[7] * 32767.0);
    v23 = v25;
    v40 = v25;
    v31 = 21;
    v41 = (int)(a3[8] * 32767.0);
    v31 = 23;
    if ( (v42 & 2) != 0 )
      v31 += rf_replication_encode_forward_hit_samples((int)(&Src + v31));
    v22 = v31 - 3;
    Src_1 = v31 - 3;
    return (_DWORD *)rf_network_queue_unreliable_player_packet(rf_local_fpgun_player, &Src, v31);
  }
  return result;
}

