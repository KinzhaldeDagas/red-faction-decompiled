// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BC40 rf_ai_scripted_action_has_remaining_time
// UNREALRED VERIFIED [ai-script-animation-release-20261013] Filename action activity is retained index Entity+0x1368 != -1 AND rf_vfx_get_remaining_time(model,index) != 0. For character instances, a held endpoint has a record but zero remaining time and is therefore inactive for this cleanup predicate.
bool __cdecl rf_ai_scripted_action_has_remaining_time(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 4968) != -1
      && rf_vfx_get_remaining_time((const void *)*(_DWORD *)(*(_DWORD *)a1 + 128), *(_DWORD *)(*(_DWORD *)a1 + 4968)) != 0.0;
}

