// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1DA0 rf_ui_state_image_get_animation_pointer
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Returns raw DWORD+8 from this32-byte state-image record. All four direct callers are staticbox animation-loader0x5F6680 using it as VANI player pointer for loop/draw-flag setters. No mode,ownership or NULL check. Prior unknown_libname_63 library label was misleading;no runtime-library semantics in body.
int __thiscall rf_ui_state_image_get_animation_pointer(_DWORD *this)
{
  return *(this + 2);
}

