// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004305D0 sub_4305D0
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Initializes class prop IDs from the supplied model only when class+0x724 bit0x20000000 is clear and the handle is nonzero. Queries primary_weapon_1, then 2, etc; appends nonnegative IDs to class+0x1D4 until the FIRST missing name. Thus 420020 slot0 comes from primary_weapon_1 with the model-kind lookup semantics. No hand_right, bind-pose or cached-render fallback.
int __cdecl sub_4305D0(const void **a1, int a2, char a3)
{
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  char *v8; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  char *v12; // eax
  char *v13; // eax
  const char *v14; // eax
  char *v15; // eax
  char *v16; // eax
  int first_dword; // esi
  const char *v18; // eax
  std::exception *v19; // [esp+8h] [ebp-1F8h]
  _DWORD *v20; // [esp+10h] [ebp-1F0h]
  std::exception *v21; // [esp+18h] [ebp-1E8h]
  _DWORD *v22; // [esp+20h] [ebp-1E0h]
  std::exception *v23; // [esp+28h] [ebp-1D8h]
  _DWORD *v24; // [esp+30h] [ebp-1D0h]
  std::exception *v25; // [esp+38h] [ebp-1C8h]
  _DWORD *v26; // [esp+40h] [ebp-1C0h]
  std::exception *v27; // [esp+48h] [ebp-1B8h]
  _DWORD *v28; // [esp+50h] [ebp-1B0h]
  std::exception *v29; // [esp+58h] [ebp-1A8h]
  _DWORD *v30; // [esp+60h] [ebp-1A0h]
  std::exception *v31; // [esp+68h] [ebp-198h]
  _DWORD *v32; // [esp+70h] [ebp-190h]
  std::exception *v33; // [esp+78h] [ebp-188h]
  _DWORD *v34; // [esp+80h] [ebp-180h]
  std::exception *v35; // [esp+88h] [ebp-178h]
  _DWORD *v36; // [esp+90h] [ebp-170h]
  std::exception *v37; // [esp+98h] [ebp-168h]
  _DWORD *v38; // [esp+A0h] [ebp-160h]
  std::exception *v39; // [esp+A8h] [ebp-158h]
  _DWORD *v40; // [esp+B0h] [ebp-150h]
  std::exception *v41; // [esp+B8h] [ebp-148h]
  _DWORD *v42; // [esp+C0h] [ebp-140h]
  std::exception *v43; // [esp+C8h] [ebp-138h]
  _DWORD *v44; // [esp+D0h] [ebp-130h]
  std::exception *v45; // [esp+D8h] [ebp-128h]
  _DWORD *v46; // [esp+E0h] [ebp-120h]
  _BYTE v47[8]; // [esp+ECh] [ebp-114h] BYREF
  _BYTE v48[8]; // [esp+F4h] [ebp-10Ch] BYREF
  _BYTE v49[8]; // [esp+FCh] [ebp-104h] BYREF
  _DWORD v50[2]; // [esp+104h] [ebp-FCh] BYREF
  _BYTE v51[8]; // [esp+10Ch] [ebp-F4h] BYREF
  _DWORD v52[2]; // [esp+114h] [ebp-ECh] BYREF
  _BYTE v53[8]; // [esp+11Ch] [ebp-E4h] BYREF
  _BYTE v54[8]; // [esp+124h] [ebp-DCh] BYREF
  _BYTE v55[8]; // [esp+12Ch] [ebp-D4h] BYREF
  _DWORD v56[2]; // [esp+134h] [ebp-CCh] BYREF
  _BYTE v57[8]; // [esp+13Ch] [ebp-C4h] BYREF
  _DWORD v58[2]; // [esp+144h] [ebp-BCh] BYREF
  _BYTE v59[8]; // [esp+14Ch] [ebp-B4h] BYREF
  _DWORD v60[2]; // [esp+154h] [ebp-ACh] BYREF
  _BYTE v61[8]; // [esp+15Ch] [ebp-A4h] BYREF
  _DWORD v62[2]; // [esp+164h] [ebp-9Ch] BYREF
  _BYTE v63[8]; // [esp+16Ch] [ebp-94h] BYREF
  _DWORD v64[2]; // [esp+174h] [ebp-8Ch] BYREF
  _BYTE v65[8]; // [esp+17Ch] [ebp-84h] BYREF
  _DWORD v66[2]; // [esp+184h] [ebp-7Ch] BYREF
  _BYTE v67[8]; // [esp+18Ch] [ebp-74h] BYREF
  _DWORD v68[2]; // [esp+194h] [ebp-6Ch] BYREF
  _BYTE v69[8]; // [esp+19Ch] [ebp-64h] BYREF
  _DWORD v70[2]; // [esp+1A4h] [ebp-5Ch] BYREF
  _BYTE v71[8]; // [esp+1ACh] [ebp-54h] BYREF
  _DWORD v72[2]; // [esp+1B4h] [ebp-4Ch] BYREF
  _BYTE v73[8]; // [esp+1BCh] [ebp-44h] BYREF
  _DWORD v74[2]; // [esp+1C4h] [ebp-3Ch] BYREF
  int v75; // [esp+1D0h] [ebp-30h]
  int v76; // [esp+1D4h] [ebp-2Ch]
  int i; // [esp+1D8h] [ebp-28h]
  int v78; // [esp+1DCh] [ebp-24h]
  int definition_pointer; // [esp+1E0h] [ebp-20h]
  int v80[2]; // [esp+1E4h] [ebp-1Ch] BYREF
  int v81; // [esp+1ECh] [ebp-14h]
  int node_adapter; // [esp+1F0h] [ebp-10h]
  int v83; // [esp+1FCh] [ebp-4h]

  if ( !a2 )
    return -1;
  rf_string_construct_empty(v80);
  v83 = 0;
  if ( ((unsigned int)a1[457] & 0x20000000) != 0 )
  {
    v83 = -1;
    rf_string_destroy_buffer(v80);
    return 0;
  }
  else
  {
    a1[1269] = (const void *)rf_model_handle_find_node_adapter(a2, "corpse_carry");
    if ( a1[1269] == (const void *)-1 )
      a1[1269] = (const void *)rf_model_handle_find_node_adapter(a2, (char *)off_6329A8);
    rf_string_assign_from_cstr(v80, "primary_weapon_");
    v81 = 0;
    v46 = rf_string_format_int32_decimal(v74, 1);
    LOBYTE(v83) = 1;
    v45 = (std::exception *)rf_string_concat_two_objects(v73, v80, (int)v46);
    LOBYTE(v83) = 2;
    v4 = (char *)rf_string_object_c_str_or_empty(v45);
    node_adapter = rf_model_handle_find_node_adapter(a2, v4);
    LOBYTE(v83) = 1;
    rf_string_destroy_buffer(v73);
    LOBYTE(v83) = 0;
    rf_string_destroy_buffer(v74);
    while ( node_adapter >= 0 )
    {
      rf_inline_dword2_append_unless_exact_full(a1 + 117, node_adapter);
      v44 = rf_string_format_int32_decimal(v72, ++v81 + 1);
      LOBYTE(v83) = 3;
      v43 = (std::exception *)rf_string_concat_two_objects(v71, v80, (int)v44);
      LOBYTE(v83) = 4;
      v5 = (char *)rf_string_object_c_str_or_empty(v43);
      node_adapter = rf_model_handle_find_node_adapter(a2, v5);
      LOBYTE(v83) = 3;
      rf_string_destroy_buffer(v71);
      LOBYTE(v83) = 0;
      rf_string_destroy_buffer(v72);
    }
    rf_pointer_array_clear_count_keep_storage(a1 + 120);
    rf_string_assign_from_cstr(v80, "secondary_weapon_");
    v81 = 0;
    v42 = rf_string_format_int32_decimal(v70, 1);
    LOBYTE(v83) = 5;
    v41 = (std::exception *)rf_string_concat_two_objects(v69, v80, (int)v42);
    LOBYTE(v83) = 6;
    v6 = (char *)rf_string_object_c_str_or_empty(v41);
    node_adapter = rf_model_handle_find_node_adapter(a2, v6);
    LOBYTE(v83) = 5;
    rf_string_destroy_buffer(v69);
    LOBYTE(v83) = 0;
    rf_string_destroy_buffer(v70);
    while ( node_adapter >= 0 )
    {
      rf_inline_dword2_append_unless_exact_full(a1 + 120, node_adapter);
      v40 = rf_string_format_int32_decimal(v68, ++v81 + 1);
      LOBYTE(v83) = 7;
      v39 = (std::exception *)rf_string_concat_two_objects(v67, v80, (int)v40);
      LOBYTE(v83) = 8;
      v7 = (char *)rf_string_object_c_str_or_empty(v39);
      node_adapter = rf_model_handle_find_node_adapter(a2, v7);
      LOBYTE(v83) = 7;
      rf_string_destroy_buffer(v67);
      LOBYTE(v83) = 0;
      rf_string_destroy_buffer(v68);
    }
    rf_string_assign_from_cstr(v80, "primary_");
    v81 = 0;
    v38 = rf_string_format_int32_decimal(v66, 1);
    LOBYTE(v83) = 9;
    v37 = (std::exception *)rf_string_concat_two_objects(v65, v80, (int)v38);
    LOBYTE(v83) = 10;
    v8 = (char *)rf_string_object_c_str_or_empty(v37);
    node_adapter = rf_model_handle_find_node_adapter(a2, v8);
    LOBYTE(v83) = 9;
    rf_string_destroy_buffer(v65);
    LOBYTE(v83) = 0;
    rf_string_destroy_buffer(v66);
    while ( node_adapter >= 0 )
    {
      rf_inline_dword2_append_unless_exact_full(a1 + 111, node_adapter);
      v36 = rf_string_format_int32_decimal(v64, ++v81 + 1);
      LOBYTE(v83) = 11;
      v35 = (std::exception *)rf_string_concat_two_objects(v63, v80, (int)v36);
      LOBYTE(v83) = 12;
      v9 = (char *)rf_string_object_c_str_or_empty(v35);
      node_adapter = rf_model_handle_find_node_adapter(a2, v9);
      LOBYTE(v83) = 11;
      rf_string_destroy_buffer(v63);
      LOBYTE(v83) = 0;
      rf_string_destroy_buffer(v64);
    }
    rf_string_assign_from_cstr(v80, "secondary_");
    v81 = 0;
    v34 = rf_string_format_int32_decimal(v62, 1);
    LOBYTE(v83) = 13;
    v33 = (std::exception *)rf_string_concat_two_objects(v61, v80, (int)v34);
    LOBYTE(v83) = 14;
    v10 = (char *)rf_string_object_c_str_or_empty(v33);
    node_adapter = rf_model_handle_find_node_adapter(a2, v10);
    LOBYTE(v83) = 13;
    rf_string_destroy_buffer(v61);
    LOBYTE(v83) = 0;
    rf_string_destroy_buffer(v62);
    while ( node_adapter >= 0 )
    {
      rf_inline_dword2_append_unless_exact_full(a1 + 114, node_adapter);
      v32 = rf_string_format_int32_decimal(v60, ++v81 + 1);
      LOBYTE(v83) = 15;
      v31 = (std::exception *)rf_string_concat_two_objects(v59, v80, (int)v32);
      LOBYTE(v83) = 16;
      v11 = (char *)rf_string_object_c_str_or_empty(v31);
      node_adapter = rf_model_handle_find_node_adapter(a2, v11);
      LOBYTE(v83) = 15;
      rf_string_destroy_buffer(v59);
      LOBYTE(v83) = 0;
      rf_string_destroy_buffer(v60);
    }
    a1[61] = (const void *)rf_model_handle_find_node_adapter(a2, "muzzle_1");
    a1[62] = (const void *)rf_model_handle_find_node_adapter(a2, "led_1");
    a1[441] = (const void *)rf_model_handle_find_node_adapter(a2, "helmet");
    a1[442] = (const void *)rf_model_handle_find_node_adapter(a2, "shell_eject_1");
    a1[443] = (const void *)rf_model_handle_find_node_adapter(a2, "hand_left");
    a1[444] = (const void *)rf_model_handle_find_node_adapter(a2, "hand_right");
    rf_string_assign_from_cstr(v80, "thruster_");
    v81 = 1;
    v30 = rf_string_format_int32_decimal(v58, 1);
    LOBYTE(v83) = 17;
    v29 = (std::exception *)rf_string_concat_two_objects(v57, v80, (int)v30);
    LOBYTE(v83) = 18;
    v12 = (char *)rf_string_object_c_str_or_empty(v29);
    node_adapter = rf_model_handle_find_node_adapter(a2, v12);
    LOBYTE(v83) = 17;
    rf_string_destroy_buffer(v57);
    LOBYTE(v83) = 0;
    rf_string_destroy_buffer(v58);
    while ( node_adapter >= 0 )
    {
      rf_inline_dword_array32_append(a1 + 124, node_adapter);
      v28 = rf_string_format_int32_decimal(v56, ++v81);
      LOBYTE(v83) = 19;
      v27 = (std::exception *)rf_string_concat_two_objects(v55, v80, (int)v28);
      LOBYTE(v83) = 20;
      v13 = (char *)rf_string_object_c_str_or_empty(v27);
      node_adapter = rf_model_handle_find_node_adapter(a2, v13);
      LOBYTE(v83) = 19;
      rf_string_destroy_buffer(v55);
      LOBYTE(v83) = 0;
      rf_string_destroy_buffer(v56);
    }
    if ( rf_receiver_get_first_dword(a1 + 124) < (int)a1[413] )
    {
      v26 = rf_string_concat_cstr_object(v54, "Entity \"", a1);
      LOBYTE(v83) = 21;
      v25 = (std::exception *)rf_string_concat_object_cstr(
                                v53,
                                v26,
                                "\" has too many thruster effects specified in entity.tbl.  Remove some, or add more thru"
                                "ster_n points to the model.");
      LOBYTE(v83) = 22;
      v14 = rf_string_object_c_str_or_empty(v25);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp", 3983, v14);
    }
    rf_string_assign_from_cstr(v80, "corona_");
    v81 = 1;
    v24 = rf_string_format_int32_decimal(v52, 1);
    LOBYTE(v83) = 23;
    v23 = (std::exception *)rf_string_concat_two_objects(v51, v80, (int)v24);
    LOBYTE(v83) = 24;
    v15 = (char *)rf_string_object_c_str_or_empty(v23);
    node_adapter = rf_model_handle_find_node_adapter(a2, v15);
    LOBYTE(v83) = 23;
    rf_string_destroy_buffer(v51);
    LOBYTE(v83) = 0;
    rf_string_destroy_buffer(v52);
    while ( node_adapter >= 0 )
    {
      rf_inline_dword8_append_unless_exact_full(a1 + 414, node_adapter);
      v22 = rf_string_format_int32_decimal(v50, ++v81);
      LOBYTE(v83) = 25;
      v21 = (std::exception *)rf_string_concat_two_objects(v49, v80, (int)v22);
      LOBYTE(v83) = 26;
      v16 = (char *)rf_string_object_c_str_or_empty(v21);
      node_adapter = rf_model_handle_find_node_adapter(a2, v16);
      LOBYTE(v83) = 25;
      rf_string_destroy_buffer(v49);
      LOBYTE(v83) = 0;
      rf_string_destroy_buffer(v50);
    }
    first_dword = rf_receiver_get_first_dword(a1 + 414);
    if ( first_dword != rf_receiver_get_first_dword(a1 + 423) )
    {
      v20 = rf_string_concat_cstr_object(v48, "Entity \"", a1);
      LOBYTE(v83) = 27;
      v19 = (std::exception *)rf_string_concat_object_cstr(
                                v47,
                                v20,
                                "\" has an incorrect number coronas specified in entity.tbl.  Make sure the number of pro"
                                "p points matches the number of table entries.");
      LOBYTE(v83) = 28;
      v18 = rf_string_object_c_str_or_empty(v19);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp", 3997, v18);
    }
    if ( a3 )
    {
      definition_pointer = rf_model_handle_get_definition_pointer(a2);
      if ( definition_pointer )
      {
        v75 = -1;
        v78 = -1;
        for ( i = 0; i < *(_DWORD *)(definition_pointer + 72); ++i )
        {
          if ( rf_cstring_find_first_substring((char *)(definition_pointer + 76 * i + 76), "spine") )
          {
            if ( v75 != -1 )
            {
              v78 = i;
              break;
            }
            v75 = i;
          }
        }
        v76 = -1;
        for ( i = 0; i < *(_DWORD *)(definition_pointer + 72); ++i )
        {
          if ( rf_cstring_find_first_substring((char *)(definition_pointer + 76 * i + 76), "head") )
          {
            v76 = i;
            break;
          }
        }
        if ( *(_DWORD *)(definition_pointer + 76 * v78 + 148) != v75 )
        {
          i = v78;
          v78 = v75;
          v75 = i;
        }
        a1[1270] = (const void *)v75;
        a1[1271] = (const void *)v78;
        a1[1272] = (const void *)v76;
      }
    }
    else
    {
      a1[1270] = (const void *)-1;
      a1[1271] = (const void *)-1;
      a1[1272] = (const void *)-1;
    }
    v83 = -1;
    rf_string_destroy_buffer(v80);
    return 0;
  }
}

