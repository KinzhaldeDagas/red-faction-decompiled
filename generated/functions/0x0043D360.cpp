// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043D360 rf_blood_surface_mark_pool_init
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Reset free head0x6E6228 and active head0x6E6254 to0, link8 static84-byte records from0x6E6268 into circular doubly linked free ring using next+0x4C/previous+0x50. Does not initialize every mark payload float or allocate texture/resources; snapshot export cap16 does not enlarge this pool.
int rf_blood_surface_mark_pool_init()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_6E6228 = 0;
  result = 0;
  unk_6E6254 = 0;
  for ( i = 0; i < 8; ++i )
  {
    if ( unk_6E6228 )
    {
      unk_6E62B8[21 * i] = *(_DWORD *)(unk_6E6228 + 80);
      unk_6E62B4[21 * i] = unk_6E6228;
      *(_DWORD *)(*(_DWORD *)(unk_6E6228 + 80) + 76) = (char *)&unk_6E6268 + 84 * i;
      *(_DWORD *)(unk_6E6228 + 80) = (char *)&unk_6E6268 + 84 * i;
    }
    else
    {
      unk_6E62B4[21 * i] = (int)&unk_6E6268 + 84 * i;
      unk_6E62B8[21 * i] = (int)&unk_6E6268 + 84 * i;
      unk_6E6228 = (char *)&unk_6E6268 + 84 * i;
    }
    result = 0;
  }
  return result;
}

