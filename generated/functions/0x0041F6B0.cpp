// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F6B0 rf_console_drop_entity_command
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No-argument void console callback. If global1809818==0, only final help-flag test runs. Otherwise parse56F950(mask2,preserveCase0), ignoring
// returned flags, then unbounded NUL scan of current token1809820. Empty token sets global help1809814=1; nonempty name resolves entities.tbl index431680, SIGNED index<0 prints
// literal misspelled "unrecongnized entity type" and skips creation. Nonnegative index: read local-fpgun-player+196 view wrapper without NULL guards; copy referenced entity
// position+60 and retained matrix+2016. Spawn point is FLOAT32 position+FLOAT32(5.0*third matrix row); build explicit identity orientation, then
// create42CB80(index,emptyString,-1,&point,&identity,LOWBYTE0,-1). Null create result skips all remaining creation actions. Successful create prints "dropped "+class RFString+newline
// and destroys both temporary strings.435A50(owner) EXACT AL1 (class RFString equals Hendrix) sets friendliness2, all otherAL friendliness1. Case-insensitive exact class name
// stationary turret requests numeric AI mode11(owner+672,-1,-1), then friendliness0; all others request mode2, whose delegate may remap to3. OR owner DWORD+2064 mask0x00200000 BEFORE
// parsing next argument. Parse56F950(mask0xC3,0); current global token flags1809308 mask0x40 sets owner2064 mask0x10000. Only FULL flags==EXACT0x40 OR0x80 parses one additional
// argument with mask3. Afterwards RE-READ current flags: mask2 plus nonempty current token invokes4368F0(owner,token), delegates model skin-profile lookup, ignores result; it does
// not necessarily use the original entity-name token. Vehicle predicate437690 EXACT AL1 then key-1 runtime-enabled predicate438090 ANY nonzero enables recursive headlamps, zero
// disables. Route-fit boolean starts0 and becomes1 unless BOTH437F60(owner) AND437FD0(owner) return nonzero, with second predicate skipped when first zero. Preserve this literal
// NOT-AND, unlike normal NOT-OR grounded tests; their category sets are disjoint for unchanged descriptor. Call40FD80(owner COMMON position,owner FLOAT1984,owner FLOAT1988,that
// BYTE,&owner1692,&owner1696,BYTE0), distinct output slots; ignore returnedAL even when fallback populates output withAL0. Finally OR owner2064 mask0x01000000 and owner2068
// mask0x400. On every ordinary exit, nonzero help1809814 prints exact usage line; callback never clears help itself. Parser mask failure can longjmp after entity
// creation/friendliness/mode/early flags, with no rollback; later route/final flags then do not run. No success return, authority/runtime/death admission, owner guard or deletion
// rollback. SEH cleanup destroys string temporaries only.
void rf_console_drop_entity_command()
{
  float *v0; // eax
  float *v1; // eax
  float *v2; // eax
  const char *v3; // eax
  float *v4; // [esp+Ch] [ebp-FCh]
  float *v5; // [esp+10h] [ebp-F8h]
  std::exception *v6; // [esp+30h] [ebp-D8h]
  _DWORD *v7; // [esp+38h] [ebp-D0h]
  _BYTE v8[8]; // [esp+50h] [ebp-B8h] BYREF
  _BYTE v9[8]; // [esp+58h] [ebp-B0h] BYREF
  float v10[3]; // [esp+60h] [ebp-A8h] BYREF
  float v11[3]; // [esp+6Ch] [ebp-9Ch] BYREF
  float v12[3]; // [esp+78h] [ebp-90h] BYREF
  _BYTE v13[36]; // [esp+84h] [ebp-84h] BYREF
  float scaled_result[3]; // [esp+A8h] [ebp-60h] BYREF
  char v15; // [esp+B7h] [ebp-51h]
  float lhs[3]; // [esp+B8h] [ebp-50h] BYREF
  _DWORD *runtime; // [esp+C4h] [ebp-44h]
  float sum_result[3]; // [esp+C8h] [ebp-40h] BYREF
  _BYTE v19[24]; // [esp+D4h] [ebp-34h] BYREF
  float vector[3]; // [esp+ECh] [ebp-1Ch] BYREF
  int v21; // [esp+F8h] [ebp-10h]
  int v22; // [esp+104h] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    if ( &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 == (char *)&unk_1809821 )
    {
      dword_1809814 = 1;
    }
    else
    {
      v21 = sub_431680(&MEMORY[0x1809820]);
      if ( v21 < 0 )
      {
        rf_console_output_append_text_lines("unrecongnized entity type", nullptr);
      }
      else
      {
        rf_entity_view_copy_referenced_position(lhs, *(_DWORD *)(rf_local_fpgun_player + 196));
        rf_entity_view_copy_referenced_matrix_2016((int)v19, *(_DWORD **)(rf_local_fpgun_player + 196));
        v0 = rf_vector_multiply_scalar(vector, scaled_result, 5.0);
        rf_vector_add(lhs, sum_result, v0);
        v5 = rf_vector3_set_components_return_destination(v12, 0.0, 0.0, 1.0);
        v4 = rf_vector3_set_components_return_destination(v11, 0.0, 1.0, 0.0);
        v1 = rf_vector3_set_components_return_destination(v10, 1.0, 0.0, 0.0);
        v2 = (float *)rf_matrix3_construct_from_three_rows((int)v13, v1, v4, v5);
        runtime = (_DWORD *)rf_entity_create_runtime(v21, (char *)&byte_63198D, -1, (int)sum_result, v2, 0, -1);
        if ( runtime )
        {
          v7 = rf_string_concat_cstr_object(v9, "dropped ", (const void **)runtime[165]);
          v22 = 0;
          v6 = (std::exception *)rf_string_concat_object_cstr(v8, v7, "\n");
          LOBYTE(v22) = 1;
          v3 = rf_string_object_c_str_or_empty(v6);
          rf_console_output_append_text_lines(v3, nullptr);
          LOBYTE(v22) = 0;
          rf_string_destroy_buffer(v8);
          v22 = -1;
          rf_string_destroy_buffer(v9);
          if ( rf_entity_class_name_is_hendrix((int)runtime) )
            sub_4BBF50((int)runtime, 2);
          else
            sub_4BBF50((int)runtime, 1);
          if ( rf_string_equals_case_insensitive(runtime[165], "stationary turret") )
          {
            rf_ai_numeric_mode_write(runtime + 168, 11, -1, -1);
            sub_4BBF50((int)runtime, 0);
          }
          else
          {
            rf_ai_numeric_mode_write(runtime + 168, 2, -1, -1);
          }
          runtime[516] |= 0x200000u;
          rf_console_read_argument_validate_type_mask(195, 0);
          if ( (dword_1809308 & 0x40) != 0 )
            runtime[516] |= 0x10000u;
          if ( dword_1809308 == 64 || dword_1809308 == 128 )
            rf_console_read_argument_validate_type_mask(3, 0);
          if ( (dword_1809308 & 2) != 0 && &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 != (char *)&unk_1809821 )
            rf_entity_apply_named_skin_profile((int)runtime, &MEMORY[0x1809820]);
          if ( rf_object_is_use_vehicle(runtime) )
          {
            if ( rf_entity_runtime_enabled_or_resolved_attachment((int)runtime, -1) )
              rf_entity_enable_headlamp_recursive(runtime);
            else
              rf_entity_disable_headlamp_recursive(runtime);
          }
          v15 = 0;
          if ( !rf_entity_descriptor_mode_is_12_15_13_11_or9((int)runtime)
            || !rf_entity_movement_is_index4_or7((int)runtime) )
          {
            v15 = 1;
          }
          sub_40FD80(
            (float *)runtime + 15,
            *((float *)runtime + 496),
            *((float *)runtime + 497),
            v15,
            runtime + 423,
            runtime + 424,
            0);
          runtime[516] |= (unsigned int)&unk_1000000;
          runtime[517] |= 0x400u;
        }
      }
    }
  }
  if ( dword_1809814 )
    rf_console_output_append_text_lines("drop_entity <entity_name> <ai_controlled>\n", nullptr);
}

