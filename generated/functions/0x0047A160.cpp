// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A160 rf_rfl_light_scalar_delete
// UNREALRED VERIFIED [level-lifecycle-20261028]: Destroys light-record RF string+4 through0x47A190, then operator-deletes record only if low flags byte bit0 set. Returns original pointer, potentially freed. Does not clear light registry slot.
void *__thiscall rf_rfl_light_scalar_delete(void *this, char a2)
{
  rf_rfl_light_destroy_name((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

