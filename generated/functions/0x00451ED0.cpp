// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00451ED0 rf_input_scan_code_is_chat_reserved
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(full32-bit scanCode), returns AL only. Subtracts1 with wrapping32-bit arithmetic,
// unsigned-bounds checks resulting value<=85, then uses PE-verified86-byte selector and two-entry jump table. Returns AL1 exactly for full input1..28,30..54,57,86; all other32-bit
// inputs return AL0, including0,29,55,56,58..85,87+,negative. No key-state/input/event reads, callbacks or mutation; upper EAX bits are incidental selector/input residue, not full
// normalized bool.
char __cdecl rf_input_scan_code_is_chat_reserved(int a1)
{
  char result; // al

  switch ( a1 )
  {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 57:
    case 86:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

