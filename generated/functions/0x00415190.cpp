// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415190 rf_clutter_runtime_create
// UNREALRED VERIFIED [mission-when-dead-targets-20261013] Third argument is parent/owner handle, forwarded as the third argument of 0x4B7E00 and stored at NEW common object+0x30. It is NOT a requested replacement handle. A corpse clutter created from 0x414950 therefore has a fresh slot/generation handle at +0x2C; keeping its visual cannot keep the old When_Dead source target alive.
// UNREALRED VERIFIED [clutter-clock-20261029] Every successful runtime clutter creation arms class-definition+0x70 deadline with duration0 at4155EB, independently of the object corpse deadline+0x2B4 reset. Creating another object of the same class re-arms the shared explosion gate immediately; this is not a once-per-level class initialization.
_DWORD *__cdecl rf_clutter_runtime_create(int a1, char *Source, int a3, float *source, float *a5, int a6)
{
  int v7; // eax
  int v8; // eax
  char *v9; // eax
  int index_by_name; // eax
  int first_dword; // eax
  _DWORD *v12; // eax
  char *v13; // eax
  int v14; // eax
  int *v15; // eax
  int v16; // eax
  float *v17; // [esp-4h] [ebp-128h]
  int v18; // [esp+0h] [ebp-124h]
  char *v19; // [esp+4h] [ebp-120h]
  int v20; // [esp+4h] [ebp-120h]
  int v21; // [esp+10h] [ebp-114h]
  void *v22; // [esp+18h] [ebp-10Ch]
  const void **v23; // [esp+24h] [ebp-100h]
  _DWORD *v24; // [esp+30h] [ebp-F4h]
  _BYTE v25[8]; // [esp+34h] [ebp-F0h] BYREF
  _DWORD v26[2]; // [esp+3Ch] [ebp-E8h] BYREF
  float copy_result[3]; // [esp+48h] [ebp-DCh] BYREF
  int v28; // [esp+54h] [ebp-D0h]
  int v29; // [esp+58h] [ebp-CCh]
  int node_adapter; // [esp+5Ch] [ebp-C8h]
  _DWORD v31[2]; // [esp+60h] [ebp-C4h] BYREF
  int v32; // [esp+68h] [ebp-BCh]
  int v33; // [esp+6Ch] [ebp-B8h]
  int v34; // [esp+70h] [ebp-B4h]
  char *v35; // [esp+74h] [ebp-B0h]
  void *v36[38]; // [esp+78h] [ebp-ACh] BYREF
  int i; // [esp+110h] [ebp-14h]
  _DWORD *v38; // [esp+114h] [ebp-10h]
  int v39; // [esp+120h] [ebp-4h]

  if ( a1 < 0 || a1 > unk_666B60 )
    return nullptr;
  v35 = &byte_667000[232 * a1];
  rf_object_setup152_construct_members((char *)v36);
  v39 = 0;
  memset(v36, 0, sizeof(v36));
  v36[0] = (void *)rf_string_object_c_str_or_empty(v35 + 8);
  v36[1] = *((void **)v35 + 14);
  v36[2] = nullptr;
  rf_vector_copy((float *)&v36[15], copy_result, source);
  rf_matrix3_copy((float *)&v36[18], a5);
  v36[4] = (void *)(unsigned __int8)v35[76];
  v36[33] = *((void **)v35 + 16);
  v36[37] = nullptr;
  if ( (*((_DWORD *)v35 + 29) & 6) != 0 )
    v36[37] = (void *)((int)v36[37] | 0x20);
  v33 = 0;
  if ( a1 == unk_666B64 )
    v33 |= 0x100000u;
  v38 = (_DWORD *)rf_object_create(4, -1, a3, (int)v36, v33, 0);
  if ( v38 )
  {
    if ( (*((_DWORD *)v35 + 29) & 0x20) != 0 )
      v38[31] |= 0x100000u;
    if ( (*((_DWORD *)v35 + 29) & 2) != 0 )
      v38[31] |= 0x40000u;
    v38[165] = v35;
    v38[166] = a1;
    rf_string_assign_from_cstr(v38 + 6, Source);
    if ( rf_string_equals_case_insensitive((int)(v38 + 6), (char *)byte_6312C6) )
      rf_string_assign_from_object(v38 + 6, v38[165]);
    *((_BYTE *)v38 + 716) = 0;
    if ( *((float *)v35 + 15) >= 0.0 )
    {
      *((float *)v38 + 13) = *((float *)v35 + 15);
    }
    else
    {
      *((float *)v38 + 13) = 100.0;
      v38[31] |= 4u;
    }
    *((float *)v38 + 14) = 0.0;
    if ( *((int *)v35 + 20) < 0 )
    {
      v38[168] = -1;
    }
    else
    {
      v17 = (float *)(v38 + 15);
      v7 = rf_foley_choose_random_sound(*((_DWORD *)v35 + 20));
      v8 = rf_gamesound_play_positional_event(v7, v17, 1.0, (int)&unk_17F10B0, 0);
      v38[168] = v8;
    }
    if ( (*((_DWORD *)v35 + 29) & 1) != 0 )
      v38[31] |= 0x1000u;
    if ( (int)rf_string_length_from_cstr((const char **)v35 + 4) > 0 )
    {
      v9 = (char *)rf_string_object_c_str_or_empty(v35 + 16);
      index_by_name = rf_clutter_class_find_index_by_name(v9);
      v38[167] = index_by_name;
    }
    else
    {
      v38[167] = -1;
    }
    rf_replicator_reset(v38 + 169);
    v38[170] = -1;
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(v38[165] + 40));
      if ( i >= first_dword )
        break;
      if ( *(int *)sub_552200((_DWORD *)(v38[165] + 40), i) > -1 )
      {
        v19 = (char *)(v38 + 15);
        v18 = rf_receiver_get_first_dword(v38);
        v12 = (_DWORD *)sub_552200((_DWORD *)(v38[165] + 40), i);
        v32 = rf_particle_emitter_create(v38[11], (float *)dword_867800[*v12], v18, (int)v19, 1);
        if ( v32 )
        {
          *(_DWORD *)(v32 + 336) = v38[154];
          v38[154] = v32;
        }
      }
    }
    if ( *(float *)(v38[165] + 52) <= 0.0 )
      rf_replicator_reset(v38 + 172);
    else
      rf_replicator_arm_milliseconds(v38 + 172, (int)(*(float *)(v38[165] + 52) * 1000.0 + 0.5));
    rf_replicator_arm_milliseconds((int *)(v38[165] + 112), 0);
    rf_replicator_reset(v38 + 173);
    v38[174] = 0;
    v38[175] = -1;
    v38[180] = -1;
    if ( *((_DWORD *)v35 + 31) != -1 && (*((_DWORD *)v35 + 29) & 0x400) == 0 )
    {
      v29 = 1;
      rf_string_construct_empty(v31);
      LOBYTE(v39) = 1;
      while ( 1 )
      {
        v23 = (const void **)rf_string_format_int32_decimal(v26, v29);
        LOBYTE(v39) = 2;
        v22 = rf_string_concat_cstr_object(v25, "corona_", v23);
        LOBYTE(v39) = 3;
        rf_string_assign_from_object(v31, (int)v22);
        ++v29;
        LOBYTE(v39) = 2;
        rf_string_destroy_buffer(v25);
        LOBYTE(v39) = 1;
        rf_string_destroy_buffer(v26);
        v13 = (char *)rf_string_object_c_str_or_empty(v31);
        node_adapter = rf_model_handle_find_node_adapter(v38[32], v13);
        if ( node_adapter < 0 )
          break;
        rf_inline_dword_array4_append_unchecked((_DWORD *)v35 + 33, node_adapter);
      }
      *((_DWORD *)v35 + 29) |= 0x400u;
      LOBYTE(v39) = 0;
      rf_string_destroy_buffer(v31);
    }
    for ( i = 0; ; ++i )
    {
      v14 = rf_receiver_get_first_dword(v35 + 132);
      if ( i >= v14 )
        break;
      v20 = *((_DWORD *)v35 + 31);
      v15 = (int *)rf_inline_dword_array4_element_address_unchecked(v35 + 132, i);
      rf_glare_create_attached_to_model_prop(v38[11], *v15, v20, 0);
    }
    v34 = rf_model_handle_find_node_adapter(v38[32], "corona_rod1");
    if ( v34 >= 0 )
    {
      v28 = rf_model_handle_find_node_adapter(v38[32], "corona_rod2");
      if ( v28 < 0 )
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\gamesrc\\clutter\\clutter.cpp",
          1664,
          "Clutter model had a corona_rod1 point but not a corona_rod2 point!");
      if ( *((int *)v35 + 32) >= 0 )
        rf_glare_create_between_model_props(v38[11], *((_DWORD *)v35 + 32), v34, v28);
    }
    if ( (*((_DWORD *)v35 + 29) & 0x10) != 0 && (*((_DWORD *)v35 + 29) & 0x800) == 0 )
    {
      v16 = rf_model_handle_find_node_adapter(v38[32], "light_prop");
      *((_DWORD *)v35 + 38) = v16;
      *((_DWORD *)v35 + 29) |= 0x800u;
    }
    if ( (*((_DWORD *)v35 + 29) & 8) != 0 )
      rf_monitor_create_record(v38[11], -1, *((_DWORD *)v35 + 56), *((_DWORD *)v35 + 57), 1);
    if ( *((_DWORD *)v35 + 22) != -1 )
      rf_vclip_preload_bitmap_and_vfx_stub(*((_DWORD *)v35 + 22));
    if ( (v38[106] & 0x20) != 0 && (v38[31] & 0x8000) == 0 )
      rf_collision_register_object_against_active_list((int)v38);
    v38[164] = unk_666FA8;
    v38[163] = &unk_666D18;
    *(_DWORD *)(unk_666FA8 + 652) = v38;
    unk_666FA8 = v38;
    ++unk_666B6C;
    *((_WORD *)v38 + 362) = -1;
    if ( a6 && dword_666B74 < 3200 )
    {
      *((_WORD *)v38 + 362) = dword_666B74;
      v21 = dword_666B74++;
      rf_bitset_set_bit_unchecked(dword_666FF0, v21, 1);
    }
    v24 = v38;
    v39 = -1;
    rf_object_setup152_destroy_array_backing(v36);
    return v24;
  }
  else
  {
    v39 = -1;
    rf_object_setup152_destroy_array_backing(v36);
    return nullptr;
  }
}

