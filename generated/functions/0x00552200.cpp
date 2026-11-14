// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552200 sub_552200
// UNREALRED VERIFIED [ai-navigation-import-20261028] Returns pointer-array backing address +4*index without bounds checks. Used by AI0x40DCA0 after list/cursor bounds checks, but that caller does not range-check the point index stored in the list. Do not claim native safe rejection of -1 list point references. Unreal typed-data route consumers must validate these authored indices explicitly.
int __thiscall sub_552200(_DWORD *this, int a2)
{
  return *(this + 2) + 4 * a2;
}

