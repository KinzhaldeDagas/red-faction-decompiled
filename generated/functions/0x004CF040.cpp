// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CF040 rf_underwater_particles_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Cdecl noargs. Loads "glowball.tga" with arguments -1,1 and stores returned bitmap handle in DWORD 0x662E04, with no failure check here. Sets base RGBA at 0x872A68 to
// (60,90,70,255). Initializes all 1024 records at 0x872A88 with stride32: position+0 and velocity+12 zero, radius+24 sampled from binary32 endpoints 0.02 and 0.05000000074505806,
// RGB+28/+29/+30 independently assigned low bytes of trunc(base_channel + unit_sample*20 -10). Unit helper 0x567730 returns F32(rand()/32768.0), not division by32767. No per-record
// alpha+31 write in this initializer.
// Does not change active count 0x662DFC (original initialized-data default1024), enable BYTE 0x662E00, bounds/radius globals, or static-construction flags. Ends by arming shared
// deadline 0x872A74 through signed-millisecond helper with offset -1; this is a helper call, not an explicit raw timestamp=-1 store. Returns that helper's incidental EAX. Record
// constructor 0x4CF9B0 is a no-op and does not replace this explicit initialization.
int rf_underwater_particles_initialize()
{
  double v1; // [esp+Ch] [ebp-28h]
  double v2; // [esp+18h] [ebp-1Ch]
  double v3; // [esp+24h] [ebp-10h]
  int i; // [esp+30h] [ebp-4h]

  flt_662E04 = rf_bitmap_load_with_optional_mipmap_generation("glowball.tga", (void *)0xFFFFFFFF, 1);
  rf_color4_set_bytes_return_destination(&unk_872A68, 60, 90, 70, 255);
  for ( i = 0; i < 1024; ++i )
  {
    rf_vector3_zero_return_destination((float *)&unk_872A88 + 8 * i);
    rf_vector3_set_components_thiscall((float *)&unk_872A94 + 8 * i, 0.0, 0.0, 0.0);
    *((float *)&unk_872AA0 + 8 * i) = rf_random_float_range(0.02, 0.050000001);
    v3 = (double)unk_872A68;
    unk_872AA4[32 * i] = (int)(sub_567730() * 20.0 - 10.0 + v3);
    v2 = (double)unk_872A69;
    unk_872AA5[32 * i] = (int)(sub_567730() * 20.0 - 10.0 + v2);
    v1 = (double)unk_872A6A;
    unk_872AA6[32 * i] = (int)(sub_567730() * 20.0 - 10.0 + v1);
  }
  return rf_replicator_arm_milliseconds(&unk_872A74, -1);
}

