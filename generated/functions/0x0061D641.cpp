// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D641 _realloc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(block,unsigned size), pointer result. NULL
// block delegates malloc(size), even size0. NonNULL with size0 calls free(block), returnsNULL. Oversize>0xFFFFFFE0 calls callnewh(current size) once regardless newmode, ignores
// result, errno12/NULL. Nonmode3 uses HeapReAlloc(heap,0,block,size), with failure/newmode retry; final error maps GetLastError via errno SLOT acquired first. Mode3: lock4/SEH; find
// small-block region. Found and requested<=threshold first try sbh_resize_block; success returns same block. Else sbh_alloc_block(requested); success COPY
// minUnsigned(rawDWORD[old-4]-1,REQUESTED size), RE-FIND old region, then sbh_free_block. If stillNULL, round working size up16, HeapAlloc; success COPY
// minUnsigned(rawDWORD[old-4]-1,ROUNDED size), then free old small block using saved region. These copy counts subtract1, NOT msize subtract9. Finally unlock4, including unwind. No
// small region ->round working up16 and HeapReAlloc. NULL result with newmode enabled calls newh(current possibly rounded size) and retries without restoring original requested size.
// Final small-region failure errno12; Windows branch maps GetLastError. Body frees old small block only after successful new allocation/copy; no zeroing, memcpy-status check or
// rollback on exceptions. Scope65EFC8 handler61D77F restores working registers then unlock4.
void *__cdecl realloc(void *Block, size_t Size)
{
  size_t v3; // esi
  _DWORD *v4; // eax
  size_t v5; // eax
  size_t v6; // eax
  void *v7; // edi
  int *v8; // eax
  int *v9; // esi
  DWORD v10; // eax
  int *v11; // eax
  int *v12; // esi
  DWORD LastError; // eax
  _DWORD *v14; // [esp+10h] [ebp-20h]
  void *v15; // [esp+14h] [ebp-1Ch]

  if ( !Block )
    return malloc(Size);
  v3 = Size;
  if ( Size )
  {
    if ( unk_2021F40 == 3 )
    {
      while ( 1 )
      {
        v15 = nullptr;
        if ( v3 > 0xFFFFFFE0 )
          break;
        _lock(4);
        v4 = __sbh_find_block(Block);
        v14 = v4;
        if ( v4 )
        {
          if ( v3 <= unk_2021F4C )
          {
            if ( __sbh_resize_block(v4, Block, v3) )
            {
              v15 = Block;
            }
            else
            {
              v15 = __sbh_alloc_block(v3);
              if ( v15 )
              {
                v5 = *((_DWORD *)Block - 1) - 1;
                if ( v5 >= v3 )
                  v5 = v3;
                memcpy(v15, Block, v5);
                v14 = __sbh_find_block(Block);
                __sbh_free_block(v14, Block);
              }
            }
          }
          if ( !v15 )
          {
            if ( !v3 )
              v3 = 1;
            v3 = (v3 + 15) & 0xFFFFFFF0;
            v15 = HeapAlloc(MEMORY[0x2021854], 0, v3);
            if ( v15 )
            {
              v6 = *((_DWORD *)Block - 1) - 1;
              if ( v6 >= v3 )
                v6 = v3;
              memcpy(v15, Block, v6);
              __sbh_free_block(v14, Block);
            }
          }
        }
        _unlock(4);
        if ( v14 )
        {
          v7 = v15;
        }
        else
        {
          if ( !v3 )
            v3 = 1;
          v3 = (v3 + 15) & 0xFFFFFFF0;
          v7 = HeapReAlloc(MEMORY[0x2021854], 0, Block, v3);
        }
        if ( v7 )
          return v7;
        if ( !unk_2021B6C )
        {
          v11 = _errno();
          if ( !v14 )
            goto LABEL_45;
          *v11 = 12;
          return v7;
        }
        if ( !_callnewh(v3) )
        {
          v8 = _errno();
          if ( v14 )
            goto LABEL_41;
          goto LABEL_31;
        }
      }
    }
    else
    {
      while ( v3 <= 0xFFFFFFE0 )
      {
        if ( !v3 )
          v3 = 1;
        v7 = HeapReAlloc(MEMORY[0x2021854], 0, Block, v3);
        if ( v7 )
          return v7;
        if ( !unk_2021B6C )
        {
          v11 = _errno();
LABEL_45:
          v12 = v11;
          LastError = GetLastError();
          *v12 = _get_errno_from_oserr(LastError);
          return v7;
        }
        if ( !_callnewh(v3) )
        {
          v8 = _errno();
LABEL_31:
          v9 = v8;
          v10 = GetLastError();
          *v9 = _get_errno_from_oserr(v10);
          return nullptr;
        }
      }
    }
    _callnewh(v3);
    v8 = _errno();
LABEL_41:
    *v8 = 12;
  }
  else
  {
    free(Block);
  }
  return nullptr;
}

