// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006105CA __ceil_default
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Default ceil, cdecl(double),ST0 result. ctrlFP(LIVE
// DWORD0x00665100,0xFFFF) installs raw x87 CW and saves old rawCW in EBX. Original compiled words: ceil665100=0x1B3F (round up),floor665460=0x173F (round down); both raw precision
// bits0x300, not an assumed0x027F constant. Globals mutable; routine follows current stored value. FLD/FSTP creates binary64 copy before sptype/frnd; raw exponent extracted via DWORD
// read at argument+6 (two following bytes read but masked away). All-ones exponent ->sptype of FP-loaded/stored copy:1/2 restore oldCW and reload original infinity;3 delegate
// handle_qnan1(12,original,oldCW); any other class uses except1(flags8,operation12,original,original+verified1.0,oldCW). Copy may already quiet a signaling NaN under live working CW,
// so do not equate branch with raw original payload classification. Finite path frnd(original) performs FRNDINT and binary64 store/reload under installed CW, store result local,
// compare original vs result via x87 FCOMP/FNSTSW TEST AH,44h. Equal ->restore CW/return result; unequal OR unordered then oldCW bit0x20 SET ->same restore, otherwise
// except1(flags0x10,operation12,original,rounded,oldCW). Delegate may modify result/errno or raise. Own restore covers raw x87 CW, not status/MXCSR; no own SEH/finally if helper
// throws. All argument widths/caller cleanup8/16/28 verified, no independent output pointer.
double __cdecl _ceil_default(double a1)
{
  unsigned int v1; // ebx
  int v2; // eax
  double v4; // [esp+1Ch] [ebp-8h]

  v1 = _ctrlfp(dword_665100, 0xFFFFu);
  if ( (HIWORD(a1) & 0x7FF0) == 0x7FF0 )
  {
    v2 = _sptype(a1);
    if ( v2 > 0 )
    {
      if ( v2 <= 2 )
      {
        _ctrlfp(v1, 0xFFFFu);
        return a1;
      }
      if ( v2 == 3 )
        return _handle_qnan1(12, a1, v1);
    }
    return _except1(8u, 12, a1, a1 + 1.0, v1);
  }
  else
  {
    v4 = _frnd(a1);
    if ( a1 == v4 || (v1 & 0x20) != 0 )
    {
      _ctrlfp(v1, 0xFFFFu);
      return v4;
    }
    else
    {
      return _except1(0x10u, 12, a1, v4, v1);
    }
  }
}

