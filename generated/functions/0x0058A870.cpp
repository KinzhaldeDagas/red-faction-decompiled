// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A870 rf_mouse_release_directinput_interfaces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): If device193A068 exists, Unacquire and Release then NULL pointer. If DirectInput interface193A064 exists, Release then NULL pointer. Clears DirectInput-ready193A06C. DLL module handle193A07C remains loaded. EAX varies by last release or prior register state; no consistent success status.
int rf_mouse_release_directinput_interfaces()
{
  int result; // eax

  if ( dword_193A068 )
  {
    (*(void (__stdcall **)(_DWORD *))(*dword_193A068 + 32))(dword_193A068);
    result = (*(int (__stdcall **)(_DWORD *))(*dword_193A068 + 8))(dword_193A068);
    dword_193A068 = nullptr;
  }
  if ( dword_193A064 )
  {
    result = (*(int (__thiscall **)(LPVOID, LPVOID))(*(_DWORD *)dword_193A064 + 8))(dword_193A064, dword_193A064);
    dword_193A064 = nullptr;
  }
  unk_193A06C = 0;
  return result;
}

