// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C382 _setvbuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): FILE32 offsets
// ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28; dynamic critical section+32. Invalid(E) means errno E plus invalid_parameter(NULL,NULL,NULL,0,0); stated status follows
// only if that handler returns. Cdecl(FILE,optional buffer,mode,unsigned size). NULL FILE invalid(22)/-1. Only mode0,4,64 admitted; modes0/64 require unsigned(size-2)<=0x7FFFFFFD,
// i.e.2..INT_MAX; mode4 skips size validation. Round size DOWN to even, lock_file,armSEH. flush(FILE) and freebuf(FILE),IGNORE both results; flags &=0xFFFFC2F3 before replacement.
// Mode4 ORflag4, install inline FILE+20,size2, ignore supplied buffer/size. Buffered mode with supplied pointer ORflags0x500; NULL buffer malloc_crt(even size), successOR0x408.
// Success sets bufsiz,base,ptr,cnt0,return0. AllocationNULL increments20213AC,return-1, with no restoration of flushed/freed buffer or cleared flags; final header install is skipped
// and prior fields depend on freebuf behavior. No own errno assignment on allocationfailure. Normal/unwind finally unlock_file. This implementation treats modes0/64 identically after
// admission; no independent line-buffer flush policy.
int __cdecl setvbuf(FILE *Stream, char *Buffer, int Mode, size_t Size)
{
  size_t v5; // edi
  unsigned int v6; // edi
  int flag; // ecx
  int v8; // ecx
  char *p_charbuf; // eax
  int v10; // [esp+10h] [ebp-1Ch]

  v10 = 0;
  if ( !Stream )
    goto LABEL_2;
  if ( Mode != 4 )
  {
    if ( !Mode )
      goto LABEL_7;
    if ( Mode != 64 )
    {
LABEL_2:
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return -1;
    }
  }
  if ( Mode != 64 )
  {
    v5 = Size;
    goto LABEL_10;
  }
LABEL_7:
  v5 = Size;
  if ( Size - 2 > 0x7FFFFFFD )
    goto LABEL_2;
LABEL_10:
  v6 = v5 & 0xFFFFFFFE;
  _lock_file(Stream);
  _flush(Stream);
  _freebuf((int)Stream);
  Stream->_flag &= 0xFFFFC2F3;
  flag = Stream->_flag;
  if ( (Mode & 4) != 0 )
  {
    v8 = flag | 4;
    p_charbuf = (char *)&Stream->_charbuf;
    v6 = 2;
LABEL_17:
    Stream->_flag = v8;
    goto LABEL_18;
  }
  p_charbuf = Buffer;
  if ( Buffer )
  {
    v8 = flag | 0x500;
    goto LABEL_17;
  }
  p_charbuf = (char *)_malloc_crt(v6);
  if ( p_charbuf )
  {
    Stream->_flag |= 0x408u;
LABEL_18:
    Stream->_bufsiz = v6;
    Stream->_base = p_charbuf;
    Stream->_ptr = p_charbuf;
    Stream->_cnt = 0;
    goto $done$25030;
  }
  ++unk_20213AC;
  v10 = -1;
$done$25030:
  _unlock_file(Stream);
  return v10;
}

