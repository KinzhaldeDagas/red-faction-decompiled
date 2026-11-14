// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004397E0 rf_entity_snapshot_collect
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Collect536-byte entity records plus separate inactive stable-id list, byte counts. Skip common carryover mask0x800 and case-insensitive definition names bat/fish. Respawn-inactive owners contribute only stable id to separate list. Active writer sets common0x08000000 when owner physics+0x1A8 signed negative, then common60 pack also clamps LIVE life/armor. Preserve decoded AI/history/route/pose state via observed fields and fixup ids. Literal packing quirk: loop64 presence bytes owner+0x42C tests equality1 but ORs 32-bit(1<<CL) into entry+0x100; x86 masks shift count to31, so indices j and j+32 alias. Owner+0x810 is saved at entry+0x1D0 with mask0x100 cleared; fire-owner presence is folded into entry byte+0x216 mask0x80. This contract does not claim lossless full64-flag roundtrip.
char __cdecl rf_entity_snapshot_collect(int a1, _BYTE *a2, int a3, _BYTE *a4)
{
  const char *v4; // eax
  const char *v5; // eax
  int first_dword; // eax
  int *v7; // eax
  int v8; // eax
  char v9; // al
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  char *v15; // eax
  int v16; // eax
  int v17; // eax
  _DWORD *v18; // eax
  char result; // al
  float v20[3]; // [esp+4h] [ebp-74h] BYREF
  float v21[3]; // [esp+10h] [ebp-68h] BYREF
  float v22[3]; // [esp+1Ch] [ebp-5Ch] BYREF
  float v23[3]; // [esp+28h] [ebp-50h] BYREF
  float v24[3]; // [esp+34h] [ebp-44h] BYREF
  float v25[3]; // [esp+40h] [ebp-38h] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-2Ch] BYREF
  int v27; // [esp+58h] [ebp-20h] BYREF
  int character_instance_or_null; // [esp+5Ch] [ebp-1Ch]
  int k; // [esp+60h] [ebp-18h]
  int v30; // [esp+64h] [ebp-14h]
  int v31; // [esp+68h] [ebp-10h]
  int i; // [esp+6Ch] [ebp-Ch]
  int j; // [esp+70h] [ebp-8h]
  int v34; // [esp+74h] [ebp-4h]

  v34 = 0;
  v31 = 0;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 124) & 0x800) == 0 )
    {
      v4 = rf_string_object_c_str_or_empty(*(const void **)(i + 660));
      if ( _stricmp(v4, off_632F54) )
      {
        v5 = rf_string_object_c_str_or_empty(*(const void **)(i + 660));
        if ( _stricmp(v5, "fish") )
        {
          if ( rf_object_has_respawn_inactive_flag(i) )
          {
            *(_DWORD *)(a3 + 4 * v31++) = *(_DWORD *)(i + 32);
          }
          else
          {
            if ( *(int *)(i + 424) < 0 )
              *(_DWORD *)(i + 124) |= 0x8000000u;
            rf_object_snapshot_pack_common60(i, a1 + 536 * v34);
            *(_BYTE *)(a1 + 536 * v34 + 60) = *(_BYTE *)(i + 676);
            *(_BYTE *)(a1 + 536 * v34 + 61) = *(_BYTE *)(i + 680);
            *(_WORD *)(a1 + 536 * v34 + 62) = *(_WORD *)(i + 664);
            for ( j = 0; j < 32; ++j )
            {
              if ( *(int *)(i + 4 * j + 684) > 0 )
                *(_WORD *)(a1 + 536 * v34 + 2 * j + 64) = *(_WORD *)(i + 4 * j + 684);
              else
                *(_WORD *)(a1 + 536 * v34 + 2 * j + 64) = 0;
            }
            for ( j = 0; j < 64; ++j )
              *(_WORD *)(a1 + 536 * v34 + 2 * j + 128) = *(_WORD *)(i + 4 * j + 812);
            *(_DWORD *)(a1 + 536 * v34 + 256) = 0;
            for ( j = 0; j < 64; ++j )
              *(_DWORD *)(a1 + 536 * v34 + 256) |= (*(_BYTE *)(j + i + 1068) == 1) << j;
            for ( j = 0; ; ++j )
            {
              first_dword = rf_receiver_get_first_dword((void *)(i + 1196));
              if ( j >= first_dword )
                break;
              v7 = (int *)sub_552200((_DWORD *)(i + 1196), j);
              v8 = rf_object_runtime_identifier_to_saved_identifier(*v7);
              *(_DWORD *)(a1 + 536 * v34 + 4 * j + 260) = v8;
            }
            v9 = rf_receiver_get_first_dword((void *)(i + 1196));
            *(_BYTE *)(a1 + 536 * v34 + 292) = v9;
            *(_BYTE *)(a1 + 536 * v34 + 293) = *(_BYTE *)(i + 1312);
            *(_BYTE *)(a1 + 536 * v34 + 294) = *(_BYTE *)(i + 1364);
            *(_DWORD *)(a1 + 536 * v34 + 296) = *(_DWORD *)(i + 1324);
            *(_DWORD *)(a1 + 536 * v34 + 300) = *(_DWORD *)(i + 1328);
            v10 = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 1376));
            *(_DWORD *)(a1 + 536 * v34 + 304) = v10;
            v11 = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 1396));
            *(_DWORD *)(a1 + 536 * v34 + 308) = v11;
            if ( rf_object_handle_has_direct_player_flag(*(_DWORD *)(i + 44)) && (*(_DWORD *)(i + 424) & 0x400000) != 0 )
            {
              v12 = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 2220));
              *(_DWORD *)(a1 + 536 * v34 + 308) = v12;
            }
            v13 = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 1400));
            *(_DWORD *)(a1 + 536 * v34 + 312) = v13;
            *(_WORD *)(a1 + 536 * v34 + 324) = *(_WORD *)(i + 1436);
            *(_WORD *)(a1 + 536 * v34 + 326) = *(_WORD *)(i + 1440);
            rf_geomod_saved_position_encode_u16(
              (const float *)rf_world_solid,
              (const float *)(i + 1568),
              (unsigned __int16 *)(a1 + 536 * v34 + 328));
            *(_WORD *)(a1 + 536 * v34 + 334) = -1;
            *(_WORD *)(a1 + 536 * v34 + 336) = -1;
            for ( j = 0; j < 4; ++j )
              *(_WORD *)(a1 + 536 * v34 + 2 * j + 316) = -1;
            for ( j = 0; ; ++j )
            {
              v14 = rf_receiver_get_first_dword((void *)(rf_world_solid + 768));
              if ( j >= v14 )
                break;
              v30 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), j);
              if ( *(_DWORD *)(i + 1692) == v30 )
              {
                *(_WORD *)(a1 + 536 * v34 + 334) = j;
              }
              else if ( *(_DWORD *)(i + 1696) == v30 )
              {
                *(_WORD *)(a1 + 536 * v34 + 336) = j;
              }
              else
              {
                for ( k = 0; k < 4; ++k )
                {
                  if ( *(_DWORD *)(i + 4 * k + 1420) == v30 )
                    *(_WORD *)(a1 + 536 * v34 + 2 * k + 316) = j;
                }
              }
            }
            *(_WORD *)(a1 + 536 * v34 + 338) = *(_WORD *)(i + 1704);
            *(_WORD *)(a1 + 536 * v34 + 340) = *(_WORD *)(i + 1708);
            *(_BYTE *)(a1 + 536 * v34 + 342) = *(_BYTE *)(i + 1712);
            *(_BYTE *)(a1 + 536 * v34 + 343) = *(_BYTE *)(i + 1716);
            rf_snapshot_pack_normalized_vector_s16((float *)(i + 1728), (_WORD *)(a1 + 536 * v34 + 344));
            *(_BYTE *)(a1 + 536 * v34 + 350) = *(_BYTE *)(i + 1744);
            rf_geomod_saved_position_encode_u16(
              (const float *)rf_world_solid,
              (const float *)(i + 1748),
              (unsigned __int16 *)(a1 + 536 * v34 + 352));
            rf_geomod_saved_position_encode_u16(
              (const float *)rf_world_solid,
              (const float *)(i + 1772),
              (unsigned __int16 *)(a1 + 536 * v34 + 358));
            *(_BYTE *)(a1 + 536 * v34 + 295) = 1;
            for ( j = 0; j < 16; ++j )
            {
              v15 = sub_445740(j);
              if ( *(char **)(i + 2136) == v15 )
              {
                *(_BYTE *)(a1 + 536 * v34 + 295) = j;
                break;
              }
            }
            rf_vector_copy((float *)(a1 + 536 * v34 + 364), copy_result, (const float *)(i + 1800));
            rf_vector_copy((float *)(a1 + 536 * v34 + 376), v25, (const float *)(i + 1812));
            *(_BYTE *)(a1 + 536 * v34 + 388) = *(_BYTE *)(i + 1824);
            v16 = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 1884));
            *(_DWORD *)(a1 + 536 * v34 + 392) = v16;
            *(float *)(a1 + 536 * v34 + 396) = *(float *)(i + 1888);
            rf_vector_copy((float *)(a1 + 536 * v34 + 400), v24, (const float *)(i + 1952));
            *(_DWORD *)(a1 + 536 * v34 + 412) = *(_DWORD *)(i + 2000);
            rf_vector_copy((float *)(a1 + 536 * v34 + 416), v23, (const float *)(i + 2004));
            rf_matrix3_copy((float *)(a1 + 536 * v34 + 428), (const float *)(i + 2016));
            *(_DWORD *)(a1 + 536 * v34 + 464) = *(_DWORD *)(i + 2064) & 0xFFFFFEFF;
            *(_DWORD *)(a1 + 536 * v34 + 468) = *(_DWORD *)(i + 2068);
            rf_vector_copy((float *)(a1 + 536 * v34 + 472), v22, (const float *)(i + 2148));
            rf_vector_copy((float *)(a1 + 536 * v34 + 484), v21, (const float *)(i + 2172));
            rf_vector_copy((float *)(a1 + 536 * v34 + 496), v20, (const float *)(i + 2208));
            *(_BYTE *)(a1 + 536 * v34 + 534) = *(_BYTE *)(i + 2244);
            *(_WORD *)(a1 + 536 * v34 + 508) = *(_WORD *)(i + 5004);
            *(_WORD *)(a1 + 536 * v34 + 510) = *(_WORD *)(i + 5008);
            *(_BYTE *)(a1 + 536 * v34 + 351) = *(_BYTE *)(i + 5232);
            if ( *(_DWORD *)(i + 5080) )
              *(_BYTE *)(a1 + 536 * v34 + 534) |= 0x80u;
            if ( !*(_DWORD *)(i + 128) || *(_DWORD *)(i + 4968) == -1 )
            {
              *(_WORD *)(a1 + 536 * v34 + 512) = -1;
            }
            else if ( rf_vfx_get_remaining_time((const void *)*(_DWORD *)(i + 128), *(_DWORD *)(i + 4968)) == 0.0 )
            {
              character_instance_or_null = rf_model_handle_get_character_instance_or_null(*(_DWORD **)(i + 128));
              if ( character_instance_or_null
                && rf_model_read_selected_action_index_if_enabled(character_instance_or_null, &v27) )
              {
                if ( *(_BYTE *)(*(_DWORD *)(character_instance_or_null + 7504) + v27 + 4620) )
                {
                  *(_WORD *)(a1 + 536 * v34 + 512) = -1;
                }
                else
                {
                  *(_WORD *)(a1 + 536 * v34 + 512) = v27;
                  *(_DWORD *)(a1 + 536 * v34 + 464) |= 8u;
                }
              }
              else
              {
                *(_WORD *)(a1 + 536 * v34 + 512) = -1;
              }
            }
            else
            {
              *(_WORD *)(a1 + 536 * v34 + 512) = *(_WORD *)(i + 4968);
            }
            *(_WORD *)(a1 + 536 * v34 + 514) = *(_WORD *)(i + 2628);
            *(float *)(a1 + 536 * v34 + 516) = *(float *)(i + 5012);
            *(float *)(a1 + 536 * v34 + 520) = *(float *)(i + 5016);
            *(float *)(a1 + 536 * v34 + 524) = *(float *)(i + 5060);
            *(float *)(a1 + 536 * v34 + 528) = *(float *)(i + 5064);
            *(_BYTE *)(a1 + 536 * v34 + 532) = 0;
            if ( (*(_DWORD *)(i + 5160) & (1 << dword_911CBC)) != 0 )
              *(_BYTE *)(a1 + 536 * v34 + 532) |= 1u;
            if ( (*(_DWORD *)(i + 5160) & (1 << unk_911C6C)) != 0 )
              *(_BYTE *)(a1 + 536 * v34 + 532) |= 2u;
            if ( (*(_DWORD *)(i + 5160) & (1 << dword_911CC4)) != 0 )
              *(_BYTE *)(a1 + 536 * v34 + 532) |= 4u;
            if ( (*(_DWORD *)(i + 5160) & (1 << unk_911C98)) != 0 )
              *(_BYTE *)(a1 + 536 * v34 + 532) |= 8u;
            *(_BYTE *)(a1 + 536 * v34 + 533) = *(_BYTE *)(i + 5164);
            *(_BYTE *)(a1 + 536 * v34 + 535) = -1;
            if ( *(_DWORD *)(i + 5104) )
            {
              for ( j = 0; ; ++j )
              {
                v17 = rf_receiver_get_first_dword(unk_6FC3E8);
                if ( j >= v17 )
                  break;
                v18 = (_DWORD *)sub_552200(unk_6FC3E8, j);
                if ( *(_DWORD *)(i + 5104) == *v18 )
                {
                  *(_BYTE *)(a1 + 536 * v34 + 535) = j;
                  break;
                }
              }
            }
            ++v34;
          }
        }
      }
    }
  }
  *a2 = v34;
  result = v31;
  *a4 = v31;
  return result;
}

