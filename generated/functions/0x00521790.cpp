// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00521790 rf_world_decal_advance_fade_and_expiry
// UNREALRED VERIFIED [resource-pools-20261028]: Clears fading count0xA70628. For active record flag0x40000000 subtracts trunc(frame_delta*255) from alpha byte+76 when decrement<=alpha and increments fading count; otherwise sets alpha0 and deletion flag0x80000000. Flag0x08000000 subtracts frame delta from lifetime+220, marks delete when<=0. Any negative signed flags word invokes full detach0x524100. Control flow then takes saved successor and advances it again if nonnull, potentially skipping that successor this update. Finishes logical clears of scratch arrays0xA7063C/0xCFACA4 through unknown_libname_19. No clamp of negative frame delta.
_DWORD *rf_world_decal_advance_fade_and_expiry()
{
  int v1; // [esp+0h] [ebp-14h]
  int v2; // [esp+4h] [ebp-10h]
  int v3; // [esp+Ch] [ebp-8h]
  int v4; // [esp+10h] [ebp-4h]

  unk_A70628 = 0;
  v4 = unk_A7051C;
  while ( v4 )
  {
    if ( (*(_DWORD *)(v4 + 80) & 0x40000000) != 0 )
    {
      v3 = (int)(rf_frame_delta_seconds * 1.0 * 255.0);
      if ( v3 <= *(unsigned __int8 *)(v4 + 76) )
      {
        *(_BYTE *)(v4 + 76) -= v3;
        ++unk_A70628;
      }
      else
      {
        *(_BYTE *)(v4 + 76) = 0;
        *(_DWORD *)(v4 + 80) |= 0x80000000;
      }
    }
    if ( (*(_DWORD *)(v4 + 80) & 0x8000000) != 0 )
    {
      *(float *)(v4 + 220) = *(float *)(v4 + 220) - rf_frame_delta_seconds;
      if ( *(float *)(v4 + 220) <= 0.0 )
        *(_DWORD *)(v4 + 80) |= 0x80000000;
    }
    if ( *(int *)(v4 + 80) < 0 )
    {
      if ( *(_DWORD *)(v4 + 224) == unk_A7051C )
        v2 = 0;
      else
        v2 = *(_DWORD *)(v4 + 224);
      rf_world_decal_remove_spatial_links_and_recycle((_DWORD *)v4);
      v4 = v2;
    }
    if ( v4 )
    {
      if ( *(_DWORD *)(v4 + 224) == unk_A7051C )
        v1 = 0;
      else
        v1 = *(_DWORD *)(v4 + 224);
      v4 = v1;
    }
  }
  rf_pointer_array_clear_count_keep_storage(unk_A7063C);
  return rf_pointer_array_clear_count_keep_storage(dword_CFACA4);
}

