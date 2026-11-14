// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F75D0 rf_mission_event_registry_update
// UNREALRED VERIFIED [event-registry-crc-20261028]: Iterates dynamic count at registry0x90B0E0, fetches each event pointer and invokes vtable byte offset12 with event in ECX and no explicit stack arguments. Called by pause-gated main level update. Count is reread each iteration; no snapshot or deletion-safety mechanism in this loop. Decompiler extra event argument is spurious.
int rf_mission_event_registry_update()
{
  int result; // eax
  _DWORD *v1; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= result )
      break;
    v1 = (_DWORD *)sub_552200(unk_90B0E0, i);
    (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v1 + 12))(*v1, *v1);
  }
  return result;
}

