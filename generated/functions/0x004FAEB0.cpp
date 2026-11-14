// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAEB0 rf_event_unhide_create
// UNREALRED VERIFIED [mission-protection-20261020] UnHide construction sets both pending bytes zero and arms its shared deadline+0x2B8 with0ms. Show/hide input setters do not restart this deadline, so first work may run in the next event frame update.
// UNREALRED VERIFIED [mission-visibility-20261020] Polling construction arms the deadline with0ms rather than leaving it negative/unarmed. Pending-show and pending-hide both start0. The local runtime poll is independent of base authored event Delay and generic linked activation.
int __cdecl rf_event_unhide_create(float *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_mission_event_create_at_position(a1, 0x32u);
  if ( v2 )
  {
    *(_BYTE *)(v2 + 700) = 0;
    *(_BYTE *)(v2 + 701) = 0;
    rf_replicator_arm_milliseconds((int *)(v2 + 696), 0);
  }
  return v2;
}

