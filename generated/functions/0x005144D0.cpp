// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005144D0 rf_mesh_decal_pools_reset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdecl noargs. Reinitialize static intrusive pools:50collections stride48 at9287E0,free sentinel929140 links40/44,active sentinel929170;150polygons stride36 at9291A0,free sentinel92DD68 links28/32;500vertices stride28 at92A6B8,free sentinel9287C4 links20/24. FIFO-tail link records in ascending address order. Set collectionDWORD0=-1 and embedded polygonring32/36=record+4;set each polygon embedded vertexring20/24=polygon. Vertex xyz/UV0..19 and polygon payload0..19 untouched;does not zero whole records. Set free counters9287B8=50,9287BC=150,9287C0=500. No heap operations,active-handle invalidation notifications or retention of previous active records. EAX is incidental previous vertex
// free-tail fromlast append(record498),not normalized success. Must not conflate these pools with1332-byte geomod face-decal polygons.
int rf_mesh_decal_pools_reset()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]
  int k; // [esp+0h] [ebp-4h]

  unk_929168 = &unk_929140;
  unk_92916C = &unk_929140;
  for ( i = 0; i < 50; ++i )
  {
    unk_928808[12 * i] = 0;
    unk_92880C[12 * i] = 0;
    unk_9287E0[12 * i] = -1;
    unk_928800[12 * i] = (int)&unk_9287E4 + 48 * i;
    unk_928804[12 * i] = (int)&unk_9287E4 + 48 * i;
    unk_92880C[12 * i] = unk_92916C;
    unk_928808[12 * i] = (int)&unk_929140;
    *(_DWORD *)(unk_92916C + 40) = &unk_9287E0[12 * i];
    unk_92916C = &unk_9287E0[12 * i];
  }
  unk_9287B8 = 50;
  unk_929198 = &unk_929170;
  unk_92919C = &unk_929170;
  unk_92DD84 = &unk_92DD68;
  unk_92DD88 = &unk_92DD68;
  result = 0;
  for ( j = 0; j < 150; ++j )
  {
    unk_9291BC[9 * j] = 0;
    unk_9291C0[9 * j] = 0;
    unk_9291B4[9 * j] = (int)&unk_9291A0 + 36 * j;
    unk_9291B8[9 * j] = (int)&unk_9291A0 + 36 * j;
    unk_9291C0[9 * j] = unk_92DD88;
    unk_9291BC[9 * j] = (int)&unk_92DD68;
    *(_DWORD *)(unk_92DD88 + 28) = (char *)&unk_9291A0 + 36 * j;
    unk_92DD88 = (char *)&unk_9291A0 + 36 * j;
    result = 0;
  }
  dword_9287BC = 150;
  dword_9287D8 = (float *)&unk_9287C4;
  unk_9287DC = &unk_9287C4;
  for ( k = 0; k < 500; ++k )
  {
    unk_92A6CC[7 * k] = 0;
    unk_92A6D0[7 * k] = 0;
    unk_92A6D0[7 * k] = unk_9287DC;
    unk_92A6CC[7 * k] = (int)&unk_9287C4;
    result = unk_9287DC;
    *(_DWORD *)(unk_9287DC + 20) = (char *)&unk_92A6B8 + 28 * k;
    unk_9287DC = (char *)&unk_92A6B8 + 28 * k;
  }
  dword_9287C0 = 500;
  return result;
}

