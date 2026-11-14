// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005211F0 sub_5211F0
// UNREALRED VERIFIED [decal-face-links-20261028]: Returns raw byte at this+2. No normalization, null check or other effects. Full semantic role of this byte remains unproven; do not infer decal ownership from address neighborhood.
char __thiscall sub_5211F0(_BYTE *this)
{
  return *(this + 2);
}

