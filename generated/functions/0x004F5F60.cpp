// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5F60 rf_restore_queue_object_identifier_fixup
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Append saved identifier to0x88E8D0 and destination dword address to parallel0x8935B8 at count0x88E7C8, then increment count. No destination write or object resolution here, including sentinel-1. No capacity check in body; caller manages queue epoch.
int __cdecl rf_restore_queue_object_identifier_fixup(int a1, int a2)
{
  unk_88E8D0[unk_88E7C8] = a1;
  unk_8935B8[unk_88E7C8++] = a2;
  return a2;
}

