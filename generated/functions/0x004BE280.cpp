// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BE280 rf_projectile_pool_initialize_inline_free_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Pool projectile: 50 inline records of788 bytes; trailing header H=0x99E8. H+0 free head,H+4 opaque tag,H+8 heap-block count,H+12 free-list count,H+16 peak heap count,H+20 peak in-use,H+24 in-use. Thiscall(pool,tag),RET4,returns pool. Stores tag, zeros counters/head then sets free count50,head=poolBase. Links first DWORD of each record to next at exact stride788, last toNULL. Does not initialize other record bytes or call member constructors. No release of old heap blocks/live objects before overwrite, no repeated-init guard, allocation or capacity argument; fixed capacity is native constant.
_DWORD *__thiscall rf_projectile_pool_initialize_inline_free_list(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 9851) = a2;
  *(this + 9850) = 0;
  *(this + 9852) = 0;
  *(this + 9853) = 0;
  *(this + 9854) = 0;
  *(this + 9856) = 0;
  *(this + 9855) = 0;
  *(this + 9853) = 50;
  *(this + 9850) = this;
  for ( i = 0; i < 49; ++i )
    *(this + 197 * i) = this + 197 * i + 197;
  *(this + 197 * i) = 0;
  return this;
}

