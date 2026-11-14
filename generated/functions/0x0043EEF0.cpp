// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043EEF0 sub_43EEF0
// UNREALRED VERIFIED [combat-native-followup-20261104]: Obtains model resource through565EC0 and requires positive primary-name count+72, then589840 searches only ordered primary records.589840 delegates41F140/CRT strstr: first CASE-SENSITIVE substring match, not full-name equality or case-insensitive matching. Burn fallback list order43ECF0 is distinct from search order within primary records.
int sub_43EEF0(int a1, ...)
{
  char *v1; // eax
  int primary_bone_substring; // [esp+8h] [ebp-1Ch]
  int definition_pointer; // [esp+14h] [ebp-10h]
  va_list va; // [esp+30h] [ebp+Ch] BYREF

  va_start(va, a1);
  definition_pointer = rf_model_handle_get_definition_pointer(*(_DWORD *)(a1 + 128));
  if ( definition_pointer && *(int *)(definition_pointer + 72) > 0 )
  {
    v1 = (char *)rf_string_object_c_str_or_empty(va);
    primary_bone_substring = rf_character_find_primary_bone_substring((char *)definition_pointer, v1);
    rf_string_destroy_buffer(va);
    return primary_bone_substring;
  }
  else
  {
    rf_string_destroy_buffer(va);
    return -1;
  }
}

