// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7C90 rf_physics_state_frame_reset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion integration, selected-row transforms, angular/tensor updates, contact velocity response and x87 gates): Cdecl physics-state P (object136). Copies global frame delta toP296;sets contact fractionP324=1 and DWORDP360 (object496 contact face)=0. DOES NOT clear whole contact or liquid/material/UID fields. FlagsP288 previous-contact bit0x08000000 becomes boolean OLD current-contact bit0x10000000;then applies mask0xAAFFFFFF,clearing bits0x01000000/0x04000000/0x10000000/0x40000000 while preserving newly rolled bit0x08000000 and other bits. Returns final flags inEAX. No pointer or time/finite validation.
unsigned int __cdecl rf_physics_state_frame_reset(int a1)
{
  unsigned int v1; // eax
  unsigned int result; // eax

  *(float *)(a1 + 296) = rf_frame_delta_seconds;
  *(float *)(a1 + 324) = 1.0;
  *(_DWORD *)(a1 + 360) = 0;
  if ( (*(_DWORD *)(a1 + 288) & 0x10000000) != 0 )
    v1 = *(_DWORD *)(a1 + 288) | 0x8000000;
  else
    v1 = *(_DWORD *)(a1 + 288) & 0xF7FFFFFF;
  *(_DWORD *)(a1 + 288) = v1;
  result = *(_DWORD *)(a1 + 288) & 0xAAFFFFFF;
  *(_DWORD *)(a1 + 288) = result;
  return result;
}

