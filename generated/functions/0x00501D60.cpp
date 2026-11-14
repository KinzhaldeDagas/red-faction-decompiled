// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501D60 rf_event_reverse_mover_apply_forward
// UNREALRED VERIFIED [mission-mover-events-20261020] Reverse_Mover forward handler iterates authored targets, resolves mover owners, skips waiting or idle states via0x48A720, and reverses only when current direction bit0x2000 equals event byte+0x2B8. Loader derives that byte as generic integer0 == 0. Duplicate targets cannot reverse twice because the first operation changes direction. No rotating-kind exclusion. Type89 suppresses automatic forwarding in both directions.
int __thiscall rf_event_reverse_mover_apply_forward(_BYTE *this)
{
  int result; // eax
  int *v2; // eax
  int v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(this + 668);
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)this + 167, i);
    v4 = rf_mover_resolve_handle(*v2);
    if ( v4
      && !rf_mover_is_waiting_or_idle(v4)
      && ((*(_DWORD *)(v4 + 792) & 0x2000) != 0 && *(this + 696)
       || (*(_DWORD *)(v4 + 792) & 0x2000) == 0 && !*(this + 696)) )
    {
      rf_mover_reverse_linear_segment(v4);
    }
  }
  return result;
}

