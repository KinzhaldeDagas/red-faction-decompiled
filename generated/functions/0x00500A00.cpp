// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500A00 rf_event_goal_check_reverse
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_goal_check reverse, vtable0x63E21C slot+8. Uses the SAME signed count>=threshold condition and shared-before-level lookup as forward; accepted result dispatches(event+0x2AC,event+0x2A8,0). Reverse does not invert the condition or decrement counts.
int *__thiscall rf_event_goal_check_reverse(int *this)
{
  char *v1; // eax
  int *result; // eax
  int v4; // [esp+10h] [ebp-8h]
  char *shared_record_by_name; // [esp+14h] [ebp-4h]

  v1 = (char *)rf_string_object_c_str_or_empty(this + 174);
  shared_record_by_name = rf_goal_find_shared_record_by_name(v1);
  if ( shared_record_by_name )
  {
    v4 = *((_DWORD *)shared_record_by_name + 3);
  }
  else
  {
    result = (int *)rf_goal_find_level_record_by_name((int)(this + 174));
    if ( !result )
      return result;
    v4 = result[176];
  }
  result = this;
  if ( v4 >= *(this + 176) )
    return (int *)rf_mission_event_forward_targets((int)this, *(this + 171), *(this + 170), 0);
  return result;
}

