// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606C8C _malloc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl unsigned size. Size>0xFFFFFFE0 calls
// callnewh(originalSize) ONCE regardless new-mode global, ignores its result, sets errno12 and returnsNULL. Admitted attempts first require heap handle2021854 nonzero; missing handle
// invokes FF_MSGBANNER,NMSG_WRITE(30),crtExitProcess(255), then falls through if those return. LIVE heap mode2021F40==1 uses HeapAlloc(handle,0,max(size,1)) without16-byte rounding.
// Mode3 first calls V6_HeapAlloc(raw working size); success returns it. Other modes or failed small allocation normalize0->1 and round working size up16 for HeapAlloc(handle,0,size).
// Failure with global2021B6C0 writes errno12 twice, returnsNULL. Enabled new mode calls callnewh(ORIGINAL size); zero result sets errno12/returnsNULL, nonzero reloads original size
// and retries from handle check. No own zero-fill, ownership validation or invalid-parameter call.
void *__cdecl malloc(size_t Size)
{
  size_t v1; // esi
  SIZE_T v2; // eax
  void *v3; // eax
  void *v4; // ebx

  v1 = Size;
  if ( Size > 0xFFFFFFE0 )
  {
    _callnewh(Size);
    *_errno() = 12;
    return nullptr;
  }
  else
  {
    while ( 1 )
    {
      if ( !MEMORY[0x2021854] )
      {
        _FF_MSGBANNER();
        _NMSG_WRITE(30);
        __crtExitProcess(0xFFu);
      }
      if ( unk_2021F40 == 1 )
      {
        v2 = v1 ? v1 : 1;
        v3 = HeapAlloc(MEMORY[0x2021854], 0, v2);
      }
      else if ( unk_2021F40 != 3 || (v3 = V6_HeapAlloc(v1)) == nullptr )
      {
        if ( !v1 )
          v1 = 1;
        v3 = HeapAlloc(MEMORY[0x2021854], 0, (v1 + 15) & 0xFFFFFFF0);
      }
      v4 = v3;
      if ( v3 )
        return v4;
      if ( !unk_2021B6C )
      {
        *_errno() = 12;
LABEL_19:
        *_errno() = 12;
        return v4;
      }
      if ( !_callnewh(Size) )
        goto LABEL_19;
      v1 = Size;
    }
  }
}

