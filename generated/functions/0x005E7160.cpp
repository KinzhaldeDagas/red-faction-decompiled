// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7160 rf_string_pool_construct_attached
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall pool,base,capacity,ownership byte. Calls0x5E6DE0 then returns POOL pointer,unlike callee returning base. Leaves string count+16 uninitialized/unchanged because callee does not write it. No empty-constructor call or old buffer release in body.
_BYTE *__thiscall rf_string_pool_construct_attached(_BYTE *this, int a2, int a3, char a4)
{
  rf_string_pool_attach_buffer(this, a2, a3, a4);
  return this;
}

