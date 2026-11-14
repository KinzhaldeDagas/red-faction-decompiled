// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ABE70 rf_server_send_pregame_remote_charge_packet19
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl recipient player. Acts only runtime mode1 AND authority EXACT1. Walk projectile list head911F74 until sentinel911CE8 using next652, select projectile
// DWORD664==remote-charge registry ID911C78. First count is BYTE increment (wrap256); if resulting byte0 send NOTHING, even when actual count is a nonzero multiple256. Otherwise
// traverse again and serialize ALL matching projectiles, not just wrapped count. Packet opcode19, countBYTE, 71-byte records. Stack buffer512; before record, if
// signed(currentSize+71)>509 finalize current count/payload, reliable_queue(recipient,packet,size,requireActive0), reset packet/count. At most7 records (501 envelope bytes,498
// payload) per packet. After loop always queue final packet. Record offsets: DWORD projectile680 at0, parent688 at4, owner48 at8, float668 at12; position60 XYZ at16, forward-axis96
// XYZ at28, parent-local position692 XYZ at40, parent-local forward728 XYZ at52; common flags424 at64, compressed velocity324 at68..70. Float values pass through x87 single
// temporaries. Velocity copied and normalized; returned length clamped[0,127], X/Y*127 converted truncation towardzero through ftol2 lowBYTE; magnitude truncated via x87 control-word
// to lowBYTE, OR80 when normalizedZ ordered<0. No finite checks. Count backpatched per chunk; WORD payload=size-3. No recipient/local/handle check here beyond queue delegate. Only
// final queue EAX returned, prior queue errors ignored; no aggregate delivery status.
int __cdecl rf_server_send_pregame_remote_charge_packet19(int a1)
{
  int result; // eax
  float v2[3]; // [esp+1Ch] [ebp-280h] BYREF
  unsigned __int8 v3; // [esp+29h] [ebp-273h]
  unsigned __int8 v4; // [esp+2Ah] [ebp-272h]
  unsigned __int8 v5; // [esp+2Bh] [ebp-271h]
  int v6; // [esp+2Ch] [ebp-270h] BYREF
  int v7; // [esp+30h] [ebp-26Ch]
  float v8; // [esp+34h] [ebp-268h]
  float v9; // [esp+38h] [ebp-264h]
  float v10; // [esp+3Ch] [ebp-260h]
  float v11; // [esp+40h] [ebp-25Ch]
  float v12; // [esp+44h] [ebp-258h]
  float v13; // [esp+48h] [ebp-254h]
  float v14; // [esp+4Ch] [ebp-250h]
  float v15; // [esp+50h] [ebp-24Ch]
  float v16; // [esp+54h] [ebp-248h]
  float v17; // [esp+58h] [ebp-244h]
  float v18; // [esp+5Ch] [ebp-240h]
  float v19; // [esp+60h] [ebp-23Ch]
  float v20; // [esp+64h] [ebp-238h]
  int v21; // [esp+68h] [ebp-234h]
  int v22; // [esp+6Ch] [ebp-230h]
  int v23; // [esp+70h] [ebp-22Ch]
  unsigned __int8 v24; // [esp+77h] [ebp-225h]
  __int16 v25; // [esp+78h] [ebp-224h]
  unsigned __int8 v26; // [esp+7Fh] [ebp-21Dh]
  size_t Size; // [esp+80h] [ebp-21Ch]
  int v28; // [esp+84h] [ebp-218h]
  unsigned __int8 v29; // [esp+8Bh] [ebp-211h]
  unsigned __int8 Src[512]; // [esp+8Ch] [ebp-210h] BYREF
  signed int v31; // [esp+290h] [ebp-Ch]
  int i; // [esp+294h] [ebp-8h]
  unsigned __int8 v33; // [esp+29Bh] [ebp-1h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v29 = 0;
    for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
    {
      if ( *(_DWORD *)(i + 664) == dword_911C78 )
        ++v29;
      result = i;
    }
    if ( v29 )
    {
      v31 = 509;
      Src[0] = 19;
      v26 = v29;
      Src[3] = v29;
      Size = 4;
      v33 = 0;
      v28 = 71;
      for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
      {
        if ( *(_DWORD *)(i + 664) == dword_911C78 )
        {
          if ( (int)(v28 + Size) > v31 )
          {
            Src[3] = v33;
            v25 = Size - 3;
            *(_WORD *)&Src[1] = Size - 3;
            rf_multiplayer_queue_reliable_packet(a1, Src, Size, 0);
            Src[0] = 19;
            v24 = v29;
            Src[3] = v29;
            Size = 4;
            v33 = 0;
          }
          v23 = *(_DWORD *)(i + 680);
          *(_DWORD *)&Src[Size] = v23;
          Size += 4;
          v22 = *(_DWORD *)(i + 688);
          *(_DWORD *)&Src[Size] = v22;
          Size += 4;
          v21 = *(_DWORD *)(i + 48);
          *(_DWORD *)&Src[Size] = v21;
          Size += 4;
          v20 = *(float *)(i + 668);
          *(float *)&Src[Size] = v20;
          Size += 4;
          v19 = *(float *)(i + 60);
          *(float *)&Src[Size] = v19;
          Size += 4;
          v18 = *(float *)(i + 64);
          *(float *)&Src[Size] = v18;
          Size += 4;
          v17 = *(float *)(i + 68);
          *(float *)&Src[Size] = v17;
          Size += 4;
          v16 = *(float *)(i + 96);
          *(float *)&Src[Size] = v16;
          Size += 4;
          v15 = *(float *)(i + 100);
          *(float *)&Src[Size] = v15;
          Size += 4;
          v14 = *(float *)(i + 104);
          *(float *)&Src[Size] = v14;
          Size += 4;
          v13 = *(float *)(i + 692);
          *(float *)&Src[Size] = v13;
          Size += 4;
          v12 = *(float *)(i + 696);
          *(float *)&Src[Size] = v12;
          Size += 4;
          v11 = *(float *)(i + 700);
          *(float *)&Src[Size] = v11;
          Size += 4;
          v10 = *(float *)(i + 728);
          *(float *)&Src[Size] = v10;
          Size += 4;
          v9 = *(float *)(i + 732);
          *(float *)&Src[Size] = v9;
          Size += 4;
          v8 = *(float *)(i + 736);
          *(float *)&Src[Size] = v8;
          Size += 4;
          v7 = *(_DWORD *)(i + 424);
          *(_DWORD *)&Src[Size] = v7;
          Size += 4;
          rf_vector3_copy_return_destination(v2, (float *)(i + 324));
          *(float *)&v6 = rf_vector3_normalize_return_length(v2);
          rf_float_clamp_in_place((float *)&v6, 0.0, 127.0);
          v5 = (int)(v2[0] * 127.0);
          v4 = (int)(v2[1] * 127.0);
          v3 = (int)*(float *)&v6;
          if ( v2[2] < 0.0 )
            v3 |= 0x80u;
          Src[Size++] = v5;
          Src[Size++] = v4;
          Src[Size++] = v3;
          ++v33;
        }
      }
      Src[3] = v33;
      *(_WORD *)&Src[1] = Size - 3;
      return rf_multiplayer_queue_reliable_packet(a1, Src, Size, 0);
    }
  }
  return result;
}

