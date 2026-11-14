// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BFE40 rf_scene_frame_channel_state_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Calls verified no-op72-byte channel-state destructor5F8E70. Flag byte mask1 additionally operator deletes receiver; returns original pointer bits even if freed. Other flags ignored,no member nulling or shared channel-definition release.
void *__thiscall rf_scene_frame_channel_state_scalar_deleting_destructor(void *this, char a2)
{
  rf_saved_receiver_noop_5F8E70();
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

