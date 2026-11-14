// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005876A0 rf_character_animation_remaining_time
// UNREALRED VERIFIED [ai-script-animation-release-20261013] Character remaining-time query finds the record by animation identity and returns max(0, end_tick - record_tick) / 160 / 30. It does not report positive time merely because a frozen endpoint record still exists. AI cleanup uses this exact nonzero-time distinction.
double __thiscall rf_character_animation_remaining_time(_DWORD *this, int a2)
{
  int end_tick; // eax
  int action_record; // [esp+8h] [ebp-8h]

  action_record = rf_character_instance_find_action_record(this, a2);
  if ( action_record < 0 )
    return 0.0;
  end_tick = rf_rfa_get_end_tick(*(void **)(*(this + 1876) + 4 * a2 + 3932));
  return (float)((double)rf_int_max(0, end_tick - *(this + 3 * action_record + 1206)) / 160.0 / 30.0);
}

