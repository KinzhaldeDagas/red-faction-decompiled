// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABCF0 rf_ui_gadget_query_parent_region
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall screen X,Y. Parent+616 nonnull forwards to parent virtual region hit-test+24;otherwise calls owner-window hit-mask query0x5B1020. Returns raw helper region result,including negatives. No owner-null check or local bounds test.
int __thiscall rf_ui_gadget_query_parent_region(_DWORD **this, int a2, int a3)
{
  if ( *(this + 154) )
    return (*(int (__thiscall **)(_DWORD, int, int))(**(this + 154) + 24))(*(this + 154), a2, a3);
  else
    return rf_ui_window_hit_mask_value_at_screen_point(*(this + 151), a2, a3);
}

