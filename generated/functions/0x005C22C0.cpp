// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C22C0 rf_d3d8_present_and_recover_device
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Flushes pending immediate buffers, ends active scene, and calls Present: windowed flag664A00 uses stored source/dest RECT and HWND, otherwise all NULL. Ignores Present HRESULT. If TestCooperativeLevel equals0x88760869, releases vertex/index buffers, calls Reset with presentation parameters, then recreates/binds main buffers; Reset HRESULT unchecked. Afterwards gets backbuffer0, locks stored RECT664A18 with flag0x8000, unlocks/releases it, and begins next scene/reset batch counters. Backbuffer/lock return values unchecked. The post-Present lock/unlock is present even without recovery; no pixel copy.
void rf_d3d8_present_and_recover_device()
{
  int v0; // [esp+4h] [ebp-Ch] BYREF
  _BYTE v1[8]; // [esp+8h] [ebp-8h] BYREF

  if ( unk_1E014E5 )
    rf_renderer_flush_immediate_buffers();
  rf_d3d8_end_scene_if_active();
  if ( byte_664A00 )
    (*(void (__stdcall **)(int, struct tagRECT *, struct tagRECT *, HWND, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 60))(
      dword_1DAEDC4,
      &unk_1DAE8E4,
      &unk_1DAE8E4,
      unk_1DAEDF8,
      0);
  else
    (*(void (__stdcall **)(int, _DWORD, _DWORD, _DWORD, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 60))(
      dword_1DAEDC4,
      0,
      0,
      0,
      0);
  if ( (*(int (__thiscall **)(int, int))(*(_DWORD *)dword_1DAEDC4 + 12))(dword_1DAEDC4, dword_1DAEDC4) == -2005530519 )
  {
    if ( dword_1DAEDB0 )
      (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB0 + 8))(dword_1DAEDB0);
    if ( dword_1DAEDB4 )
      (*(void (__stdcall **)(_DWORD *))(*dword_1DAEDB4 + 8))(dword_1DAEDB4);
    (*(void (__thiscall **)(int, int, void *))(*(_DWORD *)dword_1DAEDC4 + 56))(
      dword_1DAEDC4,
      dword_1DAEDC4,
      &unk_1DAE914);
    rf_d3d8_create_and_bind_main_geometry_buffers();
  }
  (*(void (__stdcall **)(int, _DWORD, _DWORD, int *))(*(_DWORD *)dword_1DAEDC4 + 64))(dword_1DAEDC4, 0, 0, &v0);
  (*(void (__stdcall **)(int, _BYTE *, void *, int))(*(_DWORD *)v0 + 36))(v0, v1, &unk_664A18, 0x8000);
  (*(void (__stdcall **)(int))(*(_DWORD *)v0 + 40))(v0);
  (*(void (__thiscall **)(int, int))(*(_DWORD *)v0 + 8))(v0, v0);
  rf_d3d8_begin_scene_reset_batch_counts();
}

