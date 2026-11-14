// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005786A0 rf_bitmap_snapshot_active_list_head
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): No args. Copies current pointer1897434 (ordinary-record list head) to snapshot1897458 and returns that pointer. Does not iterate,pin,mark,add references or save all bitmap records. Later snapshot semantics not inferred here.
void *__cdecl rf_bitmap_snapshot_active_list_head()
{
  dword_1897458 = dword_1897434;
  return (void *)dword_1897434;
}

