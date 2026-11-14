// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D0850 rf_renderer_toggle_trilinear_filtering
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, all packed-state selector branches, original-PE device-call immediates and option/cache paths): Only when device-ready global1809818 nonzero,toggles byte1E014E7 by logical NOT,sets stage0 MIPFILTER state18 toLINEAR2 when enabled/POINT1 when disabled,then prints matching status via56DD50. No packed-cache invalidation,texture binding,flush,retry or HRESULT check. No device writes when not ready;inferred EAX on that path uninitialized/incidental. Packed dispatcher does not otherwise write stage0 MIP filter.
int rf_renderer_toggle_trilinear_filtering()
{
  int result; // eax

  if ( dword_1809818 )
  {
    byte_1E014E7 = byte_1E014E7 == 0;
    if ( byte_1E014E7 )
    {
      (*(void (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
        dword_1DAEDC4,
        dword_1DAEDC4,
        0,
        18,
        2);
      return rf_console_output_append_text_lines("Trilinear filtering enabled.", nullptr);
    }
    else
    {
      (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 18, 1);
      return rf_console_output_append_text_lines("Trilinear filtering disabled.", nullptr);
    }
  }
  return result;
}

