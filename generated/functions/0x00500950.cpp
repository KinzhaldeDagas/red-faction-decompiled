// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500950 rf_event_goal_check_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_goal_check forward, vtable0x63E21C slot+4. Lookup string event+0x2B8 in shared16-byte goal table0x4FABF0 first; when found use its signed count+0xC. Only when absent, find named level record0x501E70 and use its signed count+0x2C0; absent in both returns. If count>=signed event threshold+0x2C0, explicitly dispatch authored targets with(event+0x2AC,event+0x2A8,1). Shared count wins if both exist, even if counts disagree. No count mutation or one-shot latch in this body.
int *__thiscall rf_event_goal_check_forward(int *this)
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
    return (int *)rf_mission_event_forward_targets((int)this, *(this + 171), *(this + 170), 1);
  return result;
}

