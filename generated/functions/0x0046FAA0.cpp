// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FAA0 rf_demo_upsell_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Resets full-screen viewport, then unchecked index6F910C selects handle6F9100[index]. If signed handle>=0, obtains bitmap dimensions and blits full source bitmap to physical
// screen width/height at(0,0), source offsets0, flags0/0, style187CD34. Native blit has12 stack arguments/48-byte cleanup. No index guard, aspect preservation, color setup or
// ownership changes.
int rf_demo_upsell_render()
{
  int result; // eax
  int physical_screen_width; // eax
  int physical_screen_height; // [esp-20h] [ebp-28h]
  int v3; // [esp-14h] [ebp-1Ch]
  int v4; // [esp-10h] [ebp-18h]
  int v5; // [esp-4h] [ebp-Ch]
  int v6; // [esp+0h] [ebp-8h] BYREF
  int v7; // [esp+4h] [ebp-4h] BYREF

  rf_renderer_reset_viewport_full_screen();
  result = unk_6F910C;
  if ( dword_6F9100[unk_6F910C] >= 0 )
  {
    rf_bitmap_get_resolved_dimensions(dword_6F9100[unk_6F910C], &v6, &v7);
    v5 = unk_187CD34;
    v4 = v7;
    v3 = v6;
    physical_screen_height = rf_renderer_get_physical_screen_height();
    physical_screen_width = rf_renderer_get_physical_screen_width();
    return rf_bitmap_blit_subrectangle_backend_dispatch(
             dword_6F9100[unk_6F910C],
             0,
             0,
             physical_screen_width,
             physical_screen_height,
             0,
             0,
             v3,
             v4,
             0,
             0,
             v5);
  }
  return result;
}

