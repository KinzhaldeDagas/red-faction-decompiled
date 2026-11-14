// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053A0E0 rf_procedural_bitmap_find_or_create
// UNREALRED VERIFIED [resource-pools-20261028]: Rejects width or height>256; no lower bound check. Scans active56-byte records for same mode+28,width+16,height+20 and either source handle+36 matching input or equaling global default0x663CB8. Reuses existing slot index. Otherwise acquires slot; for unsigned mode<=2 accepts caller source only if handle>=0 and0x576550(handle)==4, else loads Rck_Default.tga, stores as globaldefault and replaces dimensions with source dimensions. Stores callback0x53A440 and clears floats+44/+48/+52 for modes0..2. Other modes leave those fields untouched in this body. Clears dword+4, writes+0=-1, creates format4 USERBMAP via0x5782B0 into+24 and returns slot index even if bitmap creation fails; no rollback.
int __cdecl rf_procedural_bitmap_find_or_create(int a1, int a2, unsigned int a3, int a4)
{
  _DWORD *v5; // [esp+4h] [ebp-Ch]
  int resolved_format_code; // [esp+8h] [ebp-8h]
  int v7; // [esp+Ch] [ebp-4h] BYREF

  if ( a2 > 256 || a1 > 256 )
    return -1;
  for ( dword_1426664 = (_DWORD *)unk_142665C; dword_1426664; dword_1426664 = v5 )
  {
    if ( dword_1426664[7] == a3
      && dword_1426664[4] == a1
      && dword_1426664[5] == a2
      && (dword_1426664[9] == a4 || dword_1426664[9] == dword_663CB8) )
    {
      return ((char *)dword_1426664 - (char *)&unk_14262D8) / 56;
    }
    if ( dword_1426664[2] == unk_142665C )
      v5 = nullptr;
    else
      v5 = (_DWORD *)dword_1426664[2];
  }
  dword_1426664 = (_DWORD *)rf_procedural_bitmap_pool_acquire(&v7);
  if ( !dword_1426664 )
    return -1;
  dword_1426664[4] = a1;
  dword_1426664[5] = a2;
  dword_1426664[7] = a3;
  if ( a3 <= 2 )
  {
    resolved_format_code = rf_bitmap_get_resolved_format_code(a4);
    if ( a4 >= 0 && resolved_format_code == 4 )
    {
      dword_1426664[9] = a4;
    }
    else
    {
      dword_1426664[9] = rf_bitmap_load_with_optional_mipmap_generation("Rck_Default.tga", (void *)0xFFFFFFFF, 1);
      dword_663CB8 = dword_1426664[9];
      rf_bitmap_get_resolved_dimensions(dword_1426664[9], dword_1426664 + 4, dword_1426664 + 5);
    }
    dword_1426664[8] = rf_procedural_bitmap_update_sine_warp;
    *((float *)dword_1426664 + 11) = 0.0;
    *((float *)dword_1426664 + 12) = 0.0;
    *((float *)dword_1426664 + 13) = 0.0;
  }
  dword_1426664[1] = 0;
  *dword_1426664 = -1;
  dword_1426664[6] = rf_bitmap_create_user_bitmap(4, dword_1426664[4], dword_1426664[5]);
  return v7;
}

