// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005265A0 rf_renderer_reset_light_records_when_enabled
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): No args void. If master rf_renderer_lights_enabled==0 return with NO writes. Else suppressionDWORD663B0C=0, increment light-change serial (wrap native32), initialize common sentinelD03608 prev/next toself and category1 sentinelD03720 toself, zero renderer object count and active-world count, memset rf_renderer_light_records exactly0x47F90 bytes, call528C20 to clear validityBYTE D035FC and active countD035E8 again. Does not unlink/free former records or spill nodes, clear additional receiver ringD035F0 or reset master enable. Assumes lifecycle ownership handled elsewhere; no full spatial-tree reconstruction.
void rf_renderer_reset_light_records_when_enabled()
{
  if ( rf_renderer_lights_enabled )
  {
    dword_663B0C = 0;
    ++rf_renderer_light_change_serial;
    rf_renderer_common_light_list_sentinel = &rf_renderer_common_light_list_sentinel;
    unk_D0360C = &rf_renderer_common_light_list_sentinel;
    rf_renderer_category1_light_list_sentinel = &rf_renderer_category1_light_list_sentinel;
    unk_D03724 = &rf_renderer_category1_light_list_sentinel;
    rf_renderer_object_count = 0;
    rf_light_active_world_count = 0;
    memset(rf_renderer_light_records, 0, 0x47F90u);
    rf_light_invalidate_active_world_list();
  }
}

