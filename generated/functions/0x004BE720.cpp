// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE720 rf_corpse_pool_drain_free_nodes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Pool corpse: 30 inline records of792 bytes; trailing header H=0x5CD0. H+0 free head,H+4 opaque tag,H+8 heap-block count,H+12 free-list count,H+16 peak heap count,H+20 peak in-use,H+24 in-use. Thiscall,no args. Walks and POPS ENTIRE free list, leaving headNULL. For each node computes SIGNED32 byteDifference=node-poolBase, CDQ/IDIV by792 (truncate toward0). Only quotient<0 OR quotient>=30 is operator-deleted and decrements heap-block count; other nodes are simply detached. This is quotient classification, not pointer alignment/exact membership validation: a pointer less than one stride below base truncates to quotient0. Does not visit in-use spill blocks, run payload destructors, reconstruct
// inline links, decrement/reset free count or reset in-use/tag/peaks. Returns pool bits. No cycle/null-membership/ownership/overflow guard; raw address subtraction follows32-bit native arithmetic.
_DWORD *__thiscall rf_corpse_pool_drain_free_nodes(_DWORD *this)
{
  _DWORD *result; // eax
  unsigned int v3; // [esp+Ch] [ebp-8h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this;
    if ( !*(this + 5940) )
      break;
    v3 = (*(this + 5940) - (int)this) / 792;
    v4 = (_DWORD *)*(this + 5940);
    *(this + 5940) = *v4;
    if ( v3 >= 0x1E )
    {
      operator delete(v4);
      --*(this + 5942);
    }
  }
  return result;
}

