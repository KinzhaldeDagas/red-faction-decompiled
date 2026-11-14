// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449550 rf_ai_difficulty_get_with_zero_fallback
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): No arguments. Reads raw DWORD6612A4, compares UNSIGNED to3;0..3 dispatch through PE-verified four-entry jump
// table449594 to literal EAX0/1/2/3 respectively. Every other32-bit value including signed negatives returns EAX0. Does not clamp/store the global, call random/timer helpers, or
// cache a transformed difficulty. Used by4083A0 exact0/1 admission; invalid raw difficulty therefore maps to the admitted0 case.
int rf_ai_difficulty_get_with_zero_fallback()
{
  int result; // eax

  switch ( dword_6612A4 )
  {
    case 0:
      result = 0;
      break;
    case 1:
      result = 1;
      break;
    case 2:
      result = 2;
      break;
    case 3:
      result = 3;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

