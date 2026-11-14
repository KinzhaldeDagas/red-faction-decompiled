// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE440 rf_corpse_pool_initialize_inline_free_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Pool corpse: 30 inline records of792 bytes; trailing header H=0x5CD0. H+0 free head,H+4 opaque tag,H+8 heap-block count,H+12 free-list count,H+16 peak heap count,H+20 peak in-use,H+24 in-use. Thiscall(pool,tag),RET4,returns pool. Stores tag, zeros counters/head then sets free count30,head=poolBase. Links first DWORD of each record to next at exact stride792, last toNULL. Does not initialize other record bytes or call member constructors. No release of old heap blocks/live objects before overwrite, no repeated-init guard, allocation or capacity argument; fixed capacity is native constant.
_DWORD *__thiscall rf_corpse_pool_initialize_inline_free_list(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 5941) = a2;
  *(this + 5940) = 0;
  *(this + 5942) = 0;
  *(this + 5943) = 0;
  *(this + 5944) = 0;
  *(this + 5946) = 0;
  *(this + 5945) = 0;
  *(this + 5943) = 30;
  *(this + 5940) = this;
  for ( i = 0; i < 29; ++i )
    *(this + 198 * i) = this + 198 * i + 198;
  *(this + 198 * i) = 0;
  return this;
}

