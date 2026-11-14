// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501CC0 rf_event_countdown_begin_apply
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Countdown initialization precision: exact case-insensitive event NAME station_blowup selects difficulty0/1/2/3=>90/55/45/35 seconds; other difficulty values leave previous global countdown unchanged (no default fallback). Other event names convert signed integer event+0x2B8 to float remaining seconds. Does not reset other events observed-above/fired bytes or clear shared countdown-over notification in this body.
char __thiscall rf_event_countdown_begin_apply(int *this)
{
  char result; // al
  char v2; // kr00_1

  result = rf_string_equals_case_insensitive((int)(this + 7), "station_blowup");
  if ( result )
  {
    v2 = result;
    result = dword_6612A4;
    switch ( dword_6612A4 )
    {
      case 0:
        rf_mission_countdown_remaining_seconds = 90.0;
        break;
      case 1:
        rf_mission_countdown_remaining_seconds = 55.0;
        break;
      case 2:
        rf_mission_countdown_remaining_seconds = 45.0;
        break;
      case 3:
        rf_mission_countdown_remaining_seconds = 35.0;
        break;
      default:
        result = v2;
        break;
    }
  }
  else
  {
    rf_mission_countdown_remaining_seconds = (float)*(this + 174);
  }
  return result;
}

