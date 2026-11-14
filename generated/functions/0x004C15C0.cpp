// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C15C0 rf_managed_particle_effect_node_release
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall node. If emitter0 nonnull destroys it via4CEDE0 and clears emitter0; if voiceHandle4!=-1 calls stop_voice_handle, including any other negative value, but DOES NOT reset
// stored voiceHandle afterward. No unlink, node free, position/room/link clearing. EAX incidental receiver or voice-stop return, not a reliable ownership/status result. Repeated
// release repeats voice-stop request; emitter destruction is guarded by cleared pointer.
int *__thiscall rf_managed_particle_effect_node_release(int *this)
{
  int *result; // eax

  result = this;
  if ( *this )
  {
    rf_particle_emitter_destroy(*this);
    result = this;
    *this = 0;
  }
  if ( *(this + 1) != -1 )
    return rf_gamesound_stop_voice_handle(*(this + 1));
  return result;
}

