// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506DD0 rf_vclip_effect_pool_clear_runtime
// UNREALRED VERIFIED [resource-pools-20261028]: Scans128 records at0x90B880 stride72 and destroys only records whose active byte+60==1 through0x5067E0. Retains pool and definitions; returns128. Shared destroy helper clears active byte.
int rf_vclip_effect_pool_clear_runtime()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 128; ++i )
  {
    if ( unk_90B8BC[72 * i] == 1 )
      rf_vclip_effect_destroy_runtime_record((int)&unk_90B880 + 72 * i);
    result = i + 1;
  }
  return result;
}

