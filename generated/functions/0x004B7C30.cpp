// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7C30 rf_object_get_use_classification
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall common object. Unsigned type DWORD+36 dispatches0..5; other values including negative signed return0. Type0 reads definition pointer+660 then definition DWORD+436; type4 reads definition+68. Type2 returns8; type5 returns7; types1/3 return0. Full six-entry jump table verified against original PE. No pointer/class/use-range validation or state mutation; this classifier is separate from common friendliness+504, team identity or attached entity handle+512.
int __thiscall rf_object_get_use_classification(_DWORD *this)
{
  int result; // eax

  switch ( *(this + 9) )
  {
    case 0:
      result = *(_DWORD *)(*(this + 165) + 436);
      break;
    case 2:
      result = 8;
      break;
    case 4:
      result = *(_DWORD *)(*(this + 165) + 68);
      break;
    case 5:
      result = 7;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

