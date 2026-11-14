// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041DD50 rf_corpse_render_alpha
// UNREALRED VERIFIED [corpse-lifecycle-decode]: Converts a retiring corpse's one-second remaining time to clamp(round(remaining * 255), 0, 255).
int __cdecl rf_corpse_render_alpha(int a1)
{
  int result; // eax
  char v2[80]; // [esp+0h] [ebp-E0h] BYREF
  char v3[36]; // [esp+50h] [ebp-90h] BYREF
  float v4[3]; // [esp+74h] [ebp-6Ch] BYREF
  int v5; // [esp+80h] [ebp-60h]
  char *v6; // [esp+84h] [ebp-5Ch]
  int v7; // [esp+88h] [ebp-58h] BYREF
  int v8; // [esp+8Ch] [ebp-54h]
  int v9; // [esp+90h] [ebp-50h] BYREF
  _DWORD v10[8]; // [esp+94h] [ebp-4Ch] BYREF
  float v11[9]; // [esp+B4h] [ebp-2Ch] BYREF
  int lod_group_count; // [esp+D8h] [ebp-8h]
  float v13; // [esp+DCh] [ebp-4h]

  rf_model_render_options_construct((char *)&v7);
  result = a1;
  if ( *(_DWORD *)(a1 + 128) )
  {
    if ( *(_BYTE *)(unk_87C640 + 4016) == 1 )
    {
      v7 |= 2u;
      if ( *(_BYTE *)(unk_87C640 + 4017) == 1 )
      {
        v7 |= 1u;
        v10[0] = *(_DWORD *)(unk_87C640 + 4018);
      }
      else
      {
        rf_color4_set_bytes_return_destination(v10, 0, 32, 0, 255);
      }
    }
    v6 = &rf_entity_info_definitions[5396 * *(_DWORD *)(a1 + 672)];
    lod_group_count = rf_model_handle_get_lod_group_count(*(int **)(a1 + 128));
    v8 = rf_entity_choose_definition_lod((const float *)(a1 + 60), *(_DWORD *)(a1 + 672));
    if ( lod_group_count > 1 && (*(_DWORD *)(a1 + 668) & 0x10) != 0 && !v8 )
      v8 = 1;
    if ( (unsigned __int8)rf_corpse_is_retiring(a1) == 1 )
    {
      v9 = (int)(*(float *)(a1 + 664) / 1.0 * 255.0 + 0.5);
      rf_integer_clamp_in_place(&v9, 0, 255);
    }
    v13 = 0.0;
    if ( (*(_DWORD *)(a1 + 668) & 0x100) != 0 )
    {
      v13 = 1.0;
    }
    else if ( (*(_DWORD *)(a1 + 668) & 0x200) != 0 )
    {
      v13 = rf_record_float48_divide12_or_one(*(_DWORD *)(a1 + 720));
    }
    if ( v13 > 0.0 )
      *(float *)&v10[2] = 1.0 - (1.0 - flt_661300) * v13;
    v7 |= 0x80u;
    v10[7] = *(_DWORD *)(a1 + 728);
    rf_matrix3_copy(v11, (const float *)(a1 + 72));
    result = rf_model_handle_render_all_adapter(*(_DWORD *)(a1 + 128), a1 + 60, a1 + 72, (int)&v7);
    if ( *(_DWORD *)(a1 + 712) )
    {
      rf_vector3_default_construct_noop(v4);
      rf_matrix3_construct(v3);
      result = 5396 * *(_DWORD *)(a1 + 672);
      v5 = *(_DWORD *)((char *)&unk_683C2C + result);
      if ( v5 >= 0 )
      {
        rf_vmesh_compose_prop_world_transform(*(_DWORD *)(a1 + 128), v5, (float *)(a1 + 72), a1 + 60, (int)v3, v4);
        rf_model_render_options_construct(v2);
        return rf_model_handle_render_all_adapter(*(_DWORD *)(a1 + 712), (int)v4, (int)v3, (int)v2);
      }
    }
  }
  return result;
}

