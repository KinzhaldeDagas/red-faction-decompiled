// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565060 rf_character_trigger_query
// UNREALRED VERIFIED [animation-trigger-decode]: Queries a named CharacterInstance animation trigger for the current update.
char __cdecl rf_character_trigger_query(int **a1, const char *a2)
{
  return rf_model_handle_consume_named_animation_trigger(a1, a2);
}

