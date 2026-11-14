// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0AB0 rf_vfile_write_line_stdio_direct
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall vfile,optional text,signed length. Slot index object+272 selects32832-byte global slot0x189CEB0. Nonzero status+12 skips writes. Null text replaced with empty literal0x642FF0; negative length=strlen(text). Nonzero length uses fwrite(text,length,1,FILE at slot+32812); failure sets status-2 and SKIPS newline. Otherwise writes one LF byte; newline failure also sets status-2. Direct FILE path BYPASSES feedback encoding,operation count,position,cumulative-byte counters and write cache helpers. No CR,automatic length bound,FILE validation or common success return; EAX varies pointer/fwrite result.
int *__thiscall rf_vfile_write_line_stdio_direct(int *this, const char *Buffer, int ElementSize)
{
  int *result; // eax
  int *v4; // [esp+14h] [ebp-4h]

  result = this;
  v4 = &unk_189CEB0[8208 * *(this + 68)];
  if ( !v4[3] )
  {
    if ( !Buffer )
      Buffer = (const char *)&unk_642FF0;
    if ( ElementSize < 0 )
      ElementSize = strlen(Buffer);
    if ( ElementSize && !fwrite(Buffer, ElementSize, 1u, (FILE *)v4[8203])
      || (result = (int *)fwrite("\n", 1u, 1u, (FILE *)v4[8203])) == nullptr )
    {
      v4[3] = -2;
      return v4;
    }
  }
  return result;
}

