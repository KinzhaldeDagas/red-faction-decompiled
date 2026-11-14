// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592030 rf_command_line_option_destruct_argument_and_unlink
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall option. Calls592080 to delete owned argument+16; if borrowed name+8 nonnull, patches prev->next and next->prev using links+0/+4 then clears receiver links. Returns receiver, does not free receiver/name or interpret auxiliary DWORD+12 or clear name/matched/requires fields. Repeating destructor on a named option after links cleared is not guarded.
void **__thiscall rf_command_line_option_destruct_argument_and_unlink(void **this)
{
  void **result; // eax

  rf_command_line_option_delete_argument(this);
  result = this;
  if ( *(this + 2) )
  {
    *(_DWORD *)*(this + 1) = *this;
    *((_DWORD *)*this + 1) = *(this + 1);
    *this = nullptr;
    *(this + 1) = nullptr;
    return this;
  }
  return result;
}

