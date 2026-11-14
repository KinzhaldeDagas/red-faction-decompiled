// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FDD40 rf_event_goto_dispatch
// UNREALRED VERIFIED [ai-script-animation-release-20261013] Goto invokes 0x40BCF0 before target clearing and destination installation, without a dead-entity gate. It does not unconditionally clear all body actions, stop weapon Foley, zero attack stance or clear scheduler bit 8. Destination installation and route building invoke the same cleanup again.
// UNREALRED VERIFIED [ai-script-target-clear-20261029] Goto explicitly calls guarded target setter40BA80(AI,-1), then proceeds to destination install410ED0 without checking setter return or whether target cleared. Disabled nonsentient/player-associated owners or player-only bit0x80 may retain the existing target while Goto installs. Do not substitute an unconditional lifecycle target clear or skip Goto on a rejected clear.
int __thiscall rf_event_goto_dispatch(char *this)
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
    v4 = rf_entity_resolve_handle(*v2);
    if ( v4 )
    {
      rf_ai_clear_scripted_animation_context((int *)(v4 + 672));
      sub_40BA80((int *)(v4 + 672), -1);
      if ( !rf_ai_goto_install_destination(
              *(_DWORD *)(v4 + 44),
              (float *)this + 16,
              *(this + 696),
              *(this + 698),
              *(this + 699)) )
      {
        if ( *(this + 697) == 1 )
          sub_4355A0(v4);
        else
          sub_435500(v4, 0);
      }
    }
  }
  return result;
}

