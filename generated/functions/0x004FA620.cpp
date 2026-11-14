// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA620 rf_event_create_spawn_object_from_names
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Case-insensitive type C string accepts only clutter/entity/item, mapping numeric4/0/1 and definition lookup0x415BD0/0x431680/0x473770 respectively from supplied definition string object. Unknown type returns0 before event creation. Recognized type passes lookup result unchanged, including -1, plus raw byte and float to0x4FA720; no successful definition-resolution requirement.
int __cdecl rf_event_create_spawn_object_from_names(int a1, int a2, std::exception *a3, char a4, float a5)
{
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  int index_by_name; // [esp+4h] [ebp-8h]
  unsigned int v10; // [esp+8h] [ebp-4h]

  v10 = -1;
  index_by_name = -1;
  if ( rf_string_equals_case_insensitive(a2, "clutter") )
  {
    v10 = 4;
    v5 = (char *)rf_string_object_c_str_or_empty(a3);
    index_by_name = rf_clutter_class_find_index_by_name(v5);
  }
  else if ( rf_string_equals_case_insensitive(a2, "entity") )
  {
    v10 = 0;
    v6 = (char *)rf_string_object_c_str_or_empty(a3);
    index_by_name = sub_431680(v6);
  }
  else if ( rf_string_equals_case_insensitive(a2, "item") )
  {
    v10 = 1;
    v7 = (char *)rf_string_object_c_str_or_empty(a3);
    index_by_name = rf_item_definition_find_by_name(v7);
  }
  if ( v10 == -1 )
    return 0;
  else
    return rf_event_create_spawn_object_record(a1, v10, index_by_name, a4, a5);
}

