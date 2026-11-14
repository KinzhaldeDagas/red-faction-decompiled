// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A100 rf_mouse_poll_frame_snapshot_and_motion
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Always zeros relative DX/DY/DZ193A070/074/078 before initialized check. When initialized193A06D, locks and copies each16-byte pending button record193A080 into frame snapshot193A0B0, then clears pending press+4,release+8,double-click byte+1 while preserving held+0 and deadline+12. Cursor mode663F4C: reads screen cursor, converts to client coordinates, clamps to[0,width-1]/[0,height-1], optionally warps to clamped point, and under lock stores cached XY, cumulative wheel/Z193A030=message-wheel accumulator193A05C and deltas versus baseline193A0E8/E4/E0. With BOTH centering gates193A06E/F set, requests center warp only if XY moved but always stores center baseline afterward, even if warp helper declines because window inactive. Otherwise stores actual XY
// baseline; stores wheel baseline. DirectInput mode instead calls motion poll58A380. API errors/dimension validity unchecked; EAX incidental.
LONG rf_mouse_poll_frame_snapshot_and_motion()
{
  LONG result; // eax
  char *v1; // ecx
  char *v2; // edx
  HWND main_hwnd; // eax
  LONG v4; // [esp+0h] [ebp-1Ch]
  struct tagPOINT Point; // [esp+4h] [ebp-18h] BYREF
  int i; // [esp+Ch] [ebp-10h]
  LONG v7; // [esp+10h] [ebp-Ch]
  struct tagPOINT v8; // [esp+14h] [ebp-8h] BYREF

  unk_193A078 = 0;
  result = 0;
  unk_193A074 = 0;
  unk_193A070 = 0;
  if ( byte_193A06D )
  {
    EnterCriticalSection(&unk_193A044);
    for ( i = 0; i < 3; ++i )
    {
      v1 = &unk_193A080[16 * i];
      v2 = &unk_193A0B0[16 * i];
      *(_DWORD *)v2 = *(_DWORD *)v1;
      *((_DWORD *)v2 + 1) = *((_DWORD *)v1 + 1);
      *((_DWORD *)v2 + 2) = *((_DWORD *)v1 + 2);
      *((_DWORD *)v2 + 3) = *((_DWORD *)v1 + 3);
      unk_193A084[4 * i] = 0;
      unk_193A088[4 * i] = 0;
      unk_193A081[16 * i] = 0;
    }
    LeaveCriticalSection(&unk_193A044);
    if ( dword_663F4C )
    {
      v7 = unk_193A038 / 2;
      v4 = unk_193A034 / 2;
      GetCursorPos(&Point);
      main_hwnd = rf_window_get_main_hwnd();
      ScreenToClient(main_hwnd, &Point);
      v8 = Point;
      rf_integer_clamp_in_place(&v8, 0, unk_193A038 - 1);
      rf_integer_clamp_in_place(&v8.y, 0, unk_193A034 - 1);
      if ( v8 != Point )
        rf_mouse_warp_cursor_client_if_window_active(v8.x, v8.y);
      EnterCriticalSection(&unk_193A044);
      unk_193A060 = v8.x;
      unk_193A040 = v8.y;
      dword_193A030 = dword_193A05C;
      unk_193A070 = v8.x - unk_193A0E8;
      unk_193A074 = v8.y - unk_193A0E4;
      unk_193A078 = dword_193A05C - unk_193A0E0;
      LeaveCriticalSection(&unk_193A044);
      if ( unk_193A06F && unk_193A06E )
      {
        if ( unk_193A070 || unk_193A074 )
          rf_mouse_warp_cursor_client_if_window_active(v7, v4);
        result = v7;
        unk_193A0E8 = v7;
        unk_193A0E4 = v4;
      }
      else
      {
        unk_193A0E8 = v8.x;
        result = v8.y;
        unk_193A0E4 = v8.y;
      }
      unk_193A0E0 = dword_193A030;
    }
    else
    {
      return rf_mouse_poll_directinput_motion();
    }
  }
  return result;
}

