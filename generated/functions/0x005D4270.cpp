// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D4270 rf_d3d8_set_bump_environment_states
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, immediate vertex conversion, face-list lighting, bump-stage calls and original PE bytes): Cdecl six float bit-pattern arguments: luminanceScale,luminanceOffset,matrix00,matrix01,matrix10,matrix11. Capability byte1DAEDAD==0 returns0 with no writes. Otherwise bitcast helper5DF860 supplies unchanged32-bit representations for six stage0 SetTextureStageState(vtable252) writes:state22 LuminanceScale,23 LuminanceOffset,7 BumpEnvMat00,8 Mat01,9 Mat10,10 Mat11. Returns1 regardless failed HRESULT. No texture binding,bump-mode/color-op enable,packed cache invalidation,normalization or finite check. Original integer argument types represented the raw payload,not numeric float-to-integer conversion.
char __cdecl rf_d3d8_set_bump_environment_states(float a1, float a2, float a3, float a4, float a5, float a6)
{
  unsigned int v7; // eax
  unsigned int v8; // eax
  unsigned int v9; // eax
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax

  if ( !unk_1DAEDAD )
    return 0;
  v7 = rf_float32_as_uint32_bits(a1);
  (*(void (__stdcall **)(int, _DWORD, int, unsigned int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 22, v7);
  v8 = rf_float32_as_uint32_bits(a2);
  (*(void (__thiscall **)(int, int, _DWORD, int, unsigned int))(*(_DWORD *)dword_1DAEDC4 + 252))(
    dword_1DAEDC4,
    dword_1DAEDC4,
    0,
    23,
    v8);
  v9 = rf_float32_as_uint32_bits(a3);
  (*(void (__stdcall **)(int, _DWORD, int, unsigned int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 7, v9);
  v10 = rf_float32_as_uint32_bits(a4);
  (*(void (__stdcall **)(int, _DWORD, int, unsigned int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 8, v10);
  v11 = rf_float32_as_uint32_bits(a5);
  (*(void (__thiscall **)(int, int, _DWORD, int, unsigned int))(*(_DWORD *)dword_1DAEDC4 + 252))(
    dword_1DAEDC4,
    dword_1DAEDC4,
    0,
    9,
    v11);
  v12 = rf_float32_as_uint32_bits(a6);
  (*(void (__stdcall **)(int, _DWORD, int, unsigned int))(*(_DWORD *)dword_1DAEDC4 + 252))(dword_1DAEDC4, 0, 10, v12);
  return 1;
}

