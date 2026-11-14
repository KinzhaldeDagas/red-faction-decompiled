// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1F20 rf_explosion_graph_pool_initialize
// UNREALRED VERIFIED [resource-pools-20261028]: Clears active head0x814340/free head0x814344; memsets eight308-byte graph records at0x814350 (2464 bytes), links all into circular free list using next+300/prev+304. Does not destroy existing child emitters; use cleanup before reinitializing a live pool. Returns incidental null.
void *rf_explosion_graph_pool_initialize()
{
  void *result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_814344 = 0;
  unk_814340 = 0;
  result = memset(&unk_814350, 0, 0x9A0u);
  for ( i = 0; i < 8; ++i )
  {
    if ( unk_814344 )
    {
      unk_814480[77 * i] = *(_DWORD *)(unk_814344 + 304);
      unk_81447C[77 * i] = unk_814344;
      *(_DWORD *)(*(_DWORD *)(unk_814344 + 304) + 300) = (char *)&unk_814350 + 308 * i;
      *(_DWORD *)(unk_814344 + 304) = (char *)&unk_814350 + 308 * i;
    }
    else
    {
      unk_81447C[77 * i] = (int)&unk_814350 + 308 * i;
      unk_814480[77 * i] = (int)&unk_814350 + 308 * i;
      unk_814344 = (char *)&unk_814350 + 308 * i;
    }
    result = nullptr;
  }
  return result;
}

