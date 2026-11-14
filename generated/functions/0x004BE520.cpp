// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE520 rf_item_pool_initialize_inline_free_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Pool item: 200 inline records of708 bytes; trailing header H=0x22920. H+0 free head,H+4 opaque tag,H+8 heap-block count,H+12 free-list count,H+16 peak heap count,H+20 peak in-use,H+24 in-use. Thiscall(pool,tag),RET4,returns pool. Stores tag, zeros counters/head then sets free count200,head=poolBase. Links first DWORD of each record to next at exact stride708, last toNULL. Does not initialize other record bytes or call member constructors. No release of old heap blocks/live objects before overwrite, no repeated-init guard, allocation or capacity argument; fixed capacity is native constant.
_DWORD *__thiscall rf_item_pool_initialize_inline_free_list(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 35401) = a2;
  *(this + 35400) = 0;
  *(this + 35402) = 0;
  *(this + 35403) = 0;
  *(this + 35404) = 0;
  *(this + 35406) = 0;
  *(this + 35405) = 0;
  *(this + 35403) = 200;
  *(this + 35400) = this;
  for ( i = 0; i < 199; ++i )
    *(this + 177 * i) = this + 177 * i + 177;
  *(this + 177 * i) = 0;
  return this;
}

