// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00522800 rf_world_decal_pool_acquire_record
// UNREALRED VERIFIED [resource-pools-20261028]: Returns0 when circular free head0xA70620 empty. Otherwise unlinks first free record via+224/+228, inserts into active list0xA7051C, increments0xA70624 and returns record. Does not initialize payload/flags or allocate heap storage. Caller must populate fields.
int rf_world_decal_pool_acquire_record()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = unk_A70620;
  if ( unk_A70620 )
  {
    if ( *(_DWORD *)(unk_A70620 + 224) == unk_A70620 )
    {
      *(_DWORD *)(unk_A70620 + 224) = 0;
      *(_DWORD *)(v1 + 228) = 0;
      unk_A70620 = 0;
    }
    else
    {
      unk_A70620 = *(_DWORD *)(unk_A70620 + 224);
      *(_DWORD *)(*(_DWORD *)(v1 + 228) + 224) = *(_DWORD *)(v1 + 224);
      *(_DWORD *)(*(_DWORD *)(v1 + 224) + 228) = *(_DWORD *)(v1 + 228);
      *(_DWORD *)(v1 + 224) = 0;
      *(_DWORD *)(v1 + 228) = 0;
    }
    if ( unk_A7051C )
    {
      *(_DWORD *)(v1 + 228) = *(_DWORD *)(unk_A7051C + 228);
      *(_DWORD *)(v1 + 224) = unk_A7051C;
      *(_DWORD *)(*(_DWORD *)(unk_A7051C + 228) + 224) = v1;
      *(_DWORD *)(unk_A7051C + 228) = v1;
    }
    else
    {
      *(_DWORD *)(v1 + 224) = v1;
      *(_DWORD *)(v1 + 228) = v1;
      unk_A7051C = v1;
    }
    ++unk_A70624;
  }
  return v1;
}

