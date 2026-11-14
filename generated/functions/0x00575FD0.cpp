// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00575FD0 rf_bitmap_next_handle_generation
// UNREALRED VERIFIED [bitmap-loading-20261028]: Returns prior global generation0x663F18, then increments it; if new value>limit0x1897348, resets new generation to1. No atomicity or initialization guard. Wrap test occurs after returned value captured; does not validate existing handles.
int rf_bitmap_next_handle_generation()
{
  int v1; // [esp+0h] [ebp-4h]

  v1 = dword_663F18++;
  if ( dword_663F18 > unk_1897348 )
    dword_663F18 = 1;
  return v1;
}

