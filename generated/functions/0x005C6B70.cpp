// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6B70 rf_positional_sound_use_hardware_3d_disabled
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Unconditionally returns byte zero. Higher positional instance management therefore follows software gain/pan/Doppler paths at callers testing this function for 1. Distinct from the low-level 3D mode-byte getter.
char rf_positional_sound_use_hardware_3d_disabled()
{
  return 0;
}

