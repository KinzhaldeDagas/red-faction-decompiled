// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502F20 rf_goal_state_restore_shared_names
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] For each20-byte input(name,current), scan shared table using EXACT CASE-SENSITIVE strcmp. Existing exact match updates current count+0xC only. Otherwise call case-insensitive registrar0x4FAB50(name,0,current), which may preserve an existing case-only match instead of writing new count. Does not clear shared table first or delete entries absent from input. No serialized initial count restoration; new entry initial value is0.
void __cdecl rf_goal_state_restore_shared_names(int a1, int a2)
{
  int j; // [esp+14h] [ebp-10h]
  char v3; // [esp+1Bh] [ebp-9h]
  char *String2; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    String2 = (char *)(a1 + 20 * i);
    v3 = 0;
    for ( j = 0; j < dword_90B050; ++j )
    {
      if ( !strcmp(rf_string_object_c_str_or_empty(&byte_90B0F0[16 * j]), (const char *)(a1 + 20 * i)) )
      {
        unk_90B0FC[4 * j] = *((_DWORD *)String2 + 4);
        v3 = 1;
        break;
      }
    }
    if ( !v3 )
      rf_goal_register_shared_record_if_missing(String2, 0, *((_DWORD *)String2 + 4));
  }
}

