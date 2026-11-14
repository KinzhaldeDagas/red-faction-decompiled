// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A380 rf_mouse_poll_directinput_motion
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Zeros local16-byte state and global relative deltas. If DirectInput-ready193A06C, GetDeviceState(size16) fills XYZ/button bytes. Errors0x8007001E or0x8007000C trigger Sleep500ms then Acquire; successful Acquire retries state read, with no retry limit. Negative final HRESULT leaves deltas0; success stores first three LONGs as deltas. Returned button bytes are ignored; RF buttons come from Windows callback. Adds deltas to cached X/Y/cumulative wheel-Z, clamps XY against configured dimensions. No critical section inside or positive-size check. EAX incidental cached Y, not an HRESULT contract.
int rf_mouse_poll_directinput_motion()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-1Ch]
  char v2; // [esp+7h] [ebp-15h]
  int v3; // [esp+8h] [ebp-14h] BYREF
  int v4; // [esp+Ch] [ebp-10h]
  int v5; // [esp+10h] [ebp-Ch]
  int v6; // [esp+14h] [ebp-8h]

  v1 = 0;
  v3 = 0;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  unk_193A078 = 0;
  unk_193A074 = 0;
  unk_193A070 = 0;
  result = unk_193A06C;
  if ( unk_193A06C )
  {
    v2 = 1;
    while ( v2 )
    {
      v2 = 0;
      v1 = (*(int (__stdcall **)(_DWORD *, int, int *))(*dword_193A068 + 36))(dword_193A068, 16, &v3);
      if ( v1 == -2147024866 || v1 == -2147024884 )
      {
        Sleep(0x1F4u);
        v1 = (*(int (__stdcall **)(_DWORD *))(*dword_193A068 + 28))(dword_193A068);
        if ( v1 >= 0 )
          v2 = 1;
      }
    }
    if ( v1 < 0 )
    {
      unk_193A078 = 0;
      unk_193A074 = 0;
      unk_193A070 = 0;
    }
    else
    {
      unk_193A070 = v3;
      unk_193A074 = v4;
      unk_193A078 = v5;
    }
    dword_193A060 += unk_193A070;
    dword_193A040 += unk_193A074;
    dword_193A030 += unk_193A078;
    if ( dword_193A060 < 0 )
      dword_193A060 = 0;
    if ( dword_193A040 < 0 )
      dword_193A040 = 0;
    if ( dword_193A060 >= dword_193A038 )
      dword_193A060 = dword_193A038 - 1;
    result = dword_193A040;
    if ( dword_193A040 >= dword_193A034 )
      dword_193A040 = dword_193A034 - 1;
  }
  return result;
}

