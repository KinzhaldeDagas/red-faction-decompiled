// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580B20 rf_volume_visible_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Returns count DWORD of global active-volume pointer array18CD030. No preparation is performed here;value describes last prepared view.
int rf_volume_visible_count()
{
  return rf_receiver_get_first_dword(unk_18CD030);
}

