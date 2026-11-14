// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1A00 rf_managed_particle_effect_list_process
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall circular sentinel walks next24. Every node with voiceHandle4!=-1 calls positioned_voice_update(handle,node.position8,listener17F10B0,1.0), regardless room BYTE or emitter
// state. Then raw cachedRoom28->BYTE352 nonzero permits particle_emitter_process(node.emitter0). No separate emitterNULL guard; normal failed-create nodes have roomNULL and skip. No
// room refresh, handle clearing on failed/stale audio update, expiry removal or list mutation in this body. Next loaded AFTER delegated callbacks, not snapshotted beforehand; assumes
// list integrity across calls. Normal return incidental sentinel pointer.
float *__thiscall rf_managed_particle_effect_list_process(float *this)
{
  float *result; // eax
  float *i; // [esp+8h] [ebp-4h]

  result = this;
  for ( i = *((float **)this + 6); i != this; i = result )
  {
    if ( *((_DWORD *)i + 1) != -1 )
      rf_positioned_voice_update(*((_DWORD *)i + 1), i + 2, (int)flt_17F10B0, 1.0);
    if ( rf_managed_particle_effect_get_room_byte352(i) )
      rf_particle_emitter_process(*(_DWORD *)i);
    result = *((float **)i + 6);
  }
  return result;
}

