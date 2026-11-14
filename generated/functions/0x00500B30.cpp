// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500B30 rf_event_goal_set_reverse
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_goal_set reverse, vtable0x63E230 slot+8. Independently decrement existing level record+0x2C0 and shared record+0xC for event name+0x2B8. Does not clamp at0 or require either record to exist; both stores are raw32-bit subtraction.
char *__thiscall rf_event_goal_set_reverse(int this)
{
  char *v1; // eax
  char *result; // eax
  int level_record_by_name; // [esp+8h] [ebp-8h]
  char *v5; // [esp+Ch] [ebp-4h]

  level_record_by_name = rf_goal_find_level_record_by_name(this + 696);
  if ( level_record_by_name )
    --*(_DWORD *)(level_record_by_name + 704);
  v1 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 696));
  result = rf_goal_find_shared_record_by_name(v1);
  v5 = result;
  if ( result )
  {
    result = (char *)(*((_DWORD *)result + 3) - 1);
    *((_DWORD *)v5 + 3) = result;
  }
  return result;
}

