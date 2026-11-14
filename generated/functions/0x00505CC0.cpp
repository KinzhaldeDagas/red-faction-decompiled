// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505CC0 rf_trigger_is_auto
// UNREALRED VERIFIED [hud-trigger-lifecycle] Returns whether runtime trigger flag 0x04 is set; entity scans skip these triggers.
// UNREALRED VERIFIED [auto-trigger-use-ownership] Tests runtime trigger flag 0x04. This serialized flag, not the trigger class string, selects dedicated auto-trigger ownership.
bool __cdecl rf_trigger_is_auto(int a1)
{
  return (*(_DWORD *)(a1 + 688) & 4) != 0;
}

