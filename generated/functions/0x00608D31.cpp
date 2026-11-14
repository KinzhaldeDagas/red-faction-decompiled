// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608D31 __fwrite_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(buffer,size,count,FILE). size0/count0 ->0 first. Require
// nonNULLstream/buffer and count<=UINT_MAX/size,elseinvalid/0. Total32-bit product; initial chunkSize=FILEbufsiz ifflags0x10C else4096. Bufferedflags0x108 with positivecnt: memcpy
// minUnsigned(remaining,cnt),advanceFILEptr/cnt/source/remaining; negativecnt ->errorbit andpartial floor. Remaining>=chunkSize: ifbuffered callflush,nonzero ->partial floor.
// Request=remaining rounded DOWN by unsignedmod chunkSize whennonzero,else remaining (NO fread-style INT_MAX cap). write(fileno,source,request); exact -1 error,else credit
// minUnsigned(result,request),short unsignedresult<request errorbit/partial floor. Smaller remainder sign-extends sourcebyte andcallsflsbuf(byte,FILE); -1 ->partial
// floor,elseadvance1,refreshchunkSize andclamp signed<=0 to1. Full completion returns requestedcount;partial floors wholeelements. No lock, sourcecapacity validation, zeroing or
// rollback; only -1 specially recognized as write error. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns.
// Explicit errno34 or no-handler paths retain their separately described policy.
size_t __cdecl _fwrite_nolock(const void *Buffer, size_t ElementSize, size_t ElementCount, FILE *Stream)
{
  size_t v5; // edi
  size_t v6; // ebx
  int cnt; // eax
  size_t v8; // edi
  unsigned int v9; // edi
  int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // ecx
  size_t v13; // eax
  int bufsiz; // [esp+10h] [ebp-8h]
  char *Src; // [esp+14h] [ebp-4h]

  if ( !ElementSize || !ElementCount )
    return 0;
  if ( !Stream || !Buffer || ElementCount > 0xFFFFFFFF / ElementSize )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 0;
  }
  v5 = ElementCount * ElementSize;
  Src = (char *)Buffer;
  v6 = ElementCount * ElementSize;
  if ( (Stream->_flag & 0x10C) != 0 )
    bufsiz = Stream->_bufsiz;
  else
    bufsiz = 4096;
  if ( !v5 )
    return ElementCount;
  while ( 1 )
  {
    if ( (Stream->_flag & 0x108) != 0 )
    {
      cnt = Stream->_cnt;
      if ( cnt )
      {
        if ( cnt < 0 )
        {
          Stream->_flag |= 0x20u;
LABEL_34:
          v13 = v5;
          return (v13 - v6) / ElementSize;
        }
        v8 = v6;
        if ( v6 >= cnt )
          v8 = Stream->_cnt;
        memcpy(Stream->_ptr, Src, v8);
        Stream->_cnt -= v8;
        Stream->_ptr += v8;
        v6 -= v8;
        Src += v8;
        goto LABEL_27;
      }
    }
    if ( v6 >= bufsiz )
      break;
    if ( _flsbuf(*Src, Stream) == -1 )
      goto LABEL_34;
    ++Src;
    --v6;
    bufsiz = Stream->_bufsiz;
    if ( bufsiz <= 0 )
      bufsiz = 1;
LABEL_31:
    if ( !v6 )
      return ElementCount;
  }
  if ( (Stream->_flag & 0x108) != 0 && _flush(Stream) )
    goto LABEL_34;
  v9 = v6;
  if ( bufsiz )
    v9 = v6 - v6 % bufsiz;
  v10 = _fileno(Stream);
  v11 = _write(v10, Src, v9);
  if ( v11 != -1 )
  {
    v12 = v9;
    if ( v11 <= v9 )
      v12 = v11;
    Src += v12;
    v6 -= v12;
    if ( v11 >= v9 )
    {
LABEL_27:
      v5 = ElementCount * ElementSize;
      goto LABEL_31;
    }
  }
  Stream->_flag |= 0x20u;
  v13 = ElementCount * ElementSize;
  return (v13 - v6) / ElementSize;
}

