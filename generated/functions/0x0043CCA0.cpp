// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CCA0 sub_43CCA0
// UNREALRED VERIFIED [combat-named-sphere-capacity-20261112]: Authored source overrides append48bytes atthis+4+48*count, only when count!=8. Exactly count8 returns-1 without writing/incrementing.423760 ignores that return after consuming all row fields; runtime42F6C0 sees onlyFIRST8authored rows, notfirst8matchednames. Duplicate and unmatched rows occupy capacity.
int __thiscall sub_43CCA0(
        _DWORD *this,
        char a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13)
{
  int v14; // [esp+Ch] [ebp-8h]

  if ( *this == 8 )
    return -1;
  v14 = (*this)++;
  qmemcpy(this + 12 * v14 + 1, &a2, 0x30u);
  return v14;
}

