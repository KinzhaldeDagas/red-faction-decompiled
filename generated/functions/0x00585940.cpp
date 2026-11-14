// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00585940 rf_character_instance_unlink_and_clear_actions
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): If base-character pointer+7504 isNULL, returns immediately without unlinking. Otherwise sets record indices+7420,+7424,+7496=-1, repeatedly removes first action until count+4816<=0, then unlinks circular instance list using next+7508/prev+7512 and head18CDA28. Singleton head clears links/head and returnsNULL; multi-entry head advances before patching neighbors. Clears both link pointers but leaves base-character pointer and containing memory intact. Return incidental. Assumes valid circular links and removals reduce count.
int *__thiscall rf_character_instance_unlink_and_clear_actions(int *this)
{
  int *result; // eax

  result = this;
  if ( *(this + 1876) )
  {
    *(this + 1855) = -1;
    *(this + 1856) = -1;
    *(this + 1874) = -1;
    while ( *(this + 1204) > 0 )
      rf_character_instance_remove_action_record(this, *(this + 1205));
    if ( (int *)unk_18CDA28 == this )
    {
      result = (int *)*(this + 1877);
      if ( result == this )
      {
        *(this + 1877) = 0;
        *(this + 1878) = 0;
        unk_18CDA28 = 0;
        return result;
      }
      unk_18CDA28 = *(this + 1877);
    }
    *(_DWORD *)(*(this + 1878) + 7508) = *(this + 1877);
    *(_DWORD *)(*(this + 1877) + 7512) = *(this + 1878);
    *(this + 1877) = 0;
    *(this + 1878) = 0;
    return nullptr;
  }
  return result;
}

