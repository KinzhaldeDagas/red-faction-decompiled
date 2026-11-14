// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C2050 rf_explosion_graph_pool_destroy_and_reset
// UNREALRED VERIFIED [resource-pools-20261028]: Traverses circular active graph list0x814340; per graph reads definition pointer+296 and emitter count definition+124, destroys nonnull emitter pointers at graph+272+4*j and clears them. Then clears both heads, memsets eight308-byte records and rebuilds circular free list with links+300/+304. Returns incidental final record address, not count. No definition/count bounds validation here.
char *rf_explosion_graph_pool_destroy_and_reset()
{
  char *result; // eax
  int v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int j; // [esp+8h] [ebp-4h]
  int k; // [esp+8h] [ebp-4h]

  for ( i = unk_814340; i; i = v1 )
  {
    for ( j = 0; j < *(_DWORD *)(*(_DWORD *)(i + 296) + 124); ++j )
    {
      if ( *(_DWORD *)(i + 4 * j + 272) )
      {
        rf_particle_emitter_destroy(*(_DWORD *)(i + 4 * j + 272));
        *(_DWORD *)(i + 4 * j + 272) = 0;
      }
    }
    if ( *(_DWORD *)(i + 300) == unk_814340 )
      v1 = 0;
    else
      v1 = *(_DWORD *)(i + 300);
  }
  unk_814344 = 0;
  unk_814340 = 0;
  result = (char *)memset(&unk_814350, 0, 0x9A0u);
  for ( k = 0; k < 8; ++k )
  {
    if ( unk_814344 )
    {
      unk_814480[77 * k] = *(_DWORD *)(unk_814344 + 304);
      unk_81447C[77 * k] = unk_814344;
      *(_DWORD *)(*(_DWORD *)(unk_814344 + 304) + 300) = (char *)&unk_814350 + 308 * k;
      result = (char *)&unk_814350 + 308 * k;
      *(_DWORD *)(unk_814344 + 304) = result;
    }
    else
    {
      unk_81447C[77 * k] = (int)&unk_814350 + 308 * k;
      unk_814480[77 * k] = (int)&unk_814350 + 308 * k;
      result = (char *)&unk_814350 + 308 * k;
      unk_814344 = result;
    }
  }
  return result;
}

