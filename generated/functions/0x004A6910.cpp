// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6910 rf_net_statistics_reset_packet38_window
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Thiscall(stats). Arms wrapped game-clock deadline at stats+496 for2000ms, then zeros five DWORDs at+500,+504,+508,+512,+516. record_packet increments first two counters for
// opcode38 outgoing/incoming; meanings of remaining three are not inferred here. Does not clear total bytes, histories, per-opcode arrays or RTT state. No mode/authority/null guard.
// Native EAX contains stats pointer at exit; existing thiscall/no-stack-argument ABI retained.
int *__thiscall rf_net_statistics_reset_packet38_window(int *this)
{
  rf_clock_deadline_set_wrapped_offset(this + 124, 2000);
  *(this + 125) = 0;
  *(this + 126) = 0;
  *(this + 127) = 0;
  *(this + 128) = 0;
  *(this + 129) = 0;
  return this;
}

