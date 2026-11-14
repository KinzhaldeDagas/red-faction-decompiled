// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049EE40 rf_multiplayer_notification_enqueue
// UNREALRED VERIFIED [lan-killfeed-20261028] All nine death-notification callsites in0x429820 supply empty player-prefix and a fully assembled message. Thus style4 is a complete white death row and style5 is a complete default-green row, with ordinary feed wrapping/hold/line-budget semantics. This is a local presentation queue, not an attacker attribution or score authority.
void __cdecl rf_multiplayer_notification_enqueue(int a1, int a2, int a3, int a4)
{
  const char *v4; // eax
  const char *v5; // eax
  unsigned __int8 *v6; // eax
  unsigned int v7; // eax
  unsigned __int8 *v8; // eax
  unsigned int v9; // eax
  const char *v10; // eax
  int v11; // [esp-8h] [ebp-170h]
  int v12; // [esp+4h] [ebp-164h]
  _DWORD *v13; // [esp+Ch] [ebp-15Ch]
  int v14; // [esp+14h] [ebp-154h]
  std::exception *v15; // [esp+18h] [ebp-150h]
  void *v16; // [esp+20h] [ebp-148h]
  _DWORD *v17; // [esp+28h] [ebp-140h]
  _DWORD *v18; // [esp+30h] [ebp-138h]
  int *v19; // [esp+38h] [ebp-130h]
  void *v20; // [esp+40h] [ebp-128h]
  void *v21; // [esp+48h] [ebp-120h]
  int *v22; // [esp+50h] [ebp-118h]
  _DWORD *v23; // [esp+58h] [ebp-110h]
  int *v24; // [esp+60h] [ebp-108h]
  _DWORD v25[2]; // [esp+6Ch] [ebp-FCh] BYREF
  _BYTE v26[8]; // [esp+74h] [ebp-F4h] BYREF
  _BYTE v27[8]; // [esp+7Ch] [ebp-ECh] BYREF
  _DWORD v28[2]; // [esp+84h] [ebp-E4h] BYREF
  _DWORD v29[2]; // [esp+8Ch] [ebp-DCh] BYREF
  _BYTE v30[8]; // [esp+94h] [ebp-D4h] BYREF
  _BYTE v31[8]; // [esp+9Ch] [ebp-CCh] BYREF
  _BYTE v32[8]; // [esp+A4h] [ebp-C4h] BYREF
  _BYTE v33[8]; // [esp+ACh] [ebp-BCh] BYREF
  _BYTE v34[8]; // [esp+B4h] [ebp-B4h] BYREF
  _BYTE v35[8]; // [esp+BCh] [ebp-ACh] BYREF
  _DWORD v36[2]; // [esp+C4h] [ebp-A4h] BYREF
  int v37[2]; // [esp+CCh] [ebp-9Ch] BYREF
  int v38[2]; // [esp+D4h] [ebp-94h] BYREF
  int max_pixel_width; // [esp+DCh] [ebp-8Ch]
  unsigned int v40; // [esp+E0h] [ebp-88h]
  char v41; // [esp+E7h] [ebp-81h]
  _DWORD v42[2]; // [esp+E8h] [ebp-80h] BYREF
  _BYTE v43[8]; // [esp+F0h] [ebp-78h] BYREF
  int v44; // [esp+F8h] [ebp-70h]
  int v45; // [esp+FCh] [ebp-6Ch]
  int line_lengths[8]; // [esp+100h] [ebp-68h] BYREF
  int v47[2]; // [esp+120h] [ebp-48h] BYREF
  int line_offsets; // [esp+128h] [ebp-40h] BYREF
  _DWORD v49[7]; // [esp+12Ch] [ebp-3Ch]
  int i; // [esp+148h] [ebp-20h]
  int j; // [esp+14Ch] [ebp-1Ch]
  int v52; // [esp+150h] [ebp-18h] BYREF
  int v53; // [esp+154h] [ebp-14h]
  int v54; // [esp+158h] [ebp-10h] BYREF
  int v55; // [esp+164h] [ebp-4h]

  v55 = 1;
  if ( rf_string_equals_case_insensitive((int)&a1, (char *)&byte_63A463) )
  {
    rf_string_destroy_buffer(&a1);
    v55 = -1;
    rf_string_destroy_buffer(&a4);
  }
  else
  {
    for ( i = rf_string_find_case_insensitive(&a1, "%", 0); i != -1; i = rf_string_find_case_insensitive(&a1, "%", 0) )
      *rf_string_byte_pointer_or_zero_sentinel(&a1, i) = 32;
    if ( byte_704E83 == 1 )
    {
      rf_string_construct_from_cstr(v38, (char *)&byte_63A47A);
      LOBYTE(v55) = 2;
      rf_string_construct_from_cstr(v37, (char *)&byte_63A47B);
      LOBYTE(v55) = 3;
      switch ( a3 )
      {
        case 0:
          rf_string_assign_from_cstr(v38, "[$Red]");
          rf_string_assign_from_cstr(v37, "[$White]");
          break;
        case 1:
          rf_string_assign_from_cstr(v38, "[$Blue]");
          rf_string_assign_from_cstr(v37, "[$White]");
          break;
        case 2:
          rf_string_assign_from_cstr(v38, "[$Red]");
          rf_string_assign_from_cstr(v37, "[$Red]");
          break;
        case 3:
          rf_string_assign_from_cstr(v38, "[$Blue]");
          rf_string_assign_from_cstr(v37, "[$Blue]");
          break;
        case 4:
          rf_string_assign_from_cstr(v38, "[$White]");
          rf_string_assign_from_cstr(v37, "[$White]");
          break;
        case 5:
          rf_string_assign_from_cstr(v38, (char *)&byte_63A495);
          rf_string_assign_from_cstr(v37, (char *)&byte_63A496);
          break;
        default:
          break;
      }
      rf_string_construct_empty(v36);
      LOBYTE(v55) = 4;
      if ( rf_rf_string_not_equals_cstring_case_insensitive((int)&a4, (char *)&byte_63A497) )
      {
        v24 = (int *)rf_string_concat_two_objects(v35, v38, (int)&a4);
        LOBYTE(v55) = 5;
        v23 = rf_string_concat_two_objects(v34, v24, (int)v37);
        LOBYTE(v55) = 6;
        v22 = (int *)rf_string_concat_object_cstr(v33, v23, " ");
        LOBYTE(v55) = 7;
        v21 = rf_string_concat_two_objects(v32, v22, (int)&a1);
        LOBYTE(v55) = 8;
        rf_string_assign_from_object(v36, (int)v21);
        LOBYTE(v55) = 7;
        rf_string_destroy_buffer(v32);
        LOBYTE(v55) = 6;
        rf_string_destroy_buffer(v33);
        LOBYTE(v55) = 5;
        rf_string_destroy_buffer(v34);
        LOBYTE(v55) = 4;
        rf_string_destroy_buffer(v35);
      }
      else
      {
        v20 = rf_string_concat_two_objects(v31, v37, (int)&a1);
        LOBYTE(v55) = 9;
        rf_string_assign_from_object(v36, (int)v20);
        LOBYTE(v55) = 4;
        rf_string_destroy_buffer(v31);
      }
      v4 = rf_string_object_c_str_or_empty(v36);
      rf_console_output_append_text_lines(v4, nullptr);
      LOBYTE(v55) = 3;
      rf_string_destroy_buffer(v36);
      LOBYTE(v55) = 2;
      rf_string_destroy_buffer(v37);
      LOBYTE(v55) = 1;
      rf_string_destroy_buffer(v38);
      LOBYTE(v55) = 0;
      rf_string_destroy_buffer(&a1);
      v55 = -1;
      rf_string_destroy_buffer(&a4);
    }
    else
    {
      v19 = (int *)rf_string_concat_object_cstr(v30, &a4, " ");
      LOBYTE(v55) = 10;
      rf_string_concat_two_objects(v43, v19, (int)&a1);
      LOBYTE(v55) = 12;
      rf_string_destroy_buffer(v30);
      v5 = rf_string_object_c_str_or_empty(v43);
      rf_console_output_append_text_lines(v5, &dword_77FE64);
      v41 = 0;
      max_pixel_width = rf_renderer_get_physical_screen_width() - 320;
      v6 = (unsigned __int8 *)rf_string_object_c_str_or_empty(&a4);
      rf_font_measure_text_extent(&v54, &v52, v6, -1, -1);
      if ( v54 >= max_pixel_width )
      {
        while ( v54 >= max_pixel_width )
        {
          v7 = rf_string_length_from_cstr((const char **)&a4);
          v18 = rf_string_substring_inclusive(&a4, v29, 0, v7 - 2);
          LOBYTE(v55) = 13;
          rf_string_assign_from_object(&a4, (int)v18);
          LOBYTE(v55) = 12;
          rf_string_destroy_buffer(v29);
          v8 = (unsigned __int8 *)rf_string_object_c_str_or_empty(&a4);
          rf_font_measure_text_extent(&v54, &v52, v8, -1, -1);
        }
        v9 = rf_string_length_from_cstr((const char **)&a4);
        v17 = rf_string_substring_inclusive(&a4, v28, 0, v9 - 5);
        LOBYTE(v55) = 14;
        v16 = rf_string_concat_object_cstr(v27, v17, "...: ");
        LOBYTE(v55) = 15;
        rf_string_assign_from_object(&a4, (int)v16);
        LOBYTE(v55) = 14;
        rf_string_destroy_buffer(v27);
        LOBYTE(v55) = 12;
        rf_string_destroy_buffer(v28);
        v41 = 1;
      }
      v40 = rf_string_length_from_cstr((const char **)&a4);
      v12 = dword_663050;
      v11 = max_pixel_width;
      v15 = (std::exception *)rf_string_concat_two_objects(v26, &a4, (int)&a1);
      LOBYTE(v55) = 16;
      v10 = rf_string_object_c_str_or_empty(v15);
      v44 = rf_text_wrap_into_offset_length_arrays(line_lengths, &line_offsets, v10, v11, 8, 0, v12);
      LOBYTE(v55) = 12;
      rf_string_destroy_buffer(v26);
      if ( v44 <= 1 || v49[0] != v40 || v41 )
      {
        for ( j = 7; j >= v44; --j )
        {
          rf_string_assign_from_object(
            &rf_multiplayer_notification_prefix_rows[20 * j],
            (int)&rf_multiplayer_notification_prefix_rows[20 * (j - v44)]);
          rf_string_assign_from_object(
            (_DWORD *)&rf_multiplayer_notification_suffix_rows + 5 * j,
            (int)&rf_multiplayer_notification_suffix_rows + 20 * (j - v44));
          rf_multiplayer_notification_style_rows[5 * j] = rf_multiplayer_notification_style_rows[5 * (j - v44)];
        }
        rf_string_construct_empty(v42);
        LOBYTE(v55) = 17;
        rf_string_construct_empty(v47);
        LOBYTE(v55) = 18;
        for ( j = 0; j < v44; ++j )
        {
          v53 = v49[j - 1];
          if ( j == v44 - 1 )
            v14 = -1;
          else
            v14 = v49[j] - v40 - 1;
          v45 = v14;
          if ( j <= 0 )
          {
            if ( v41 && v45 == -1 )
              v45 = 0;
          }
          else
          {
            v53 -= v40;
          }
          if ( v53 == v45 && j <= 0 )
          {
            rf_string_assign_from_cstr(v42, (char *)&byte_63A4A9);
          }
          else
          {
            v13 = rf_string_substring_inclusive(&a1, v25, v53, v45);
            LOBYTE(v55) = 19;
            rf_string_assign_from_object(v42, (int)v13);
            LOBYTE(v55) = 18;
            rf_string_destroy_buffer(v25);
          }
          rf_string_assign_from_object(&rf_multiplayer_notification_prefix_rows[20 * (v44 - j) - 20], (int)&a4);
          rf_string_assign_from_object((_DWORD *)&rf_multiplayer_notification_suffix_rows + 5 * (v44 - j) - 5, (int)v42);
          rf_multiplayer_notification_style_rows[5 * (v44 - j) - 5] = a3;
          ++rf_multiplayer_notification_rendered_row_count;
          rf_string_assign_from_cstr(&a4, (char *)&byte_63A4AA);
        }
        rf_replicator_arm_milliseconds(&rf_multiplayer_notification_hold_timer, 8000);
        LOBYTE(v55) = 17;
        rf_string_destroy_buffer(v47);
        LOBYTE(v55) = 12;
        rf_string_destroy_buffer(v42);
        LOBYTE(v55) = 1;
        rf_string_destroy_buffer(v43);
        LOBYTE(v55) = 0;
        rf_string_destroy_buffer(&a1);
        v55 = -1;
        rf_string_destroy_buffer(&a4);
      }
      else
      {
        rf_gamesound_play_event(2, 0, 0.0, 1.0);
        LOBYTE(v55) = 1;
        rf_string_destroy_buffer(v43);
        LOBYTE(v55) = 0;
        rf_string_destroy_buffer(&a1);
        v55 = -1;
        rf_string_destroy_buffer(&a4);
      }
    }
  }
}

