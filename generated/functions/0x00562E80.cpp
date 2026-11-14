// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562E80 rf_model_handle_consume_named_animation_trigger
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Only tag2 delegates character instance consume_named_trigger(instance4,name), returning its byte result. Every other tag returns0. Does not queue a scene event, perform node-name search, or validate name/instance itself.
char __thiscall rf_model_handle_consume_named_animation_trigger(int **this, const char *a2)
{
  if ( *this == (int *)2 )
    return rf_character_instance_consume_named_trigger(*(this + 1), a2);
  else
    return 0;
}

