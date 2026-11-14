// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609942 _fputs
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(text,FILE). Require bothnonNULL;unlessFILEflag0x40,validate
// descriptorencoding BEFORE lock:fd-1/-2 use665C30,othersblock2021E40[fd>>5]+(fd&31)*64; low7 bits at+36 thenfreshbit0x80 mustboth0. Invalid ->errno22/handler/-1. strlen
// BEFORElock,thenlock_file/armSEH;stbuf(FILE),fwrite_nolock(text,1,length,FILE),savecount,ftbuf(tempflag,FILE),ignorecleanupresult;finallyunlock. Return0 iff written==length
// else-1,not charcount. Emptystring stillruns tempbuffer lifecycle. No newline/NUL written, boundedstrlen or sourcecapacity check. Finally unlocks only; ftbuf normal-only ifdelegate
// throws. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths retain
// their separately described policy.
int __cdecl fputs(const char *Buffer, FILE *Stream)
{
  int v3; // eax
  _BYTE *v4; // ecx
  char *v5; // eax
  int v6; // esi
  size_t v7; // [esp+10h] [ebp-20h]
  size_t ElementCount; // [esp+14h] [ebp-1Ch]

  if ( Buffer
    && Stream
    && ((Stream->_flag & 0x40) != 0
     || ((v3 = _fileno(Stream), v3 == -1) || v3 == -2
       ? (v4 = &unk_665C30)
       : (v4 = (_BYTE *)(unk_2021E40[v3 >> 5] + ((v3 & 0x1F) << 6))),
         (v4[36] & 0x7F) == 0
      && (v3 == -1 || v3 == -2 ? (v5 = (char *)&unk_665C30) : (v5 = (char *)(unk_2021E40[v3 >> 5] + ((v3 & 0x1F) << 6))),
          v5[36] >= 0))) )
  {
    ElementCount = strlen(Buffer);
    _lock_file(Stream);
    v6 = _stbuf(Stream);
    v7 = _fwrite_nolock(Buffer, 1u, ElementCount, Stream);
    _ftbuf(v6, Stream);
    _unlock_file(Stream);
    return (v7 == ElementCount) - 1;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

