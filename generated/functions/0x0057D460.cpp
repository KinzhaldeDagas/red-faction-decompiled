// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D460 rf_stream_adapter_seek
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 delegates unchanged offset/origin to rf_vfile_seek. Every nonzero mode uses memory cursor+12/length+16: origin0 accepts strictly0<offset<length and sets cursor; origin1 requires positive offset and cursor+offset<length; origin2 subtracts positive offset from CURRENT cursor if nonnegative (not length-relative SEEK_END). Success0; failure sets error+84=-1 and returns-1. Zero absolute position, zero motion and exact end are rejected; arithmetic overflow is unchecked.
int __thiscall rf_stream_adapter_seek(_DWORD *this, int Offset, int a3)
{
  if ( !*this )
    return rf_vfile_seek((int *)*(this + 1), Offset, a3);
  if ( a3 )
  {
    if ( a3 == 1 )
    {
      if ( Offset > 0 && *(this + 3) + Offset < *(this + 4) )
      {
        *(this + 3) += Offset;
        return 0;
      }
    }
    else if ( a3 == 2 && Offset > 0 && *(this + 3) - Offset >= 0 )
    {
      *(this + 3) -= Offset;
      return 0;
    }
  }
  else if ( Offset > 0 && Offset < *(this + 4) )
  {
    *(this + 3) = Offset;
    return 0;
  }
  *(this + 21) = -1;
  return -1;
}

