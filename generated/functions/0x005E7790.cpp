// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7790 rf_byte_arena_resize_last_allocation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered thiscall(pointer,newBytes). Only accepts pointer==lastAllocation20,elseNULL. Uses unsigned32 pointer arithmetic:if pointer+newBytes<=cursor8,or requested extension beyond cursor<=remaining16,sets cursor=pointer+newBytes,aligns/recomputes remaining,returns same pointer. Supports shrink,does not zero bytes. Else requires GROW02;records oldSize=cursor-pointer INCLUDING alignment padding,prepends new chunk,checks new remaining>=newBytes,allocates new block,copies oldSize bytes,sets lastAllocation=new pointer,returns it. Old allocation/chunk retained. Failed prepend leaves old chunk;successful prepend followed by oversized/allocation failure RETURNSNULL AFTER SWITCHING active chunk/cursor,without restoring old
// allocation context. No other-pointer realloc,free,on-failure rollback,membership or integer-overflow guard. Successful same-pointer path leaves lastAllocation unchanged.
void *__thiscall rf_byte_arena_resize_last_allocation(void *this, void *a2, unsigned int a3)
{
  void *v5; // [esp+4h] [ebp-10h]
  int Size; // [esp+Ch] [ebp-8h]

  if ( a2 != *((void **)this + 5) )
    return nullptr;
  if ( (unsigned int)a2 + a3 <= *((_DWORD *)this + 2)
    || (unsigned int)a2 + a3 - *((_DWORD *)this + 2) <= *((_DWORD *)this + 4) )
  {
    *((_DWORD *)this + 2) = (char *)a2 + a3;
    rf_byte_arena_align_cursor_update_remaining(this);
    return a2;
  }
  else if ( ((*((_DWORD *)this + 6) >> 1) & 1) != 0 )
  {
    Size = *((_DWORD *)this + 2) - (_DWORD)a2;
    if ( rf_byte_arena_prepend_chunk(this) )
    {
      return nullptr;
    }
    else if ( *((_DWORD *)this + 4) >= a3 )
    {
      v5 = (void *)rf_byte_arena_allocate(this, a3);
      if ( v5 )
      {
        memcpy(v5, a2, Size);
        *((_DWORD *)this + 5) = v5;
        return v5;
      }
      else
      {
        return nullptr;
      }
    }
    else
    {
      return nullptr;
    }
  }
  else
  {
    return nullptr;
  }
}

