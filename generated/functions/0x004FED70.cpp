// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FED70 rf_event_shake_player_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_shake_player forward, vtable0x63E104 slot+4. Divide float event+0x2B8 by double100.0, round through float local, then call0x4123F0(local player+0xC4 pointer,scaled amplitude,event float+0x2BC). No explicit local-player-null, amplitude clamp or target-list gate in body.
int __thiscall rf_event_shake_player_forward(float *this)
{
  float v2; // [esp+8h] [ebp-8h]

  v2 = *(this + 174) / 100.0;
  return rf_entity_set_player_linked_perturbation_timer(*(_DWORD *)(rf_local_fpgun_player + 196), v2, *(this + 175));
}

