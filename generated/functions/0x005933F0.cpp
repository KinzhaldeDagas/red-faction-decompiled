// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005933F0 rf_vfile_seek
// UNREALRED VERIFIED [vfile-loose-precedence] Maintains a member-relative logical offset and delegates VPP seeks through the member base-block adapter.
int __thiscall rf_vfile_seek(int *this, int Offset, int a3)
{
  int *v5; // [esp+4h] [ebp-4h]

  v5 = &unk_189CEB0[8208 * *(this + 68)];
  if ( a3 == 1 )
  {
    Offset += v5[4];
  }
  else if ( a3 == 2 )
  {
    Offset += rf_vfile_get_size((int)this, nullptr, (int)byte_98967F);
  }
  if ( rf_vfile_test_mode_mask(this, 1) && v5[8] != -1 && Offset >= v5[8] && Offset < v5[10] + v5[8] )
  {
    v5[4] = Offset;
    v5[9] = Offset - v5[8];
    return 0;
  }
  v5[4] = Offset;
  v5[9] = 0;
  v5[10] = 0;
  v5[8] = -1;
  if ( *(this + 66) )
  {
    if ( !rf_vpackfile_entry_seek(*(this + 66), Offset, 0) )
      return -99999;
  }
  else if ( fseek((FILE *)v5[8203], Offset, 0) )
  {
    return -99999;
  }
  return 0;
}

