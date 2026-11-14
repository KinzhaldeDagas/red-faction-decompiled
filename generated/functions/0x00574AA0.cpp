// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574AA0 rf_bitmap_animation_metadata_query
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(handle,optionalSecondsOut),returns frame count. CRITICAL: calls574350 first,then tests40000000 on DECODED INDEX at574AB8,rather than original handle. Tagged animation handles decode modulo3000 and therefore NEVER enter animation-entry branch;ordinary-record branch treats their entry index as bitmap index and can report unrelated record metadata. For record kind1 returns BYTE+67 and optionally float(frameCount/rate76/1000),rate being frames/ms;otherwise returns1 and optional seconds1.0. Latent tagged-index branch uses entry source index and SOURCE record rate,not instance playback multiplier. No generation,occupancy/rate/count/finite validation. Earlier broad sequence-query description omitted this tag
// bug;ordinary root behavior remains as stated.
int __cdecl rf_bitmap_animation_metadata_query(unsigned int a1, float *a2)
{
  int *v3; // [esp+8h] [ebp-Ch]
  int v4; // [esp+Ch] [ebp-8h]
  unsigned int v5; // [esp+10h] [ebp-4h]

  v5 = rf_bitmap_handle_to_slot_index(a1);
  if ( (v5 & 0x40000000) != 0 )
  {
    v3 = &unk_187CD40[9 * v5];
    if ( a2 )
      *a2 = (double)*(unsigned __int8 *)(dword_1897344 + 108 * *v3 + 67)
          / *(float *)(dword_1897344 + 108 * *v3 + 76)
          / 1000.0;
    return *(unsigned __int8 *)(dword_1897344 + 108 * *v3 + 67);
  }
  else
  {
    v4 = dword_1897344 + 108 * v5;
    if ( *(_DWORD *)(v4 + 56) == 1 )
    {
      if ( a2 )
        *a2 = (double)*(unsigned __int8 *)(v4 + 67) / *(float *)(v4 + 76) / 1000.0;
      return *(unsigned __int8 *)(v4 + 67);
    }
    else
    {
      if ( a2 )
        *a2 = 1.0;
      return 1;
    }
  }
}

