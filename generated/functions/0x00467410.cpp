// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467410 rf_intro_panel_frame_allow_mouse_centering
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg;frame dispatcher passes ignored suppressInput byte. Call mouse_set_centering_permission_byte(1) with one32-bit stack arg,cleanup4. No
// rendering,loading,position test or use of caller's suppression argument in this body. Existing int type retained;delegate only promises its actual return ABI. False library flag
// cleared:compiled panel4 frame dispatcher calls this RF mouse-permission callback.
char rf_intro_panel_frame_allow_mouse_centering()
{
  return rf_mouse_set_centering_permission_byte(1);
}

