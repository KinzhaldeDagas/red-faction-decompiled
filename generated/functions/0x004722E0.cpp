// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004722E0 rf_console_drop_item_command
// UNREALRED VERIFIED [item-pickups-20261028]: Processes shared console argument globals0x1809818/0x1809820. With item name resolves definition, obtains local-player view position, builds identity orientation and spawns item with active count, UID-1 and final flags1,0. For weapon definitions replaces quantity with weapon maximum. Prints dropped message, offsets spawn position by view direction*(radius+3), moves item through0x4BC330. Invalid name prints unrecongnized item type. Missing name sets help flag0x1809814; help prints usage and all definition names. Does not validate local-player pointer in this body.
void rf_console_drop_item_command()
{
  float *v0; // eax
  int v1; // eax
  const char *v2; // eax
  float *v3; // eax
  const char *v4; // eax
  float *v5; // [esp+Ch] [ebp-104h]
  float *v6; // [esp+10h] [ebp-100h]
  std::exception *v7; // [esp+24h] [ebp-ECh]
  float scalar; // [esp+2Ch] [ebp-E4h]
  std::exception *v9; // [esp+30h] [ebp-E0h]
  _DWORD *v10; // [esp+38h] [ebp-D8h]
  _BYTE v11[8]; // [esp+50h] [ebp-C0h] BYREF
  float scaled_result[3]; // [esp+58h] [ebp-B8h] BYREF
  _BYTE v13[8]; // [esp+64h] [ebp-ACh] BYREF
  _BYTE v14[8]; // [esp+6Ch] [ebp-A4h] BYREF
  float v15[3]; // [esp+74h] [ebp-9Ch] BYREF
  float v16[3]; // [esp+80h] [ebp-90h] BYREF
  float v17[3]; // [esp+8Ch] [ebp-84h] BYREF
  _BYTE v18[36]; // [esp+98h] [ebp-78h] BYREF
  int i; // [esp+BCh] [ebp-54h]
  float sum_result[3]; // [esp+C0h] [ebp-50h] BYREF
  float lhs[3]; // [esp+CCh] [ebp-44h] BYREF
  int v22; // [esp+D8h] [ebp-38h]
  _BYTE v23[24]; // [esp+DCh] [ebp-34h] BYREF
  float vector[3]; // [esp+F4h] [ebp-1Ch] BYREF
  int v25; // [esp+100h] [ebp-10h]
  int v26; // [esp+10Ch] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    if ( &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 == (char *)&unk_1809821 )
    {
      dword_1809814 = 1;
    }
    else
    {
      v25 = rf_item_definition_find_by_name(&MEMORY[0x1809820]);
      if ( v25 < 0 )
      {
        rf_console_output_append_text_lines("unrecongnized item type", nullptr);
      }
      else
      {
        rf_entity_view_copy_referenced_position(lhs, *(_DWORD *)(rf_local_fpgun_player + 196));
        rf_entity_view_copy_referenced_matrix_2016((int)v23, *(_DWORD **)(rf_local_fpgun_player + 196));
        v6 = rf_vector3_set_components_return_destination(v17, 0.0, 0.0, 1.0);
        v5 = rf_vector3_set_components_return_destination(v16, 0.0, 1.0, 0.0);
        v0 = rf_vector3_set_components_return_destination(v15, 1.0, 0.0, 0.0);
        v1 = rf_matrix3_construct_from_three_rows((int)v18, v0, v5, v6);
        v22 = rf_item_instance_spawn(v25, &MEMORY[0x1809820], unk_6F915C[20 * v25], -1, (int)lhs, v1, -1, 1, 0);
        if ( v22 && *(_DWORD *)(*(_DWORD *)(v22 + 660) + 64) != -1 )
          *(_DWORD *)(v22 + 676) = unk_912260[340 * *(_DWORD *)(*(_DWORD *)(v22 + 660) + 64)];
        if ( v22 )
        {
          v10 = rf_string_concat_cstr_object(v14, "dropped ", *(const void ***)(v22 + 660));
          v26 = 0;
          v9 = (std::exception *)rf_string_concat_object_cstr(v13, v10, "\n");
          LOBYTE(v26) = 1;
          v2 = rf_string_object_c_str_or_empty(v9);
          rf_console_output_append_text_lines(v2, nullptr);
          LOBYTE(v26) = 0;
          rf_string_destroy_buffer(v13);
          v26 = -1;
          rf_string_destroy_buffer(v14);
          scalar = *(float *)(v22 + 120) + 3.0;
          v3 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
          rf_vector_add(lhs, sum_result, v3);
          rf_object_publish_position_and_bounds(v22, sum_result);
        }
      }
    }
  }
  if ( dword_1809814 )
  {
    rf_console_output_append_text_lines("drop_item <item_name>\n", nullptr);
    rf_console_output_append_text_lines("item types:\n", nullptr);
    for ( i = 0; i < unk_6F9124; ++i )
    {
      v7 = (std::exception *)rf_string_concat_object_cstr(v11, (_DWORD *)&unk_6F9130 + 20 * i, "\n");
      v26 = 2;
      v4 = rf_string_object_c_str_or_empty(v7);
      rf_console_output_append_text_lines(v4, nullptr);
      v26 = -1;
      rf_string_destroy_buffer(v11);
    }
  }
}

