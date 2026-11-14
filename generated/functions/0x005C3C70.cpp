// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C3C70 rf_d3d8_check_texture_format
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Calls IDirect3D8 vtable+40 (CheckDeviceFormat) with current adapter 1DAEE0C, device type 1, adapter format 1DAE8F8, usage 0, resource type 3 (texture), and caller check-format. Returns true only for HRESULT exactly zero. Does not create a texture or validate device pointer.
bool __cdecl rf_d3d8_check_texture_format(int a1)
{
  return (*(int (__stdcall **)(_DWORD *, _DWORD, int, _DWORD, _DWORD, int, int))(*dword_1DAEDC0 + 40))(
           dword_1DAEDC0,
           unk_1DAEE0C,
           1,
           unk_1DAE8F8,
           0,
           3,
           a1) == 0;
}

