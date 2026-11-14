// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500CE0 rf_event_attack_reverse
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_attack reverse, vtable0x63E258 slot+8. Resolve same single attacker through event+0x2B8/0x4BC680/entity id. Call guarded target setter(AI,-1), then AI restore helper0x40A2A0. Does not traverse authored target list or directly clear target field.
void __thiscall rf_event_attack_reverse(int *this)
{
  int v1; // [esp+4h] [ebp-8h]
  int v2; // [esp+8h] [ebp-4h]

  v2 = rf_object_find_by_saved_identifier(*(this + 174));
  if ( v2 )
  {
    v1 = rf_entity_resolve_handle(*(_DWORD *)(v2 + 44));
    if ( v1 )
    {
      sub_40BA80((int *)(v1 + 672), -1);
      sub_40A2A0((int *)(v1 + 672));
    }
  }
}

