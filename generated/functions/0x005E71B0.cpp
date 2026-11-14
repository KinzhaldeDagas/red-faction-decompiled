// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E71B0 rf_string_pool_destroy
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall wrapper returning0x5E6E90 result. Releases underlying buffer only according to ownership flag; does not delete pool object itself.
int __thiscall rf_string_pool_destroy(void *this)
{
  return rf_string_pool_release_buffer((int)this);
}

