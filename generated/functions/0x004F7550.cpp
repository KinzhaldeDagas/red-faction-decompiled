// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7550 rf_mission_event_registry_initialize
// UNREALRED VERIFIED [event-registry-crc-20261028]: Clears/frees pointer-array backing storage at0x90B0E0; sets byte0x90B054=0, dword0x90B0D8=-1, dword0x90B050=0, removed-event count0x90B0DC=0, byte0x90B055=1. Registers0x4F73D0 with atexit, returns registration result.
int rf_mission_event_registry_initialize()
{
  rf_pointer_array_release_storage((void **)unk_90B0E0);
  unk_90B054 = 0;
  unk_90B0D8 = -1;
  unk_90B050 = 0;
  unk_90B0DC = 0;
  unk_90B055 = 1;
  return atexit(rf_mission_event_registry_atexit_cleanup);
}

