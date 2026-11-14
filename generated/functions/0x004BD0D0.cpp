// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD0D0 rf_model_apply_skin_texture_names
// UNREALRED VERIFIED [switch-clutter-reset] Loads each ordered skin texture name and replaces the corresponding live model material texture slot up to the model material count.
_DWORD *__cdecl rf_model_apply_skin_texture_names(int a1, int a2)
{
  _DWORD *result; // eax
  char *v3; // eax
  int v4; // eax
  int v5; // [esp+0h] [ebp-Ch] BYREF
  int i; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h] BYREF

  result = rf_model_handle_enable_private_materials_get_table(a1, &v7, &v5);
  for ( i = 0; i < *(_DWORD *)(a2 + 8); ++i )
  {
    result = (_DWORD *)i;
    if ( i >= v7 )
      break;
    v3 = (char *)rf_string_object_c_str_or_empty((const void *)(a2 + 8 * i + 12));
    v4 = rf_bitmap_load_with_optional_mipmap_generation(v3, (void *)0xFFFFFFFF, 1);
    *(_DWORD *)(v5 + 200 * i + 16) = v4;
    result = (_DWORD *)(i + 1);
  }
  return result;
}

