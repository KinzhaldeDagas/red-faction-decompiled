// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A840 rf_mouse_shutdown
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): When initialized, releases DirectInput device/interface, clears mouse initialized and deletes critical section. Does not unregister Windows callback, clear motion/button state, free the loaded DLL or reset centering/cursor-mode policy.
void __cdecl rf_mouse_shutdown()
{
  if ( byte_193A06D )
  {
    rf_mouse_release_directinput_interfaces();
    byte_193A06D = 0;
    DeleteCriticalSection(&unk_193A044);
  }
}

