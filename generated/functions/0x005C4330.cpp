// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C4330 rf_d3d8_apply_vertex_fog_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Applies cached fog globals. Disabled: SetRenderState(35,0), (140,0), (48,0), disabling table mode, vertex mode and range fog. Enabled: packs opaque ARGB from three cached RGB bytes, sets fog color state34, linear vertex mode state140=3, and float bit patterns for start/end states36/37. Enabled branch does NOT reset table mode or range fog and does not write FOGENABLE state28. All device calls use stack-pushed COM arguments despite some thiscall pseudocode. No HRESULT checks; EAX is last call result.
int rf_d3d8_apply_vertex_fog_state()
{
  float v1; // [esp+3Ch] [ebp-Ch]

  if ( byte_187CCF0 )
  {
    (*(void (__stdcall **)(int, int, unsigned int))(*(_DWORD *)dword_1DAEDC4 + 200))(
      dword_1DAEDC4,
      34,
      (unsigned __int8)(__int64)((double)(unsigned __int8)byte_187CCF3 / 255.0 * 255.0)
    | ((unsigned __int8)(__int64)((double)(unsigned __int8)byte_187CCF2 / 255.0 * 255.0) << 8)
    | ((unsigned __int8)(__int64)((double)(unsigned __int8)byte_187CCF1 / 255.0 * 255.0) << 16)
    | 0xFF000000);
    (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 140, 3);
    v1 = flt_187CCFC;
    (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 36, LODWORD(flt_187CCF8));
    return (*(int (__thiscall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(
             dword_1DAEDC4,
             dword_1DAEDC4,
             37,
             LODWORD(v1));
  }
  else
  {
    (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 35, 0);
    (*(void (__thiscall **)(int, int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(
      dword_1DAEDC4,
      dword_1DAEDC4,
      140,
      0);
    return (*(int (__stdcall **)(int, int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 200))(dword_1DAEDC4, 48, 0);
  }
}

