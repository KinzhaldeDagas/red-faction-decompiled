// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005137F0 rf_projected_shadows_initialize
// VERIFIED: Initializes projected shadows by loading shadow01.tga into the renderer shadow texture global and resetting the frame work counter.
// UNREALRED VERIFIED [general-gap-20260830]: Loads shadow01.tga into the projected-shadow texture global and resets the per-frame work counter.
int rf_projected_shadows_initialize()
{
  int result; // eax

  result = rf_bitmap_load_with_optional_mipmap_generation("shadow01.tga", (void *)0xFFFFFFFF, 1);
  rf_projected_shadow_texture_handle = result;
  rf_projected_shadow_work_count = 0;
  return result;
}

