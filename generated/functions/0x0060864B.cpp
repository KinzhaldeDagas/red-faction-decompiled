// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060864B __fread_nolock_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(buffer,capacity,elementSize,count,stream). size0 OR count0
// returns0 before pointerchecks. NULLbuffer ->invalid/0. NULLstream OR count>UINT_MAX/size: zero ORIGINAL capacity bytes unless capacity==UINT_MAX,then invalid/0 (no buffer clearing
// on initial NULLbuffer route). Checked32-bit total=size*count; initial chunk bufferSize=FILEbufsiz whenflags0x10C,else4096. Loop: buffered positivecnt copies
// minUnsigned(remaining,cnt) via memcpy_s when<=remainingCapacity; IGNORE copy status,advance ptr,cnt,dst,remaining/capacity. Negativecnt ->errorbit0x20 and partial
// floor((total-remaining)/size). Otherwise remaining>=chunkSize selects directread: align minUnsigned(remaining,INT_MAX) DOWN to multiple of nonzero chunkSize; chunkSize0 uses
// min(remaining,INT_MAX). Check request<=remainingCapacity BEFORE read(fileno,dst,request). Return0 ->EOFbit0x10 andpartial floor; -1 ->errorbit andpartial floor; every other result
// advances raw counters. Small remainder calls filbuf FIRST; EOFreturns partial, then capacity0 detectsrange error AFTER character consumed. Store AL,advance1,refreshchunkSize
// fromFILE. Capacity shortage zeroes ENTIRE original buffer unless UINT_MAX sentinel,errno34/invalidhandler/return0,not partial count; prior stream progress remains. Full completion
// returns requestedcount. No lock, pointer-region validation, capacity rollback or check of memcpy_s/memset results. Unqualified invalid denotes errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
size_t __cdecl _fread_nolock_s(void *Buffer, size_t BufferSize, size_t ElementSize, size_t ElementCount, FILE *Stream)
{
  size_t v6; // edi
  size_t v7; // ebx
  int cnt; // eax
  rsize_t v9; // edi
  unsigned int v10; // edx
  int v11; // eax
  unsigned int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  char *v16; // ecx
  unsigned int v17; // [esp-4h] [ebp-20h]
  unsigned int bufsiz; // [esp+10h] [ebp-Ch]
  char *DstBuf; // [esp+14h] [ebp-8h]
  rsize_t DestinationSize; // [esp+18h] [ebp-4h]

  DstBuf = (char *)Buffer;
  DestinationSize = BufferSize;
  if ( !ElementSize || !ElementCount )
    return 0;
  if ( !Buffer )
    goto LABEL_4;
  if ( !Stream || ElementCount > 0xFFFFFFFF / ElementSize )
  {
    if ( BufferSize != -1 )
      memset(Buffer, 0, BufferSize);
    if ( !Stream || ElementCount > 0xFFFFFFFF / ElementSize )
    {
LABEL_4:
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return 0;
    }
  }
  v6 = ElementCount * ElementSize;
  v7 = ElementCount * ElementSize;
  if ( (Stream->_flag & 0x10C) != 0 )
    bufsiz = Stream->_bufsiz;
  else
    bufsiz = 4096;
  if ( !v6 )
    return ElementCount;
  while ( 1 )
  {
    if ( (Stream->_flag & 0x10C) != 0 )
    {
      cnt = Stream->_cnt;
      if ( cnt )
      {
        if ( cnt < 0 )
          goto LABEL_46;
        v9 = v7;
        if ( v7 >= cnt )
          v9 = Stream->_cnt;
        if ( v9 <= DestinationSize )
        {
          memcpy_s(DstBuf, DestinationSize, Stream->_ptr, v9);
          Stream->_cnt -= v9;
          Stream->_ptr += v9;
          DstBuf += v9;
          v7 -= v9;
          DestinationSize -= v9;
          v6 = ElementCount * ElementSize;
          goto LABEL_38;
        }
        if ( BufferSize != -1 )
          memset(Buffer, 0, BufferSize);
LABEL_42:
        *_errno() = 34;
        _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
        return 0;
      }
    }
    if ( v7 < bufsiz )
    {
      v15 = _filbuf(Stream);
      if ( v15 == -1 )
        return (v6 - v7) / ElementSize;
      if ( DestinationSize )
      {
        v16 = DstBuf++;
        *v16 = v15;
        --v7;
        --DestinationSize;
        bufsiz = Stream->_bufsiz;
        goto LABEL_38;
      }
LABEL_43:
      if ( BufferSize != -1 )
        memset(Buffer, 0, BufferSize);
      goto LABEL_42;
    }
    if ( bufsiz )
    {
      if ( v7 <= 0x7FFFFFFF )
      {
        v10 = v7 % bufsiz;
        v11 = v7;
      }
      else
      {
        v10 = 0x7FFFFFFF % bufsiz;
        v11 = 0x7FFFFFFF;
      }
      v12 = v11 - v10;
    }
    else
    {
      v12 = 0x7FFFFFFF;
      if ( v7 <= 0x7FFFFFFF )
        v12 = v7;
    }
    if ( v12 > DestinationSize )
      goto LABEL_43;
    v17 = v12;
    v13 = _fileno(Stream);
    v14 = _read(v13, DstBuf, v17);
    if ( !v14 )
      break;
    if ( v14 == -1 )
    {
LABEL_46:
      Stream->_flag |= 0x20u;
      return (v6 - v7) / ElementSize;
    }
    DstBuf += v14;
    v7 -= v14;
    DestinationSize -= v14;
LABEL_38:
    if ( !v7 )
      return ElementCount;
  }
  Stream->_flag |= 0x10u;
  return (v6 - v7) / ElementSize;
}

