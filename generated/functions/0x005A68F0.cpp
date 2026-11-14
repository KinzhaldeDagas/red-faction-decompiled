// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A68F0 rf_text_list_construct
// UNREALRED VERIFIED [list-selection-20261029]: Calls base UI constructor0x5AB7F0,installs ui_listbox vtable,constructs Replicator at+668 and base-entry sentinel at+724. Clears flags+628,vertical/horizontal bar pointers+784/+788,selected+692,width callback+796;sets first+732,last+736 to sentinel. Other list extent,scroll,padding and search fields initialized later by0x5A69D0. Returns this; no entry/bar allocation here.
int *__thiscall rf_text_list_construct(int *this)
{
  rf_ui_gadget_construct(this);
  *this = (int)&ui_listbox::`vftable';
  rf_clock_deadline_construct_invalid(this + 167);
  rf_text_entry_construct(this + 181);
  *(this + 157) = 0;
  *(this + 196) = 0;
  *(this + 197) = 0;
  *(this + 183) = (int)(this + 181);
  *(this + 184) = (int)(this + 181);
  *(this + 173) = 0;
  *(this + 199) = 0;
  return this;
}

