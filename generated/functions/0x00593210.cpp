// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593210 rf_vfile_close_stdio_or_vpp
// UNREALRED VERIFIED [vfile-loose-precedence] Closes either the VPP member archive handle or the loose stdio handle selected by the unified VFile resolver.
int __thiscall rf_vfile_close_stdio_or_vpp(int *this)
{
  int v3; // [esp+4h] [ebp-8h]
  int *v4; // [esp+8h] [ebp-4h]

  v4 = &unk_189CEB0[8208 * *(this + 68)];
  if ( *(this + 66) )
  {
    v3 = 0;
    rf_vpackfile_entry_close(*(this + 66));
  }
  else
  {
    v3 = fclose((FILE *)v4[8203]);
  }
  v4[8203] = 0;
  *(this + 66) = 0;
  if ( v3 && !v4[3] )
    v4[3] = -99999;
  *v4 = 0;
  *(this + 68) = -1;
  return v4[3];
}

