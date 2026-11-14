// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413880 rf_console_drop_clutter_command
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Noargs console callback. If global1809818 set,reads string token with(requiredMask2,preserveCase0). Empty current token1809820 sets globalhelp1809814=1;unrecognized class lookup415BD0 prints native misspelled unrecognized message without settinghelp itself. Valid class:gets position from entity referenced by local-player196 viewwrapper and copies referenced entity2016 matrix to local EBP-38h. That36-byte matrix DEFINES forward vector at EBP-20h (its third row);it is NOT uninitialized despite decompiler splitting locals. Builds identity orientation explicitly,creates clutter(classIndex,emptyName,room-1,viewPosition,identityMatrix,0). On nonNULL creation prints dropped class
// name,then relocates to viewPosition+viewForward*(created common/model radius120+3) via4BC330,which updates common/current/predicted positions and bounds;identity spawn orientation retained. Does not trace/validate free space or use physics outer radius384 for spacing. Independent help1809814 branch prints usage and ALL class names using signed count666B60,even after a successful spawn if flag already set. Does not reset console flags or guard local-player/viewwrapper/entity pointers.
void rf_console_drop_clutter_command()
{
  float *v0; // eax
  int v1; // eax
  const char *v2; // eax
  float *v3; // eax
  const char *v4; // eax
  float *v5; // [esp+Ch] [ebp-FCh]
  float *v6; // [esp+10h] [ebp-F8h]
  std::exception *v7; // [esp+1Ch] [ebp-ECh]
  float scalar; // [esp+24h] [ebp-E4h]
  std::exception *v9; // [esp+28h] [ebp-E0h]
  _DWORD *v10; // [esp+30h] [ebp-D8h]
  _BYTE v11[8]; // [esp+48h] [ebp-C0h] BYREF
  float scaled_result[3]; // [esp+50h] [ebp-B8h] BYREF
  _BYTE v13[8]; // [esp+5Ch] [ebp-ACh] BYREF
  _BYTE v14[8]; // [esp+64h] [ebp-A4h] BYREF
  float v15[3]; // [esp+6Ch] [ebp-9Ch] BYREF
  float v16[3]; // [esp+78h] [ebp-90h] BYREF
  float v17[3]; // [esp+84h] [ebp-84h] BYREF
  _BYTE v18[36]; // [esp+90h] [ebp-78h] BYREF
  int i; // [esp+B4h] [ebp-54h]
  float sum_result[3]; // [esp+B8h] [ebp-50h] BYREF
  float lhs[3]; // [esp+C4h] [ebp-44h] BYREF
  _BYTE v22[24]; // [esp+D0h] [ebp-38h] BYREF
  float vector[3]; // [esp+E8h] [ebp-20h] BYREF
  int v24; // [esp+F4h] [ebp-14h]
  int index_by_name; // [esp+F8h] [ebp-10h]
  int v26; // [esp+104h] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    if ( &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 == (char *)&unk_1809821 )
    {
      dword_1809814 = 1;
    }
    else
    {
      index_by_name = rf_clutter_class_find_index_by_name(&MEMORY[0x1809820]);
      if ( index_by_name < 0 )
      {
        rf_console_output_append_text_lines("unrecongnized entity type", nullptr);
      }
      else
      {
        rf_entity_view_copy_referenced_position(lhs, *(_DWORD *)(rf_local_fpgun_player + 196));
        rf_entity_view_copy_referenced_matrix_2016((int)v22, *(_DWORD **)(rf_local_fpgun_player + 196));
        v6 = rf_vector3_set_components_return_destination(v17, 0.0, 0.0, 1.0);
        v5 = rf_vector3_set_components_return_destination(v16, 0.0, 1.0, 0.0);
        v0 = rf_vector3_set_components_return_destination(v15, 1.0, 0.0, 0.0);
        v1 = rf_matrix3_construct_from_three_rows((int)v18, v0, v5, v6);
        v24 = rf_clutter_runtime_create(index_by_name, (char *)&byte_63127B, -1, (int)lhs, v1, 0);
        if ( v24 )
        {
          v10 = rf_string_concat_cstr_object(v14, "dropped ", *(const void ***)(v24 + 660));
          v26 = 0;
          v9 = (std::exception *)rf_string_concat_object_cstr(v13, v10, "\n");
          LOBYTE(v26) = 1;
          v2 = rf_string_object_c_str_or_empty(v9);
          rf_console_output_append_text_lines(v2, nullptr);
          LOBYTE(v26) = 0;
          rf_string_destroy_buffer(v13);
          v26 = -1;
          rf_string_destroy_buffer(v14);
          scalar = *(float *)(v24 + 120) + 3.0;
          v3 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
          rf_vector_add(lhs, sum_result, v3);
          rf_object_publish_position_and_bounds(v24, sum_result);
        }
      }
    }
  }
  if ( dword_1809814 )
  {
    rf_console_output_append_text_lines("drop_clutter <clutter_name>\n", nullptr);
    rf_console_output_append_text_lines("clutter types:\n", nullptr);
    for ( i = 0; i < unk_666B60; ++i )
    {
      v7 = (std::exception *)rf_string_concat_object_cstr(v11, &byte_667000[232 * i], "\n");
      v26 = 2;
      v4 = rf_string_object_c_str_or_empty(v7);
      rf_console_output_append_text_lines(v4, nullptr);
      v26 = -1;
      rf_string_destroy_buffer(v11);
    }
  }
}

