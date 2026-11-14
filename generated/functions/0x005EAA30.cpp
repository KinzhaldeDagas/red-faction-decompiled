// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EAA30 rf_world_depth_fog_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl(cameraZ,fogSlope):float value=255-cameraZ*fogSlope;clamps in place[0,255],passes to legacy add12582912 bit-based float-to-byte helper,returns helper EAX (world pass consumes AL into specular alpha/fog byte23). No exp fog,near/start offset or global fog-enable check;rounding follows helper,not C truncation. Does not modify caller values.
int __cdecl rf_world_depth_fog_byte(float a1, float a2)
{
  int v3; // [esp+8h] [ebp-4h] BYREF

  *(float *)&v3 = 255.0 - a1 * a2;
  rf_float_clamp_in_place((float *)&v3, 0.0, 255.0);
  return rf_float_to_byte_add_12582912_bits(*(float *)&v3);
}

