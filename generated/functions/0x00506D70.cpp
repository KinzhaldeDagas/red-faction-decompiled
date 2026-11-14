// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506D70 rf_vclip_preload_liquid_splashes_if_level_has_liquid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Calls rf_level_has_liquid_room; ONLY result AL EXACT1 preloads five cached IDs through507860, in order90B830(small),90B824(medium),90B834(large),90B828(huge),90B82C(bullet). Other result bytes skip all calls. Negative cached IDs are forwarded, rejected by507860; no local upper bound/check, scene-specific507960 call, liquid-room iteration or VClip spawn.
void rf_vclip_preload_liquid_splashes_if_level_has_liquid()
{
  if ( rf_level_has_liquid_room() == 1 )
  {
    rf_vclip_preload_bitmap_and_vfx_stub(unk_90B830);
    rf_vclip_preload_bitmap_and_vfx_stub(unk_90B824);
    rf_vclip_preload_bitmap_and_vfx_stub(unk_90B834);
    rf_vclip_preload_bitmap_and_vfx_stub(unk_90B828);
    rf_vclip_preload_bitmap_and_vfx_stub(unk_90B82C);
  }
}

