// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DC25 __setdefaultprecision
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs precision initializer. Cdecl
// controlfp_s(NULLoutput,NewValue10000h,Mask30000h),reclaim12; original mapping requests native x87 precision field0200h. Normal zero status returns0. Nonzero delegate status
// ->invoke_watson with five zero slots,reclaim20 if it unexpectedly returns. Original EAX error code not saved across Watson,so no promised forwarding of that error on unexpected
// return. ESI saved0 used for zero arguments. Given unchanged controlfp_s these literal flags pass bit validation; no own hardware probing,locale,errno assignment,lock or SEH.
// Hardware control/possible FP traps delegated; no full FPU reset or status clear.
errno_t _setdefaultprecision()
{
  errno_t result; // eax

  result = _controlfp_s(nullptr, 0x10000u, 0x30000u);
  if ( result )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  return result;
}

