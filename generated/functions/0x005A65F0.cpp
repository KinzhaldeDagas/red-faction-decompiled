// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A65F0 rf_text_list_destroy_entries_and_base
// UNREALRED VERIFIED [list-selection-20261029]: Walks first-node pointer+732 until sentinel this+724. Temporarily stores current node in last pointer+736,advances first through node.next+8,then calls0x5A9670(node,1) to destroy/free each. Resets first,last to sentinel and selected+692=0,then delegates base cleanup0x5AB7B0. No per-node unlink helper or explicit extent reset here. Base cleanup releases global focus if this owns it,clears DWORD+604,then calls0x5F0F30. Function is destructor path,not merely non-destructive clear.
int __thiscall rf_text_list_destroy_entries_and_base(_DWORD *this)
{
  while ( (_DWORD *)*(this + 183) != this + 181 )
  {
    *(this + 184) = *(this + 183);
    *(this + 183) = *(_DWORD *)(*(this + 183) + 8);
    if ( *(this + 184) )
      rf_text_entry_scalar_deleting_destructor((_DWORD *)*(this + 184), 1);
  }
  *(this + 183) = this + 181;
  *(this + 184) = this + 181;
  *(this + 173) = 0;
  return rf_ui_gadget_destroy(this);
}

