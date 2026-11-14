// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505320 rf_trigger_set_forward_enabled
// UNREALRED VERIFIED [mission-when-dead-20261013] When_Dead type5 forwarding clears trigger+0x2B0 bit 0x10 only. It does NOT reset activation count, exhausted/cooldown state or invoke a clutter toggle. Type8 forwarding in 0x4FE940 instead calls mover/path function 0x489BB0.
// UNREALRED VERIFIED [mission-when-dead-targets-20261013] Forward enable clears only trigger+0x2B0 bit 0x10. Repeated enable is idempotent and must not replenish activation limits, clear exhaustion, restart occupancy deadlines, alter cooldown/reset durations or move their time anchor. This function does not synchronously activate trigger links.
// UNREALRED VERIFIED [trigger-attachment-20261020] Attachment lifecycle invokes this when a resolved owner is active and trigger disabled0x10 is set. Clears only the bit; activation count, cooldown/reset anchors and timers are preserved. A separate manual reverse-disable can therefore be overwritten on the next owner-state update.
int __cdecl rf_trigger_set_forward_enabled(int a1)
{
  *(_DWORD *)(a1 + 688) &= ~0x10u;
  return a1;
}

