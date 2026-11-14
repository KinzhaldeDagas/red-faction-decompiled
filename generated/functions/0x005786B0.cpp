// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005786B0 rf_bitmap_warm_textures_from_active_record_list
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): No args. Walks ordinary record list from head1897434 until sentinel18973E0,following DWORD next+84 AFTER each bind. Computes signed(record-base1897344)/108,indexes back into record table,reads handle+36 and calls571C60 renderer warmup binder. Does not walk unused slots or animation-instance list and adds no own suppression-flag check. Empty list returns head pointer;nonempty EAX is last binder incidental result,not bind count. No cycle/NULL/list-alignment/generation guard or stable snapshot.
int __cdecl rf_bitmap_warm_textures_from_active_record_list()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = dword_1897434;
  for ( i = dword_1897434; (_UNKNOWN *)i != &unk_18973E0; i = *(_DWORD *)(i + 84) )
    rf_renderer_bind_texture_for_level_warmup(*(_DWORD *)(dword_1897344 + 108 * ((i - dword_1897344) / 108) + 36));
  return result;
}

