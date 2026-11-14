// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E0C0 rf_hud_initialize_ammo_bar_bitmaps
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Sequential44ACC0 frame-zero bitmap loads of exact PE-backed names: ammo_bar.tga ->DWORD661890; ammo_bar_power.tga
// ->6618A4; noclip_ammo_bar.tga ->6618BC; ammo_signal_green.tga ->6618D4; ammo_signal_red.tga ->6618F0. Store EACH raw helper handle immediately, including failure-1; continue later
// loads regardless prior outcomes.44ACC0 inserts _0 before final extension and retains successful handles through its own contract; these are not direct unmodified filename requests.
// Then register exact no-op44E0B0 with atexit, clean4 and return raw atexit EAX rather than any bitmap handle/success aggregate. No existing-handle release, once guard, fallback
// texture, rollback or own cleanup on registration failure; repeated calls can overwrite prior stored handles after additional loads/retains.
int rf_hud_initialize_ammo_bar_bitmaps()
{
  dword_661890 = rf_hud_load_frame_zero_bitmap(aAmmoBarTga);
  dword_6618A4 = rf_hud_load_frame_zero_bitmap(aAmmoBarPowerTg);
  dword_6618BC = rf_hud_load_frame_zero_bitmap(aNoclipAmmoBarT);
  dword_6618D4 = rf_hud_load_frame_zero_bitmap(aAmmoSignalGree);
  dword_6618F0 = rf_hud_load_frame_zero_bitmap(aAmmoSignalRedT);
  return atexit(rf_hud_ammo_bitmaps_atexit_noop);
}

