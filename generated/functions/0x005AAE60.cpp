// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AAE60 sub_5AAE60
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns raw DWORD+892. Observed tooltip caller0x5A9F80 tests it nonzero for base-kind0/gadget-type1 before virtual region hit-test+24. Body does not establish whether value is a pointer,flag or count,so existing name is retained pending consumer/type verification. No mutation.
int __thiscall sub_5AAE60(_DWORD *this)
{
  return *(this + 223);
}

