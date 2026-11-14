// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE7B0 rf_item_pool_drain_free_nodes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Pool item: 200 inline records of708 bytes; trailing header H=0x22920. H+0 free head,H+4 opaque tag,H+8 heap-block count,H+12 free-list count,H+16 peak heap count,H+20 peak in-use,H+24 in-use. Thiscall,no args. Walks and POPS ENTIRE free list, leaving headNULL. For each node computes SIGNED32 byteDifference=node-poolBase, CDQ/IDIV by708 (truncate toward0). Only quotient<0 OR quotient>=200 is operator-deleted and decrements heap-block count; other nodes are simply detached. This is quotient classification, not pointer alignment/exact membership validation: a pointer less than one stride below base truncates to quotient0. Does not visit in-use spill blocks, run payload destructors, reconstruct
// inline links, decrement/reset free count or reset in-use/tag/peaks. Returns pool bits. No cycle/null-membership/ownership/overflow guard; raw address subtraction follows32-bit native arithmetic.
_DWORD *__thiscall rf_item_pool_drain_free_nodes(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(this + 35400) )
      break;
    v3 = (*(this + 35400) - (int)this) / 708;
    v4 = (_DWORD *)*(this + 35400);
    *(this + 35400) = *v4;
    if ( v3 >= 0xC8 )
    {
      operator delete(v4);
      --*(this + 35402);
    }
  }
  return result;
}

