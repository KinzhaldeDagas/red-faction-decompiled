// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005271D0 rf_renderer_set_global_light_triplet_663b1c
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl three BY-VALUE floats. Increment global light-change serial FIRST (nativeDWORD wrap), then copy bit patterns into floats663B1C,663B20,663B24 in argument order. Return incremented serial EAX. No clamping, normalization, active-list invalidation call, light allocation or record-specific mutation. Component semantic interpretation left to consumers; these are not three pointers.
unsigned int __cdecl rf_renderer_set_global_light_triplet_663b1c(float a1, float a2, float a3)
{
  unsigned int result; // eax

  result = ++rf_renderer_light_change_serial;
  flt_663B1C = a1;
  flt_663B20 = a2;
  flt_663B24 = a3;
  return result;
}

