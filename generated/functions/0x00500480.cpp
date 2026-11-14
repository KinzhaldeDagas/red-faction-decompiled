// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500480 rf_event_swap_textures_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_swap_textures forward, vtable0x63E1CC slot+4. Each common-object target with non-null model+0x80 supplies material count/table via0x565360. For j=0,1 read signed material index event+0x2B8+4*j and filename string+0x2C0+8*j. Only index<count, nonempty string and successfully loaded bitmap0x574E90(name,-1,1)!=-1 gate write to material_base+200*index+0x10. NO explicit index>=0 test: do not describe invalid negative index as safely skipped. No old texture release or target deduplication here.
int __thiscall rf_event_swap_textures_forward(int this)
{
  int result; // eax
  int *v2; // eax
  char *v3; // eax
  int v5; // [esp+4h] [ebp-18h]
  int v6; // [esp+8h] [ebp-14h] BYREF
  int v7; // [esp+Ch] [ebp-10h] BYREF
  int j; // [esp+10h] [ebp-Ch]
  int v9; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v9 = rf_object_resolve_handle(*v2);
    if ( v9 && *(_DWORD *)(v9 + 128) )
    {
      rf_model_handle_enable_private_materials_get_table(*(_DWORD *)(v9 + 128), &v7, &v6);
      for ( j = 0; j < 2; ++j )
      {
        if ( *(_DWORD *)(this + 4 * j + 696) < v7
          && (int)rf_string_length_from_cstr((const char **)(this + 8 * j + 704)) > 0 )
        {
          v3 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 8 * j + 704));
          v5 = rf_bitmap_load_with_optional_mipmap_generation(v3, (void *)0xFFFFFFFF, 1);
          if ( v5 != -1 )
            *(_DWORD *)(v6 + 200 * *(_DWORD *)(this + 4 * j + 696) + 16) = v5;
        }
      }
    }
  }
  return result;
}

