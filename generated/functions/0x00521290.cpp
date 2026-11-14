// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00521290 rf_world_decal_pool_initialize
// UNREALRED VERIFIED [decal-projection-20261028]: Clears active/free heads0xA7051C/0xA70620 and links128 fixed236-byte records at0xCFACB0 into circular free list using next+224/prev+228. Sets active count0xA70624 and category counts0xA70630/34=0. Does not initialize other payload or reset fading count0xA70628; does not release live polygons before overwriting links. Returns0.
int rf_world_decal_pool_initialize()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  unk_A7051C = 0;
  result = 0;
  unk_A70620 = 0;
  for ( i = 0; i < 128; ++i )
  {
    if ( unk_A70620 )
    {
      unk_CFAD94[59 * i] = *(_DWORD *)(unk_A70620 + 228);
      unk_CFAD90[59 * i] = unk_A70620;
      *(_DWORD *)(*(_DWORD *)(unk_A70620 + 228) + 224) = (char *)&unk_CFACB0 + 236 * i;
      *(_DWORD *)(unk_A70620 + 228) = (char *)&unk_CFACB0 + 236 * i;
    }
    else
    {
      unk_CFAD90[59 * i] = (int)&unk_CFACB0 + 236 * i;
      unk_CFAD94[59 * i] = (int)&unk_CFACB0 + 236 * i;
      unk_A70620 = (char *)&unk_CFACB0 + 236 * i;
    }
    result = 0;
  }
  unk_A70624 = 0;
  unk_A70630 = 0;
  unk_A70634 = 0;
  return result;
}

