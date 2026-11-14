// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FFF60 rf_event_set_friendliness_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] RTTI event_set_friendliness forward, vtable0x63E190 slot+4. Target resolver here is rf_object_resolve_handle for common objects, not entity-only. Each resolving target receives raw event dword+0x2B8 through0x4BBF50: store common friendliness+0x1F8 and clear entity target+0x560 only when object-is-entity. Does not recurse targets or directly enter combat.
int __thiscall rf_event_set_friendliness_forward(int *this)
{
  int result; // eax
  int *v2; // eax
  int i; // [esp+4h] [ebp-8h]
  int v5; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 167);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200(this + 167, i);
    v5 = rf_object_resolve_handle(*v2);
    if ( v5 )
      sub_4BBF50(v5, *(this + 174));
  }
  return result;
}

