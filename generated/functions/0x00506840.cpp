// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506840 rf_vclip_effect_pool_clear_for_level
// UNREALRED VERIFIED [resource-pools-20261028]: Scans128 fixed72-byte records at0x90B880; only active byte at+60==exactly1 invokes0x5067E0, then redundantly clears active byte. Does not release definitions. Returns128, not number destroyed.
int rf_vclip_effect_pool_clear_for_level()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 128; ++i )
  {
    if ( unk_90B8BC[72 * i] == 1 )
    {
      rf_vclip_effect_destroy_runtime_record((int)&unk_90B880 + 72 * i);
      unk_90B8BC[72 * i] = 0;
    }
    result = i + 1;
  }
  return result;
}

