// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505340 rf_trigger_set_reverse_disabled
// UNREALRED VERIFIED [trigger-attachment-20261020] Attachment lifecycle invokes this when owner common inactive is set and trigger disabled0x10 is clear. Sets only disabled0x10. Trigger common inactive0x4000 is distinct and does not by itself cancel timers or force this bit.
int __cdecl rf_trigger_set_reverse_disabled(int a1)
{
  *(_DWORD *)(a1 + 688) |= 0x10u;
  return a1;
}

