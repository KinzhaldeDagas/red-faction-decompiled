// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00504A90 rf_trigger_unlink_and_clear_members
// UNREALRED VERIFIED [event-lifecycle-20261028]: Unlinks trigger from doubly-linked runtime list using next at+652 and prev at+656, clears both links, assigns string constants0x63E485/0x63E486 to members+24/+692, releases linked-UID array backing at+724, decrements global trigger count0x90B504. Does not operator-delete trigger storage or guard null neighbor pointers/count underflow here.
void **__cdecl rf_trigger_unlink_and_clear_members(int a1)
{
  void **result; // eax

  *(_DWORD *)(*(_DWORD *)(a1 + 656) + 652) = *(_DWORD *)(a1 + 652);
  *(_DWORD *)(*(_DWORD *)(a1 + 652) + 656) = *(_DWORD *)(a1 + 656);
  *(_DWORD *)(a1 + 652) = 0;
  *(_DWORD *)(a1 + 656) = 0;
  rf_string_assign_from_cstr((_DWORD *)(a1 + 24), (char *)&byte_63E485);
  rf_string_assign_from_cstr((_DWORD *)(a1 + 692), (char *)byte_63E486);
  result = rf_pointer_array_release_storage((void **)(a1 + 724));
  --unk_90B504;
  return result;
}

