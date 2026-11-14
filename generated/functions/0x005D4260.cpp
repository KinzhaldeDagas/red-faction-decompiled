// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D4260 rf_renderer_get_auxiliary_capability_byte
// UNREALRED VERIFIED [renderer-polygons-20261028]: Returns byte0x1DAEDAD unchanged. Neighbor0x5D4270 uses this byte to gate six device state writes; this accessor does not query device or normalize to boolean.
char rf_renderer_get_auxiliary_capability_byte()
{
  return unk_1DAEDAD;
}

