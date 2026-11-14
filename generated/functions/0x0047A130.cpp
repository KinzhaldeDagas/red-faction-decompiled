// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A130 rf_bolt_emitter_scalar_delete
// UNREALRED VERIFIED [level-lifecycle-20261028]: Calls member destructor0x4C0A70 then operator-deletes this only when low flags byte bit0 set. Returns original pointer, potentially freed. Does not remove registry entry in wrapper.
void *__thiscall rf_bolt_emitter_scalar_delete(void *this, char a2)
{
  rf_bolt_emitter_destroy_members((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

