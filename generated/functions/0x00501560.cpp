// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501560 rf_event_endgame_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_endgame forward, vtable0x63E398 slot+4. Read C string from event NAME object+0x1C and pass directly to0x453B20. Does not use event+0x2B8, traverse targets or establish endgame success independently of helper.
int __thiscall rf_event_endgame_forward(int this)
{
  char *v1; // eax

  v1 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 28));
  return rf_frontend_request_credits_or_endgame_blackout(v1);
}

