// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E8F0 rf_vpackfile_release_shared_string_pool
// UNREALRED VERIFIED [string-pool-stream-20261028]: If rf_vpackfile_initialized nonzero,calls0x5E6E90 for pool0x1C8FBC8,returns pool address. Not initialized returns incidental uninitialized EAX. Does not clear initialized flag,mounted archive/member counts,lookup tables,open archives or stored string pointers. Pool was allocated0x40000 bytes during VPP initialization; release invalidates references into it.
int rf_vpackfile_release_shared_string_pool()
{
  int result; // eax

  if ( rf_vpackfile_initialized )
    return rf_string_pool_release_buffer((int)byte_1C8FBC8);
  return result;
}

