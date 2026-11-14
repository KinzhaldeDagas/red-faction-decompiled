// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517F40 rf_pointer_array_release_storage
// UNREALRED VERIFIED [event-registry-crc-20261028]: Sets first two dwords (count/capacity) to0; if backing pointer at this+8 is nonnull, operator-delete it and clear pointer. Does not destroy/free any pointed elements. Returns this.
void **__thiscall rf_pointer_array_release_storage(void **this)
{
  void **result; // eax

  result = this;
  *this = nullptr;
  *(this + 1) = nullptr;
  if ( *(this + 2) )
  {
    operator delete(*(this + 2));
    *(this + 2) = nullptr;
    return this;
  }
  return result;
}

