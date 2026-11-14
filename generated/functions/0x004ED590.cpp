// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ED590 rf_fpgun_load_default_weapon_model_and_warm_materials
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Cdecl weapon-record pointer. Strips last extension from RFString+64, loads character model with flags0,0, gets definition. Iterates signed definition count6588 with148-byte stride; mesh pointer at6736+148*i. Each mesh has signed material count132, table136,200-byte records; warms each bitmap DWORD16. Marks asset retained after warmup, returns model wrapper. No own NULL/load/handle validation.
int *__cdecl rf_fpgun_load_default_weapon_model_and_warm_materials(int a1)
{
  char *v1; // eax
  int j; // [esp+0h] [ebp-98h]
  int *character_instance; // [esp+4h] [ebp-94h]
  char v5[132]; // [esp+8h] [ebp-90h] BYREF
  int i; // [esp+90h] [ebp-8h]
  int definition_pointer; // [esp+94h] [ebp-4h]

  v1 = (char *)rf_string_object_c_str_or_empty((const void *)(a1 + 64));
  rf_path_copy_without_last_extension(v5, v1);
  character_instance = rf_model_handle_load_character_instance(v5, 0, 0);
  definition_pointer = rf_model_handle_get_definition_pointer((int)character_instance);
  for ( i = 0; i < *(_DWORD *)(definition_pointer + 6588); ++i )
  {
    for ( j = 0; j < *(_DWORD *)(*(_DWORD *)(definition_pointer + 148 * i + 6736) + 132); ++j )
      rf_renderer_bind_texture_for_level_warmup(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(definition_pointer + 148 * i + 6736)
                                                                      + 136)
                                                          + 200 * j
                                                          + 16));
  }
  rf_model_handle_mark_asset_retained(character_instance);
  return character_instance;
}

