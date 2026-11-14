// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517BE0 sub_517BE0
// UNREALRED VERIFIED [particle-contact-geometry-20261104] If the supplied detail byte differs from room byte +0, stores it and moves the room between world arrays: nonzero removes the first room occurrence from ordinary array +156 and appends it to detail array +168; zero removes from +168 and appends to +156. Equal input does nothing. This ordinary/detail membership is separate from each room's ordered +108 referenced-room array. Point-room 0x532BA0 and null-room crossing 0x5170E0 iterate world +156.
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Detail setterBYTE0 relocates room pointer between solid156 ordinary and168 detail on actual flag change (removeFirst/append). solid144 remains authored ownership array. Renderer520F70 resets353/depth only over156. Source bDetailRoom mapsBYTE0; source outside flag is a separate byte66 and must not replace renderer traversal-stop byte64.
int __thiscall sub_517BE0(unsigned __int8 *this, int a2, unsigned __int8 a3)
{
  int result; // eax

  result = a3;
  if ( a3 != *this )
  {
    *this = a3;
    if ( *this )
    {
      rf_pointer_array_remove_first((int *)(a2 + 156), (int)this);
      return rf_pointer_array_append_dword((_DWORD *)(a2 + 168), (int)this);
    }
    else
    {
      rf_pointer_array_remove_first((int *)(a2 + 168), (int)this);
      return rf_pointer_array_append_dword((_DWORD *)(a2 + 156), (int)this);
    }
  }
  return result;
}

