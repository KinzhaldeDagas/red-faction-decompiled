// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F75A0 rf_mission_event_registry_clear
// UNREALRED VERIFIED [event-registry-crc-20261028]: Releases pointer-array storage at0x90B0E0, sets global0x663290=-1 and removed-event count0x90B0DC=0. Does not destroy event pointees.
void **rf_mission_event_registry_clear()
{
  void **result; // eax

  result = rf_pointer_array_release_storage((void **)unk_90B0E0);
  dword_663290 = -1;
  unk_90B0DC = 0;
  return result;
}

