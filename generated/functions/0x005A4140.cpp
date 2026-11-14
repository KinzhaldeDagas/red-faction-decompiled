// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4140 rf_renderer_linear_depth_fade_byte
// UNREALRED VERIFIED [face-batch-20261028]: Computes float255-depth*global0x187CD00,clamps0..255 through0x40D620,converts through floating-bit helper0x5A4190 and returns integerbyte. No base fog-start offset or table lookup in this body; caller writes result into vertex specular alpha.
int __cdecl rf_renderer_linear_depth_fade_byte(float a1)
{
  int v2; // [esp+8h] [ebp-4h] BYREF

  *(float *)&v2 = 255.0 - a1 * unk_187CD00;
  rf_float_clamp_in_place((float *)&v2, 0.0, 255.0);
  return rf_float_to_byte_add_12582912_bits(*(float *)&v2);
}

