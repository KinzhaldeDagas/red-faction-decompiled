// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ED200 rf_fpgun_load_type_model_with_team_materials
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Cdecl52-byte type record, selector. Strips last extension from type RFString+8 into stack buffer, loads character instance with flags0,0, immediately marks asset retained, then enables private materials. No load-result NULL check. Iterates signed material count,200-byte records; case-insensitive hand1st.tga/envirohand.tga/armnew1.tga matching at+20. Selector0 uses type DWORDs40/44/48 (red);1 uses28/32/36 (blue);999 uses16/20/24 (default). Other selectors retain original bitmap. Matching stores material DWORD16 including invalid handles. Warms bitmap16 for EVERY material, then returns model wrapper. Retention is an asset flag, not a reference-count increment.
int *__cdecl rf_fpgun_load_type_model_with_team_materials(_DWORD *a1, int a2)
{
  char *v2; // eax
  int i; // [esp+4h] [ebp-94h]
  int *character_instance; // [esp+8h] [ebp-90h]
  int v6; // [esp+Ch] [ebp-8Ch] BYREF
  char v7[128]; // [esp+10h] [ebp-88h] BYREF
  int v8; // [esp+94h] [ebp-4h] BYREF

  v2 = (char *)rf_string_object_c_str_or_empty(a1 + 2);
  rf_path_copy_without_last_extension(v7, v2);
  character_instance = rf_model_handle_load_character_instance(v7, 0, 0);
  rf_model_handle_mark_asset_retained(character_instance);
  rf_model_handle_enable_private_materials_get_table((int)character_instance, &v8, &v6);
  for ( i = 0; i < v8; ++i )
  {
    if ( a2 )
    {
      if ( a2 == 1 )
      {
        if ( !_stricmp((const char *)(v6 + 200 * i + 20), "hand1st.tga") )
        {
          *(_DWORD *)(v6 + 200 * i + 16) = a1[7];
        }
        else if ( !_stricmp((const char *)(v6 + 200 * i + 20), "envirohand.tga") )
        {
          *(_DWORD *)(v6 + 200 * i + 16) = a1[8];
        }
        else if ( !_stricmp((const char *)(v6 + 200 * i + 20), "armnew1.tga") )
        {
          *(_DWORD *)(v6 + 200 * i + 16) = a1[9];
        }
      }
      else if ( a2 == 999 )
      {
        if ( !_stricmp((const char *)(v6 + 200 * i + 20), "hand1st.tga") )
        {
          *(_DWORD *)(v6 + 200 * i + 16) = a1[4];
        }
        else if ( !_stricmp((const char *)(v6 + 200 * i + 20), "envirohand.tga") )
        {
          *(_DWORD *)(v6 + 200 * i + 16) = a1[5];
        }
        else if ( !_stricmp((const char *)(v6 + 200 * i + 20), "armnew1.tga") )
        {
          *(_DWORD *)(v6 + 200 * i + 16) = a1[6];
        }
      }
    }
    else if ( !_stricmp((const char *)(v6 + 200 * i + 20), "hand1st.tga") )
    {
      *(_DWORD *)(v6 + 200 * i + 16) = a1[10];
    }
    else if ( !_stricmp((const char *)(v6 + 200 * i + 20), "envirohand.tga") )
    {
      *(_DWORD *)(v6 + 200 * i + 16) = a1[11];
    }
    else if ( !_stricmp((const char *)(v6 + 200 * i + 20), "armnew1.tga") )
    {
      *(_DWORD *)(v6 + 200 * i + 16) = a1[12];
    }
    rf_renderer_bind_texture_for_level_warmup(*(_DWORD *)(v6 + 200 * i + 16));
  }
  return character_instance;
}

