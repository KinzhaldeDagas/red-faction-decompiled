// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6BD0 rf_net_statistics_tick_and_probe
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Thiscall(stats,peer), RET4. Each call advances signed frame index+248 if<30; otherwise memcpy116 overlapping bytes from history+12 to+8 and+132 to+128, then zeros last
// DWORDs+124/+244, leaving index at its existing>=30 value. If wrapped one-second deadline+1400 has_elapsed returns any nonzero, similarly advances second index+492 or shifts
// histories+256 to+252 and+376 to+372, zeroing+368/+488, then rearms+1400 for1000ms. Only one second slot per call is advanced even after a long pause; no multi-second catchup or
// negative-index repair.
// Only authority BYTE EXACTLY1 performs probe logic (no own runtime guard). Sends empty opcode24 probe when retry deadline+1416 is unarmed AND outstanding stamp+1420<0, OR
// outstanding>=0 and signed wrapping performance now-stamp>3000 (EXACTLY3000 does not timeout), OR retry deadline is armed and has_elapsed returns any nonzero. Native code tests
// is_armed twice on last path. Calls server probe sender(peer), then UNCONDITIONALLY stores fresh performance-clock ms stamp and disarms retry deadline even if sender rejected
// runtime or transport failed. Return AL is guard/delegate artifact, not boolean sent/success. Does not update RTT samples or packet38 two-second window counters here.
unsigned __int8 __thiscall rf_net_statistics_tick_and_probe(_DWORD *this, int a2)
{
  unsigned __int8 result; // al

  if ( (int)*(this + 62) < 30 )
  {
    ++*(this + 62);
  }
  else
  {
    memcpy_0(this + 2, this + 3, 0x74u);
    *(this + 31) = 0;
    memcpy_0(this + 32, this + 33, 0x74u);
    *(this + 61) = 0;
  }
  if ( rf_clock_deadline_has_elapsed_half_period(this + 350) )
  {
    if ( (int)*(this + 123) < 30 )
    {
      ++*(this + 123);
    }
    else
    {
      memcpy_0(this + 63, this + 64, 0x74u);
      *(this + 92) = 0;
      memcpy_0(this + 93, this + 94, 0x74u);
      *(this + 122) = 0;
    }
    rf_clock_deadline_set_wrapped_offset(this + 350, 1000);
  }
  result = rf_multiplayer_server_authority;
  if ( rf_multiplayer_server_authority == 1
    && (!rf_timestamp_is_armed_nonnegative(this + 354) && (int)*(this + 355) < 0
     || (int)*(this + 355) >= 0 && rf_performance_clock_elapsed_scaled(1000) - *(this + 355) > 3000
     || (result = rf_timestamp_is_armed_nonnegative(this + 354)) != 0
     && (result = rf_timestamp_is_armed_nonnegative(this + 354)) != 0
     && (result = rf_clock_deadline_has_elapsed_half_period(this + 354)) != 0) )
  {
    rf_server_send_latency_probe_packet24(a2);
    *(this + 355) = rf_performance_clock_elapsed_scaled(1000);
    return (unsigned __int8)rf_clock_deadline_disarm(this + 354);
  }
  return result;
}

