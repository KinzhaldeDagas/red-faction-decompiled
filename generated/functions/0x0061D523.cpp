// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D523 __calloc_impl
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) here means storing errno E, invoking
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if the handler returns. Cdecl(count,width,optional statusDWORD pointer). If count!=0 require
// width<=0xFFFFFFE0/count unsigned; violation ->invalid(12)/NULL, WITHOUT touching optional status. Compute original product, working=max(product,1). Each attempt reset resultNULL;
// if working<=limit and mode3, round working up16, and original product<=LIVE threshold2021F4C ->lock4/armSEH/sbh_alloc_block(originalProduct)/finallyunlock4. Small-block success
// memset exactly ORIGINAL product bytes to0 (padding untouched). Otherwise HeapAlloc(heap2021854,8,working); other modes do not round here. No handle-zero fatal check. Failure: if
// newmode2021B6C0, write optional status12 iff nonNULL and returnNULL, WITHOUT own errno/handler; enabled newmode callnewh(CURRENT working size), retry on nonzero, otherwise optional
// status12/NULL. No initial status clear/success status store; handler receives rounded size in mode3. Original zero product may allocate1 or16 bytes; small-block path receives0 and
// memset0. Scope65EFA8 handler61D61A restores EDI/ESI then unlock4.
LPVOID __cdecl _calloc_impl(size_t Size, unsigned int a2, _DWORD *a3)
{
  size_t v4; // esi
  LPVOID v5; // ebx
  _DWORD *v6; // [esp+10h] [ebp-1Ch]
  size_t Sizea; // [esp+34h] [ebp+8h]

  if ( !Size || 0xFFFFFFE0 / Size >= a2 )
  {
    v4 = a2 * Size;
    Sizea = v4;
    if ( !v4 )
      v4 = 1;
    while ( 1 )
    {
      v5 = nullptr;
      if ( v4 <= 0xFFFFFFE0 )
        break;
LABEL_14:
      if ( v5 )
        return v5;
      if ( !unk_2021B6C )
      {
        if ( a3 )
          *a3 = 12;
        return v5;
      }
      if ( !_callnewh(v4) )
      {
        if ( a3 )
          *a3 = 12;
        return nullptr;
      }
    }
    if ( unk_2021F40 == 3 )
    {
      v4 = (v4 + 15) & 0xFFFFFFF0;
      if ( Sizea <= unk_2021F4C )
      {
        _lock(4);
        v6 = __sbh_alloc_block(Sizea);
        _unlock(4);
        v5 = v6;
        if ( !v6 )
        {
LABEL_13:
          v5 = HeapAlloc(MEMORY[0x2021854], 8u, v4);
          goto LABEL_14;
        }
        memset(v6, 0, Sizea);
      }
    }
    if ( v5 )
      return v5;
    goto LABEL_13;
  }
  *_errno() = 12;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  return nullptr;
}

