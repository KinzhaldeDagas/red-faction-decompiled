// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5890 rf_d3d8_set_stage0_mip_filter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): For selector 0 or 1 calls the device vtable+0xFC with (device, stage 0, texture-stage-state 18, value 1 or 2 respectively), selecting point or linear mip filtering. All four args are stack-pushed, despite the second branch misleading thiscall inference. Other selectors do nothing; no device-NULL or HRESULT handling. Caller 573CC0 gates dispatch on backend code 102.
int __cdecl rf_d3d8_set_stage0_mip_filter(int a1)
{
  int result; // eax

  result = a1;
  if ( !a1 )
    return (*(int (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 18, 1);
  if ( a1 == 1 )
    return (*(int (__thiscall **)(int, int, _DWORD, int, int))(*(_DWORD *)dword_1DAEDC4 + 252))(
             dword_1DAEDC4,
             dword_1DAEDC4,
             0,
             18,
             2);
  return result;
}

