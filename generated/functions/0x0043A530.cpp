// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043A530 rf_entity_snapshot_restore_record
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Restore536-byte entity payload after common60. Signed8 selected weapon fields, signed16 definition index; unsigned16 ammo/reserve arrays; deferred ids/history and recorded AI flags. Literal mask quirk:64 presence bytes rebuilt from ONE32-bit entry+0x100 using SHL byCL, so j/j+32 receive same bit. Route-slot loop resets owner+0x588 count=0; each nonnegative saved slot writes owner+0x58C+4*count WITHOUT incrementing count in that loop, so later valid slot overwrites first. Later route rebuild for admitted AI states may change it separately. Entry byte+0x216 fire bit0x80 can allocate ignition then is CLEARED IN INPUT SNAPSHOT before remaining byte is applied. Existing comments describe other flags/destinations; no claim of pure read-only input or full inverse of writer.
int __cdecl rf_entity_snapshot_restore_record(int a1, int a2)
{
  int v2; // eax
  float v4; // [esp+4h] [ebp-6Ch]
  float v5[3]; // [esp+Ch] [ebp-64h] BYREF
  float v6[3]; // [esp+18h] [ebp-58h] BYREF
  float v7[3]; // [esp+24h] [ebp-4Ch] BYREF
  float v8[3]; // [esp+30h] [ebp-40h] BYREF
  float v9[3]; // [esp+3Ch] [ebp-34h] BYREF
  float v10[3]; // [esp+48h] [ebp-28h] BYREF
  float v11[3]; // [esp+54h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+60h] [ebp-10h] BYREF
  int i; // [esp+6Ch] [ebp-4h]

  rf_object_snapshot_restore_common60(a1, a2);
  if ( *(_DWORD *)(a2 + 40) == -1 )
    *(_DWORD *)(a1 + 1872) = -1;
  *(_DWORD *)(a1 + 676) = *(char *)(a2 + 60);
  *(_DWORD *)(a1 + 680) = *(char *)(a2 + 61);
  *(_DWORD *)(a1 + 664) = *(__int16 *)(a2 + 62);
  for ( i = 0; i < 32; ++i )
    *(_DWORD *)(a1 + 4 * i + 684) = *(unsigned __int16 *)(a2 + 2 * i + 64);
  for ( i = 0; i < 64; ++i )
    *(_DWORD *)(a1 + 4 * i + 812) = *(unsigned __int16 *)(a2 + 2 * i + 128);
  for ( i = 0; i < 64; ++i )
    *(_BYTE *)(i + a1 + 1068) = (*(_DWORD *)(a2 + 256) & (1 << i)) != 0;
  rf_pointer_array_resize_count_unchecked((void **)(a1 + 1196), (void *)*(unsigned __int8 *)(a2 + 292));
  for ( i = 0; i < *(unsigned __int8 *)(a2 + 292); ++i )
  {
    v2 = sub_552200((_DWORD *)(a1 + 1196), i);
    rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 4 * i + 260), v2);
  }
  rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 304), a1 + 1376);
  if ( rf_object_handle_has_direct_player_flag(*(_DWORD *)(a1 + 44)) && (*(_DWORD *)(a1 + 424) & 0x400000) != 0 )
    rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 308), a1 + 2220);
  else
    rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 308), a1 + 1396);
  rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 312), a1 + 1400);
  *(_DWORD *)(a1 + 1436) = *(__int16 *)(a2 + 324);
  *(_DWORD *)(a1 + 1440) = *(__int16 *)(a2 + 326);
  rf_geomod_saved_position_decode_u16(
    (const float *)rf_world_solid,
    (const unsigned __int16 *)(a2 + 328),
    (float *)(a1 + 1568));
  rf_vector_copy((float *)(a1 + 1580), copy_result, (const float *)(a1 + 1568));
  if ( *(__int16 *)(a2 + 334) > -1 )
    *(_DWORD *)(a1 + 1692) = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), *(__int16 *)(a2 + 334));
  if ( *(__int16 *)(a2 + 336) > -1 )
    *(_DWORD *)(a1 + 1696) = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), *(__int16 *)(a2 + 336));
  *(_DWORD *)(a1 + 1416) = 0;
  for ( i = 0; i < 4; ++i )
  {
    if ( *(__int16 *)(a2 + 2 * i + 316) > -1 )
      *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 1416) + 1420) = *(_DWORD *)sub_552200(
                                                                         (_DWORD *)(rf_world_solid + 768),
                                                                         *(__int16 *)(a2 + 2 * i + 316));
  }
  *(_DWORD *)(a1 + 1704) = *(__int16 *)(a2 + 338);
  *(_DWORD *)(a1 + 1708) = *(__int16 *)(a2 + 340);
  *(_DWORD *)(a1 + 1712) = *(unsigned __int8 *)(a2 + 342);
  *(_DWORD *)(a1 + 1716) = *(unsigned __int8 *)(a2 + 343);
  rf_snapshot_unpack_normalized_vector_s16((__int16 *)(a2 + 344), (float *)(a1 + 1728));
  *(_DWORD *)(a1 + 1744) = *(char *)(a2 + 350);
  rf_geomod_saved_position_decode_u16(
    (const float *)rf_world_solid,
    (const unsigned __int16 *)(a2 + 352),
    (float *)(a1 + 1748));
  rf_geomod_saved_position_decode_u16(
    (const float *)rf_world_solid,
    (const unsigned __int16 *)(a2 + 358),
    (float *)(a1 + 1772));
  *(_DWORD *)(a1 + 2136) = sub_445740(*(unsigned __int8 *)(a2 + 295));
  *(_DWORD *)(a1 + 1312) = *(unsigned __int8 *)(a2 + 293);
  *(_DWORD *)(a1 + 1364) = *(unsigned __int8 *)(a2 + 294);
  *(_DWORD *)(a1 + 1324) = *(_DWORD *)(a2 + 296);
  *(_DWORD *)(a1 + 1328) = *(_DWORD *)(a2 + 300);
  rf_vector_copy((float *)(a1 + 1800), v11, (const float *)(a2 + 364));
  rf_vector_copy((float *)(a1 + 1812), v10, (const float *)(a2 + 376));
  *(_BYTE *)(a1 + 1824) = *(_BYTE *)(a2 + 388);
  rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 392), a1 + 1884);
  *(float *)(a1 + 1888) = *(float *)(a2 + 396);
  rf_vector_copy((float *)(a1 + 1952), v9, (const float *)(a2 + 400));
  *(_DWORD *)(a1 + 2000) = *(_DWORD *)(a2 + 412);
  rf_replicator_arm_milliseconds((int *)(a1 + 1876), 0);
  rf_vector_copy((float *)(a1 + 2004), v8, (const float *)(a2 + 416));
  rf_matrix3_copy((float *)(a1 + 2016), (const float *)(a2 + 428));
  *(_DWORD *)(a1 + 2064) = *(_DWORD *)(a2 + 464);
  *(_DWORD *)(a1 + 2068) = *(_DWORD *)(a2 + 468);
  *(_DWORD *)(a1 + 5232) = *(unsigned __int8 *)(a2 + 351);
  rf_vector_copy((float *)(a1 + 2148), v7, (const float *)(a2 + 472));
  rf_vector_copy((float *)(a1 + 2172), v6, (const float *)(a2 + 484));
  rf_vector_copy((float *)(a1 + 2208), v5, (const float *)(a2 + 496));
  if ( (*(_BYTE *)(a2 + 534) & 0x80) != 0 )
  {
    *(_DWORD *)(a1 + 5080) = sub_43E970(*(_DWORD *)(a1 + 44), -1);
    *(_BYTE *)(a2 + 534) &= ~0x80u;
  }
  if ( *(char *)(a2 + 535) != -1 )
    *(_DWORD *)(a1 + 5104) = *(_DWORD *)sub_552200(unk_6FC3E8, *(char *)(a2 + 535));
  *(_DWORD *)(a1 + 2244) = *(unsigned __int8 *)(a2 + 534);
  sub_4344D0(a1, *(unsigned __int8 *)(a2 + 534));
  *(_DWORD *)(a1 + 5004) = *(__int16 *)(a2 + 508);
  *(_DWORD *)(a1 + 5008) = *(__int16 *)(a2 + 510);
  *(_DWORD *)(a1 + 4968) = *(__int16 *)(a2 + 512);
  *(_DWORD *)(a1 + 2628) = *(__int16 *)(a2 + 514);
  *(float *)(a1 + 5012) = *(float *)(a2 + 516);
  *(float *)(a1 + 5016) = *(float *)(a2 + 520);
  *(float *)(a1 + 5060) = *(float *)(a2 + 524);
  *(float *)(a1 + 5064) = *(float *)(a2 + 528);
  *(_DWORD *)(a1 + 5160) = 0;
  if ( (*(_BYTE *)(a2 + 532) & 1) != 0 )
    *(_DWORD *)(a1 + 5160) |= 1 << dword_911CBC;
  if ( (*(_BYTE *)(a2 + 532) & 2) != 0 )
    *(_DWORD *)(a1 + 5160) |= 1 << unk_911C6C;
  if ( (*(_BYTE *)(a2 + 532) & 4) != 0 )
    *(_DWORD *)(a1 + 5160) |= 1 << dword_911CC4;
  if ( (*(_BYTE *)(a2 + 532) & 8) != 0 )
    *(_DWORD *)(a1 + 5160) |= 1 << unk_911C98;
  *(_DWORD *)(a1 + 5164) = *(unsigned __int8 *)(a2 + 533);
  if ( *(_DWORD *)(a1 + 4968) != -1 )
    rf_vfx_start_instance(*(int **)(a1 + 128), *(_DWORD *)(a1 + 4968), 1.0, (*(_DWORD *)(a1 + 2064) & 8) != 0);
  if ( (*(_DWORD *)(a1 + 1312) == 2 || *(_DWORD *)(a1 + 1312) == 16) && *(_DWORD *)(a1 + 1364) == 1 )
    rf_ai_route_build(*(_DWORD *)(a1 + 44), (float *)(a1 + 1772));
  if ( *(_DWORD *)(a1 + 1312) == 4 && *(_DWORD *)(a1 + 1364) == 1 )
  {
    sub_40DCA0(*(_DWORD *)(a1 + 44));
    *(_DWORD *)(a1 + 2068) |= 0x4000u;
  }
  if ( *(_DWORD *)(a1 + 32) == 4952
    && rf_string_equals_case_insensitive((int)unk_6FC31C, "l7s2.rfl")
    && *(_DWORD *)(a1 + 1312) == 2
    && *(_DWORD *)(a1 + 1364) == 1 )
  {
    *(_DWORD *)(a1 + 2068) |= 0x4000u;
  }
  if ( ((unsigned int)&unk_2000000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828)) != 0
    && !rf_entity_class_flag2000000_positive_scalar56(a1) )
  {
    rf_entity_restore_saved_class_motion_and_clear_source(a1, 0);
  }
  if ( *(_DWORD *)(a1 + 1312) == 17 )
  {
    v4 = rf_random_float_range(5.0, 10.0);
    sub_40B1A0((int *)(a1 + 672), v4, 1);
  }
  return rf_replicator_arm_milliseconds((int *)(a1 + 5116), -1000);
}

