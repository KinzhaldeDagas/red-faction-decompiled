// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FDA40 rf_event_alarm_forward
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] event_alarm forward callback, vtable0x63E2D0 slot+4. Walk target vector+0x29C in authored order. Each target resolving as an entity is reactivated in place, entity+0x4D0 deadline armed at0ms, AI block entity+0x2A0 assigned mode10 with(-1,-1), secondary state12, then passed to0x4355A0. After all targets, call shared alarm enable0x4EF780 even when no entity resolves. Does not start Alarm_Siren event28 or explicitly forward mission targets in this body.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] Local forward executes each resolved entity in authored target order:4BC930 reactivation (including idle shared draw), Entity4D0 Arm0,40A1B0 mode10 args(-1,-1),40A230 secondary12 using separate seconds clock,4355A0 movement reset; then shared Enable even with zero entities. Native callback does not itself forward events; ordinary outer4FB290/4FB3C0 DOES generic completion for type46.
int __thiscall rf_event_alarm_forward(char *this)
{
  int *v1; // eax
  _DWORD *v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(this + 668); ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)this + 167, i);
    v4 = (_DWORD *)rf_entity_resolve_handle(*v1);
    if ( v4 )
    {
      rf_object_reactivate_from_respawn(v4);
      rf_replicator_arm_milliseconds(v4 + 308, 0);
      rf_ai_numeric_mode_write(v4 + 168, 10, -1, -1);
      rf_ai_secondary_state_write((int)(v4 + 168), 12);
      sub_4355A0((int)v4);
    }
  }
  return rf_alarm_enable_shared();
}

