// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C46B0 rf_geomod_impact_chunks_render_for_room
// UNREALRED VERIFIED [room-render-20261028]: Traverses impact-chunk circular list sentinel rf_geomod_impact_chunk_active_head, saves next+0 before any render/removal. Only chunks with room pointer+108 equal input call0x4C4600. Does not sort or globally clear list; return incidental successor.
int __cdecl rf_geomod_impact_chunks_render_for_room(int a1)
{
  int result; // eax
  int *i; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  for ( i = (int *)rf_geomod_impact_chunk_active_head; ; i = (int *)v3 )
  {
    result = *i;
    v3 = *i;
    if ( i == &rf_geomod_impact_chunk_active_head )
      break;
    if ( i[27] == a1 )
      rf_geomod_impact_chunk_render_or_expire((int)i);
  }
  return result;
}

