// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F73D0 rf_mission_event_registry_atexit_cleanup
// UNREALRED VERIFIED [event-registry-crc-20261028]: Releases dynamic pointer-array storage at0x90B0E0 via0x517F40 and sets removed-event count0x90B0DC=0. Does not invoke event destructors or free pointed event objects.
void __cdecl rf_mission_event_registry_atexit_cleanup()
{
  rf_pointer_array_release_storage((void **)unk_90B0E0);
  unk_90B0DC = 0;
}

