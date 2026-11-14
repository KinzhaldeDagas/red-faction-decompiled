// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477070 rf_console_zap_spawn_bolt_emitter
// UNREALRED VERIFIED [cutscene-playback-20261028]: Help prints Usage: zap <num_segs> <jitter> <use_bitmap> <thickness>. Otherwise obtains local-player view transform, builds bolt parameters with forward scale5, up vector, vector(3,0,0), color(240,248,255,255), parses segment count/jitter, fixed float ranges0.2/1/0.25/1.5. Optional parse flag0x40 loads bolt.tga and parses thickness; else bitmap=-1. Allocates0x18C-byte emitter through0x4C0830 with owner local-player handle, appends result to bolt registry even if allocation returnednull. Adds ambient electric_arc_01.wav at view position then initializes ambient frontend slots. No local-player-pointer validation in body.
int rf_console_zap_spawn_bolt_emitter()
{
  float *v1; // eax
  float *v2; // eax
  char *v3; // [esp+14h] [ebp-F8h]
  char *v4; // [esp+18h] [ebp-F4h]
  float v5[3]; // [esp+20h] [ebp-ECh] BYREF
  float v6[3]; // [esp+2Ch] [ebp-E0h] BYREF
  float v7[3]; // [esp+38h] [ebp-D4h] BYREF
  float v8[3]; // [esp+44h] [ebp-C8h] BYREF
  float v9[3]; // [esp+50h] [ebp-BCh] BYREF
  float copy_result[3]; // [esp+5Ch] [ebp-B0h] BYREF
  int v11; // [esp+68h] [ebp-A4h] BYREF
  float source[3]; // [esp+6Ch] [ebp-A0h] BYREF
  _BYTE v13[4]; // [esp+78h] [ebp-94h] BYREF
  float destination[3]; // [esp+7Ch] [ebp-90h] BYREF
  float v15[3]; // [esp+88h] [ebp-84h] BYREF
  float v16[3]; // [esp+94h] [ebp-78h] BYREF
  float v17[11]; // [esp+A0h] [ebp-6Ch] BYREF
  unsigned int v18; // [esp+CCh] [ebp-40h]
  int v19; // [esp+D0h] [ebp-3Ch] BYREF
  _BYTE v20[8]; // [esp+D4h] [ebp-38h] BYREF
  _BYTE v21[24]; // [esp+DCh] [ebp-30h] BYREF
  float v22[3]; // [esp+F4h] [ebp-18h] BYREF
  int v23; // [esp+108h] [ebp-4h]

  if ( dword_1809814 )
    return rf_console_output_append_text_lines("Usage: zap <num_segs> <jitter> <use_bitmap> <thickness>", nullptr);
  rf_entity_view_copy_referenced_position(source, *(_DWORD *)(rf_local_fpgun_player + 196));
  rf_entity_view_copy_referenced_matrix_2016((int)v21, *(_DWORD **)(rf_local_fpgun_player + 196));
  rf_bolt_emitter_definition_construct_noop((int)v13);
  rf_vector_copy(destination, copy_result, source);
  rf_vector_copy(v15, v9, v22);
  rf_vector3_scale_in_place_return_self(v15, 5.0);
  v1 = rf_vector3_set_components_return_destination(v8, 0.0, 1.0, 0.0);
  rf_vector_copy(v16, v7, v1);
  v2 = rf_vector3_set_components_return_destination(v6, 3.0, 0.0, 0.0);
  rf_vector_copy(v17, v5, v2);
  rf_color4_set_bytes_return_destination(v20, 240, 248, 255, 255);
  rf_console_read_argument_validate_type_mask(8, 0);
  LODWORD(v17[9]) = dword_180981C;
  rf_console_read_argument_validate_type_mask(16, 0);
  v17[8] = flt_180A400;
  v17[4] = 0.2;
  v17[5] = 1.0;
  v17[6] = 0.25;
  v17[7] = 1.5;
  rf_console_read_argument_validate_type_mask(193, 0);
  if ( (dword_1809308 & 0x40) != 0 )
  {
    v18 = rf_bitmap_load_and_query_animation_metadata("bolt.tga", &v19, &v11, (void *)0xFFFFFFFF);
    rf_console_read_argument_validate_type_mask(16, 0);
    v17[3] = flt_180A400;
  }
  else
  {
    v18 = -1;
  }
  LODWORD(v17[10]) = 15;
  v4 = (char *)operator new(0x18Cu);
  v23 = 0;
  if ( v4 )
    v3 = rf_bolt_emitter_construct_from_descriptor(v4, -1, *(_DWORD *)(rf_local_fpgun_player + 20), (int)v13, 1);
  else
    v3 = nullptr;
  v23 = -1;
  rf_pointer_array_append_dword(rf_bolt_emitter_registry, (int)v3);
  rf_ambient_sound_create(-1, "electric_arc_01.wav", source, 5.0, 1.0, 1.0, 0);
  return rf_ambient_sounds_initialize_frontend_slots();
}

