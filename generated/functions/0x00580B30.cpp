// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580B30 rf_volume_visible_at_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Returns pointer stored at active-list backing+4*index via unchecked array slot helper552200. No negative/index/count or NULL checks;borrowed volume owned by18CCFF4.
int __cdecl rf_volume_visible_at_unchecked(int a1)
{
  return *(_DWORD *)sub_552200(unk_18CD030, a1);
}

