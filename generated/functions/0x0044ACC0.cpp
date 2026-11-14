// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044ACC0 rf_hud_load_frame_zero_bitmap
// UNREALRED VERIFIED [hud-frame-zero-20261027] Weapon-table HUD bitmap loader: saves the final dot suffix, truncates the base at that dot, then formats basename + _0 + original suffix before calling 0x574E90; no suffix yields basename_0. Example reticle.tga becomes reticle_0.tga, preserving the extension. Successful bitmap handles are retained via 0x571C60. Native reticle fields +584/+588/+592 are populated through this helper from 0x508990; do not silently substitute an unrelated bitmap when name construction fails.
int __cdecl rf_hud_load_frame_zero_bitmap(char *Source)
{
  int v2; // [esp+0h] [ebp-A4h]
  char Destination[132]; // [esp+4h] [ebp-A0h] BYREF
  char v4[16]; // [esp+88h] [ebp-1Ch] BYREF
  char *last_char_wrapper; // [esp+9Ch] [ebp-8h]
  int v6; // [esp+A0h] [ebp-4h]

  v6 = 0;
  if ( !Source )
    return -1;
  v6 = 0;
  strncpy(Destination, Source, 0x80u);
  last_char_wrapper = rf_cstring_find_last_char_wrapper(Destination, 46);
  if ( last_char_wrapper )
  {
    strncpy(v4, last_char_wrapper, 0x10u);
    *last_char_wrapper = 0;
  }
  else
  {
    v4[0] = 0;
  }
  sprintf(Destination, "%s_%d%s", Destination, v6, v4);
  v2 = rf_bitmap_load_with_optional_mipmap_generation(Destination, (void *)0xFFFFFFFF, 0);
  if ( v2 >= 0 )
    rf_renderer_bind_texture_for_level_warmup(v2);
  return v2;
}

