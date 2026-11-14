// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A8630 rf_replication_encode_entity_record38
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(recipientPlayer,entity,destination), returns signed byte count, no capacity. Select mask via4A8DB0; mask0 returns0. Header DWORD entity+44
// handle on non-client paths, entity+628 UID on runtime1/authority0; then maskBYTE. Gets motion snapshot via4A8460 into no-op-constructed stack vectors. Optional fields in EXACT
// order: bit1 motion: timestampWORD,position3FLOAT32,low16 trunc(round32(angleA.x/DOUBLE1.600000023841858)*32767),low16
// trunc(round32(angleB.y/DOUBLE6.33318567276001)*32767),actionBYTE encoded with selector1,velocity3BYTE. Velocity uses CURRENT entity vector324, normalized copy; magnitude
// clamp[0,127], direction x/y trunc(*127) lowBYTE, magnitude trunc low7 with0x80 iff normalized z ORDERED<0. Runtime1/authority0 adds global weapon-selection BYTE662C28 inside motion
// block, giving23 motion bytes vs22 otherwise. Next bit0x80 powerupBYTE; bit8 hit samples1+3*n; bit2 local net WORD532 then RESET packet38 statistics window; bit4 current weapon LOW
// BYTE; bit0x20 health/armor individually copy/clamp[0,255]/truncate packed low/highBYTE WORD plus recipient damage BYTE4604 iff recipient.entityHandle20==entity.handle44,
// otherwise0. Bits0x10/0x40 carry no extra payload. Position uses FLD/FSTP. Finally for local entity with motion buffer appends snapshot to own motion history with delay0 EVEN if
// mask lacked motion. No field bounds/finite validation; snapshot helper may leave outputs uninitialized for missing buffer.
int __cdecl rf_replication_encode_entity_record38(int a1, int a2, int a3)
{
  int v4; // eax
  int v5; // [esp+38h] [ebp-CCh] BYREF
  __int16 v6; // [esp+3Ch] [ebp-C8h]
  int v7[2]; // [esp+40h] [ebp-C4h] BYREF
  char v8; // [esp+4Ah] [ebp-BAh]
  char v9; // [esp+4Bh] [ebp-B9h]
  int v10; // [esp+4Ch] [ebp-B8h]
  __int16 v11; // [esp+50h] [ebp-B4h]
  __int16 v12; // [esp+54h] [ebp-B0h]
  int v13; // [esp+58h] [ebp-ACh]
  char v14; // [esp+5Eh] [ebp-A6h]
  _BYTE v15[5]; // [esp+5Fh] [ebp-A5h] BYREF
  float v16[3]; // [esp+64h] [ebp-A0h] BYREF
  char v17; // [esp+71h] [ebp-93h]
  char v18; // [esp+72h] [ebp-92h]
  char v19; // [esp+73h] [ebp-91h]
  float v20; // [esp+74h] [ebp-90h] BYREF
  unsigned __int8 v21; // [esp+7Bh] [ebp-89h]
  __int16 v22; // [esp+7Ch] [ebp-88h]
  __int16 v23; // [esp+80h] [ebp-84h]
  float v24; // [esp+84h] [ebp-80h]
  __int16 v25; // [esp+88h] [ebp-7Ch]
  __int16 v26; // [esp+8Ch] [ebp-78h]
  float v27; // [esp+90h] [ebp-74h]
  float v28; // [esp+94h] [ebp-70h]
  float v29; // [esp+98h] [ebp-6Ch]
  int v30; // [esp+9Ch] [ebp-68h]
  unsigned __int16 v31; // [esp+A0h] [ebp-64h]
  unsigned __int8 v32; // [esp+A7h] [ebp-5Dh] BYREF
  int v33; // [esp+A8h] [ebp-5Ch]
  unsigned __int8 v34; // [esp+AFh] [ebp-55h]
  int v35; // [esp+B0h] [ebp-54h]
  int v36; // [esp+B4h] [ebp-50h]
  int v37; // [esp+B8h] [ebp-4Ch]
  int v38[3]; // [esp+BCh] [ebp-48h] BYREF
  int v39; // [esp+C8h] [ebp-3Ch]
  unsigned __int8 v40; // [esp+CFh] [ebp-35h] BYREF
  int v41[3]; // [esp+D0h] [ebp-34h] BYREF
  int v42[3]; // [esp+DCh] [ebp-28h] BYREF
  unsigned __int16 v43; // [esp+E8h] [ebp-1Ch] BYREF
  int v44; // [esp+ECh] [ebp-18h] BYREF
  float v45; // [esp+F0h] [ebp-14h]
  float v46; // [esp+F4h] [ebp-10h]
  int v47[3]; // [esp+F8h] [ebp-Ch] BYREF

  rf_replication_select_entity_record38_mask(a1, (int *)a2, &v40);
  if ( !v40 )
    return 0;
  v37 = 0;
  v39 = 0;
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
  {
    v35 = *(_DWORD *)(a2 + 44);
    *(_DWORD *)(v37 + a3) = v35;
    v37 += 4;
  }
  else
  {
    v36 = *(_DWORD *)(a2 + 628);
    *(_DWORD *)(v37 + a3) = v36;
    v37 += 4;
  }
  v34 = v40;
  *(_BYTE *)(v37 + a3) = v40;
  v33 = ++v37 - v39;
  rf_vector3_default_construct_noop(&v44);
  rf_vector3_default_construct_noop(v41);
  rf_vector3_default_construct_noop(v47);
  rf_vector3_default_construct_noop(v42);
  rf_vector3_default_construct_noop(v38);
  rf_replication_get_entity_motion_snapshot(
    a2,
    (float *)&v44,
    (float *)v41,
    (float *)v47,
    (float *)v42,
    (float *)v38,
    &v43);
  if ( ((unsigned __int8)word_662BE8 & v40) != 0 )
  {
    v31 = v43;
    *(_WORD *)(v37 + a3) = v43;
    v37 += 2;
    v30 = v44;
    *(float *)(v37 + a3) = *(float *)&v44;
    v37 += 4;
    v29 = v45;
    *(float *)(v37 + a3) = v45;
    v37 += 4;
    v28 = v46;
    *(float *)(v37 + a3) = v46;
    v37 += 4;
    v27 = *(float *)v42 / 1.600000023841858;
    v26 = (int)(v27 * 32767.0);
    v25 = v26;
    *(_WORD *)(v37 + a3) = v26;
    v37 += 2;
    v24 = *(float *)&v38[1] / 6.33318567276001;
    v23 = (int)(v24 * 32767.0);
    v22 = v23;
    *(_WORD *)(v37 + a3) = v23;
    v37 += 2;
    rf_replication_encode_or_apply_entity_action_bits((_DWORD *)a2, &v32, 1);
    v21 = v32;
    *(_BYTE *)(v37 + a3) = v32;
    ++v37;
    rf_vector3_copy_return_destination(v16, (float *)(a2 + 324));
    v20 = rf_vector3_normalize_return_length(v16);
    rf_float_clamp_in_place(&v20, 0.0, 127.0);
    v19 = (int)(v16[0] * 127.0);
    v18 = (int)(v16[1] * 127.0);
    v17 = (int)v20;
    if ( v16[2] < 0.0 )
      v17 |= 0x80u;
    v15[4] = v19;
    *(_BYTE *)(v37 + a3) = v19;
    ++v37;
    v15[3] = v18;
    *(_BYTE *)(v37 + a3) = v18;
    ++v37;
    v15[2] = v17;
    *(_BYTE *)(v37 + a3) = v17;
    ++v37;
    if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    {
      v15[1] = byte_662C28;
      *(_BYTE *)(v37 + a3) = byte_662C28;
      ++v37;
    }
  }
  if ( ((unsigned __int8)word_662C20 & v40) != 0 )
  {
    v39 = v37;
    rf_replication_encode_player_powerup_bits(a2, v15);
    v14 = v15[0];
    *(_BYTE *)(v37 + a3) = v15[0];
    v13 = ++v37 - v39;
  }
  if ( ((unsigned __int8)word_662C00 & v40) != 0 )
  {
    v4 = rf_replication_encode_forward_hit_samples(v37 + a3);
    v37 += v4;
  }
  if ( ((unsigned __int8)word_662BF0 & v40) != 0 )
  {
    v39 = v37;
    v12 = 0;
    v12 = *(_WORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 532);
    rf_net_statistics_reset_packet38_window((int *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 28));
    v11 = v12;
    *(_WORD *)(v37 + a3) = v12;
    v37 += 2;
    v10 = v37 - v39;
  }
  if ( ((unsigned __int8)word_662BF8 & v40) != 0 )
  {
    v39 = v37;
    v9 = *(_BYTE *)(a2 + 676);
    v8 = v9;
    *(_BYTE *)(v37 + a3) = v9;
    v7[1] = ++v37 - v39;
  }
  if ( ((unsigned __int8)word_662C10 & v40) != 0 )
  {
    v39 = v37;
    v6 = 0;
    v7[0] = *(int *)(a2 + 52);
    rf_float_clamp_in_place((float *)v7, 0.0, 255.0);
    v5 = *(int *)(a2 + 56);
    rf_float_clamp_in_place((float *)&v5, 0.0, 255.0);
    v6 = ((unsigned __int8)(int)*(float *)&v5 << 8) | (unsigned __int8)(int)*(float *)v7;
    *(_WORD *)(v37 + a3) = v6;
    v37 += 2;
    if ( *(_DWORD *)(a1 + 20) == *(_DWORD *)(a2 + 44) )
      *(_BYTE *)(v37 + a3) = *(_BYTE *)(a1 + 4604);
    else
      *(_BYTE *)(v37 + a3) = 0;
    ++v37;
  }
  if ( a2 == dword_681E38 )
  {
    if ( *(_DWORD *)(a2 + 632) )
      rf_motion_sample_buffer_insert_and_extend_curve(
        *(_DWORD *)(a2 + 632),
        a2,
        (int)&v44,
        (int)v38,
        (int)v42,
        (int)v41,
        (int)v47,
        v43,
        0.0);
  }
  return v37;
}

