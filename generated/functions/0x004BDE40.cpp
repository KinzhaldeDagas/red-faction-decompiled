// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDE40 rf_physical_debris_pool_allocate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Pool physical_debris: 50 inline records of692 bytes; trailing header H=0x8728. H+0 free head,H+4 opaque tag,H+8 heap-block count,H+12 free-list count,H+16 peak heap count,H+20 peak in-use,H+24 in-use. Thiscall,no stack args. Nonnull free head pops node through its FIRST DWORD and decrements free count. Empty head with spill control false returnsNULL without counter changes. Spill enabled operator-news exactly692 bytes and increments heap count/its signed high-water; no local returned-NULL check before counters. Every non-early-return path increments in-use and signed peak. Returns raw block; does not construct/reset payload or enforce inline-capacity in-use cap. Counter arithmetic is
// unchecked32-bit; no lock, null-pool or free-link validation and no catch/rollback. Released heap blocks can be reused through same free list.
_DWORD *__thiscall rf_physical_debris_pool_allocate(_DWORD *this)
{
  _DWORD *v3; // [esp+8h] [ebp-4h]

  if ( *(this + 8650) )
  {
    v3 = (_DWORD *)*(this + 8650);
    *(this + 8650) = *v3;
    --*(this + 8653);
  }
  else
  {
    if ( !rf_fixed_pool_heap_spill_enabled )
      return nullptr;
    v3 = operator new(0x2B4u);
    if ( ++*(this + 8652) > *(this + 8654) )
      *(this + 8654) = *(this + 8652);
  }
  if ( ++*(this + 8656) > *(this + 8655) )
    *(this + 8655) = *(this + 8656);
  return v3;
}

