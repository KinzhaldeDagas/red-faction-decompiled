// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C57D0 rf_d3d8_gamma_ramp_apply
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args. For eachi0..255,builds WORD primary=WORD(primaryDWORDLUT182A380[i]<<8),copies same value into local RED/GREEN/BLUE arrays atWORD offsets0/256/512,then calls device1DAEDC4 virtual slot byte72 with stdcall arguments(device,flags0,rampPointer). Does NOT duplicate low-byte bits:normal LUT255 becomesFF00,notFFFF. No separate per-channel curve,device/readiness/capability or LUT range check. API return/EAX incidental;caller gamma setter does not validate success. Other two padding WORDs in decompiler local array are not ramp entries.
int rf_d3d8_gamma_ramp_apply()
{
  int i; // [esp+0h] [ebp-60Ch]
  _WORD v2[770]; // [esp+4h] [ebp-608h] BYREF

  for ( i = 0; i < 256; ++i )
  {
    v2[i + 512] = (unsigned __int16)rf_graphics_gamma_lut_u32[i] << 8;
    v2[i + 256] = v2[i + 512];
    v2[i] = v2[i + 256];
  }
  return (*(int (__thiscall **)(int, int, _DWORD, _WORD *))(*(_DWORD *)dword_1DAEDC4 + 72))(
           dword_1DAEDC4,
           dword_1DAEDC4,
           0,
           v2);
}

