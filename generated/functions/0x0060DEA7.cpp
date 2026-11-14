// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DEA7 __startOneArgErrorHandling
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Unary error adapter with EAX error type, EDX
// operation, ECX name pointer, ST0 proposed result; four stack DWORDs: slot0 savedCW (lowWORD read), slot1 ignored, slots2/3 original binary64 arg1. Build32-byte C math record: +0
// type,+4 name,+8 arg1,+24 retval from FSTP binary64. Own bytes at+16..23 (arg2) are NOT initialized. __87except(operation,&record,&savedCWSlot) receives three caller-popped DWORDs
// and may update retval/type. Reload record.retval via FLD; if ORIGINAL incoming savedCW WORD !=0x027F explicitly FLDCW it, else skip own reload. __87except separately restores its
// local possibly handler-modified CW, so this original-CW reload can override its changes except when incoming0x027F. Return double ST0, LEAVE/plainRET; original16 stack bytes belong
// to caller. No pointer checks/own SEH; conversions obey live x87 environment.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Refined borrowed-frame ABI: at caller core entry
// ESP=S, core reserves4 for CW; CALL adapter and PUSH EBP make EBP=S-12. EBP+8 is savedCW WORD at S-4; EBP+12 is outer return-PC at S (unused GAP, not a semantic argument);
// EBP+16/+20 are original DOUBLE at S+4. Correct custom sparse stack locations: CW@^0.2 and original@^8.8; no reserved/return-address formal. EAX type,EDX operation,ECX name,extended
// ST0 result remain register inputs. Native input conversion/record/87except/original-CW reload behavior unchanged. Fresh sparse-ABI experiment confirms this truthful type alone does
// not resolve borrowed-frame Hex-Rays call analysis; do not claim full pseudocode recovery.
double __usercall _startOneArgErrorHandling@<st0>(
        int a1@<eax>,
        int a2@<edx>,
        const char *a3@<ecx>,
        long double a4@<st0>,
        unsigned __int16 savedCW@<^0.2>,
        double original@<^8.8>)
{
  _DWORD v7[2]; // [esp+0h] [ebp-20h] BYREF
  double v8; // [esp+8h] [ebp-18h]
  double v9; // [esp+18h] [ebp-8h]

  v7[0] = a1;
  v9 = a4;
  v7[1] = a3;
  v8 = original;
  _87except(a2, v7, &savedCW);
  return v9;
}

