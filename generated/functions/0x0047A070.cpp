// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A070 rf_level_name_is_training
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Null returns false. Otherwise performs exact case-insensitive comparisons with train01.rfl and train02.rfl; no prefix, path stripping or other training-level recognition. Called by persona admission and ordinary HUD persona-render gating, and by the separately unresolved eligibility predicate at 0x4F6F50.
bool __cdecl rf_level_name_is_training(const char *level_name)
{
  if ( !level_name )
    return 0;
  if ( !_stricmp(level_name, "train01.rfl") )
    return 1;
  return _stricmp(level_name, "train02.rfl") == 0;
}

