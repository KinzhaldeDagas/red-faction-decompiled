// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507D30 rf_rail_trail_load_alpha_bitmap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Loads exact railrifle1TrailAlpha.tga through574E90(filename,-1,1), writes returned handle including failure to663A28 and returns it. No prior-handle check/release or retry suppression.
int rf_rail_trail_load_alpha_bitmap()
{
  int result; // eax

  result = rf_bitmap_load_with_optional_mipmap_generation("railrifle1TrailAlpha.tga", (void *)0xFFFFFFFF, 1);
  dword_663A28 = result;
  return result;
}

