// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C680 rf_entity_set_state814_mask40000_with_sound86
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl entity. OR Entity DWORD2068 with40000 unconditionally, then object-view sound(entity,by-value common position60 XYZ,event86,float1.5,float0.0), caller pops28
// bytes. No existing-bit/runtime/NULL guard or powerup-node mutation; returns sound delegate EAX. Flag remains set regardless of sound result; incoming ECX unused as input.
int __cdecl rf_entity_set_state814_mask40000_with_sound86(int a1)
{
  int v1; // ecx
  float v3[3]; // [esp-10h] [ebp-1Ch] BYREF
  int v4; // [esp-4h] [ebp-10h]
  float v5; // [esp+0h] [ebp-Ch]
  float v6; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  v7 = v1;
  *(_DWORD *)(a1 + 2068) |= 0x40000u;
  v6 = 0.0;
  v5 = 1.5;
  v4 = 86;
  rf_vector3_copy_return_destination(v3, (float *)(a1 + 60));
  return rf_sound_event_play_for_object_view(a1, v3[0], SLODWORD(v3[1]), SLODWORD(v3[2]), v4, v5, v6);
}

