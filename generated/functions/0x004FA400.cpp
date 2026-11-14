// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA400 rf_event_give_item_to_player_create_from_name
// UNREALRED VERIFIED [event-lifecycle-20261028]: Obtains C string from caller RF-string object via shared accessor (IDA labels it std::exception::what), resolves name using0x473770, then creates Give_Item_To_Player subtype19 with resulting index. Resolver returns-1 if absent; this wrapper does not reject it. No copying of item definitions.
int __cdecl rf_event_give_item_to_player_create_from_name(int a1, std::exception *a2)
{
  char *v2; // eax
  int v3; // eax

  v2 = (char *)rf_string_object_c_str_or_empty(a2);
  v3 = rf_item_definition_find_by_name(v2);
  return rf_event_give_item_to_player_create_from_fields(a1, v3);
}

