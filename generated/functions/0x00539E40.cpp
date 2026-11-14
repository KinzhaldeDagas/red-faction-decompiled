// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539E40 rf_procedural_bitmap_pool_initialize
// UNREALRED VERIFIED [resource-pools-20261028]: Clears active/free heads0x142665C/0x1426658, links16 fixed56-byte records at0x14262D8 into circular free list via+8/+12, sets active count0x1426660=0. Fills256 float sine samples at0x1425ED8 with sin(float(i*0.02454369328916073)). Does not clear remaining record payload or release live bitmap handles first.
char *rf_procedural_bitmap_pool_initialize()
{
  char *result; // eax
  double v1; // st7
  float v2; // [esp+4h] [ebp-Ch]
  char *v3; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]
  char *j; // [esp+Ch] [ebp-4h]

  unk_142665C = 0;
  result = nullptr;
  unk_1426658 = 0;
  for ( i = 0; i < 16; ++i )
  {
    v3 = (char *)&unk_14262D8 + 56 * i;
    if ( unk_1426658 )
    {
      *((_DWORD *)v3 + 3) = *(_DWORD *)(unk_1426658 + 12);
      *((_DWORD *)v3 + 2) = unk_1426658;
      *(_DWORD *)(*(_DWORD *)(unk_1426658 + 12) + 8) = v3;
      result = (char *)&unk_14262D8 + 56 * i;
      *(_DWORD *)(unk_1426658 + 12) = v3;
    }
    else
    {
      *((_DWORD *)v3 + 2) = v3;
      result = (char *)&unk_14262D8 + 56 * i;
      *((_DWORD *)v3 + 3) = v3;
      unk_1426658 = result;
    }
  }
  unk_1426660 = 0;
  for ( j = nullptr; (int)j < 256; ++j )
  {
    v2 = (double)(int)j * 0.02454369328916073;
    v1 = rf_sin_float(v2);
    result = j;
    unk_1425ED8[(_DWORD)j] = v1;
  }
  return result;
}

