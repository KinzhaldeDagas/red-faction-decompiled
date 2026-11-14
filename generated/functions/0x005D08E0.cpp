// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D08E0 rf_renderer_toggle_detail_textures
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, all packed-state selector branches, original-PE device-call immediates and option/cache paths): Ready global1809818 gates all work. Toggles detail option byte,then stage1 MIPFILTER18=LINEAR2 and LODBIAS19 rawfloat-1.5 when enabled;NONE0/bias0 when disabled;prints status. No texture bind/unbind,packed cache invalidation or HRESULT check. Packed modes10/11 later force stage1 MIPLINEAR independently of option;no packed mode writes stage1 LOD bias,so toggle bias persists. Not-ready EAX incidental/uninitialized.
int rf_renderer_toggle_detail_textures()
{
  int result; // eax

  if ( dword_1809818 )
  {
    rf_detail_textures_enabled = rf_detail_textures_enabled == 0;
    if ( rf_detail_textures_enabled )
    {
      (*(void (__thiscall **)(int, int, int, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
        dword_1DAEDC4,
        dword_1DAEDC4,
        1,
        18,
        2);
      (*(void (__stdcall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 19, -1.5);
      return rf_console_output_append_text_lines("Detail textures enabled.", nullptr);
    }
    else
    {
      (*(void (__thiscall **)(int, int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(
        dword_1DAEDC4,
        dword_1DAEDC4,
        1,
        18,
        0);
      (*(void (__stdcall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 1, 19, 0.0);
      return rf_console_output_append_text_lines("Detail textures disabled.", nullptr);
    }
  }
  return result;
}

