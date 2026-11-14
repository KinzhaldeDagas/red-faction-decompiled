// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061BDC0 crt_x87_divide_ext80_with_pattern_scaling
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 division support, KEEP library flag; native private caller-workspace ABI, not ordinary two-double arithmetic. Let B=entryESP+4.
// Denominator D is TEN-BYTE extended value atB+0, numerator N atB+12 (12-byte padded slots); saveCW wordB+24 and workCW DWORDB+28 are writable caller scratch beyond the two values.
// Entry FLD80 N then FLD80 D produces[D,N,...]. Normal outputST0 is N/D and consumes these two newly loaded values to one; preexisting deeper x87 entries remain. EAX is
// classifier/control scratch, not integer result. No conventional bool or game state.  Read H=DWORD[D+4], ADD H,H tests original significand integer bit via carry. Carry1:
// v=(H<<1)^0x0E000000. If v&0x0E000000 nonzero, directFDIVP. Otherwise index=v>>28 and BYTE665EF0[index]==0 also directly divides; original16-byte table
// is[0,1,0,0,4,0,0,7,0,0,10,0,0,13,0,0], ANYnonzero selects special pattern. If selected, raw denominator exponent WORD[D+8]&0x7FFF==0 OR0x7FFF still directly divides. Ordinary
// finite nonzero exponent: saveCW, load CW=(oldCW|0x033F)&0xF3FF (mask six exceptions, extended significand precision, nearest rounding). If raw numerator exponent==EXACT1, multiply
// BOTH current x87 operands by FLOAT665F04=1.0625; otherwise BOTH by FLOAT665F00=0.9375, exchanging and re-exchanging to retain[D,N] order. Restore ORIGINAL CW BEFORE finalFDIVP
// ST1,ST0. No F64/F32 intermediate store of scaled operands, no exception-status clear or full environment restore; native scaling exceptions/status and final caller-CW divide
// behavior remain.  Carry0: if raw denominator significand DWORD0|DWORD4==0, direct divide; nonzero raw exponent likewise direct. Only nonzero-significand/exponent0 enters
// normalization probe under same temporary CW. Numerator raw exponent0 proceeds only when its integer bit0; numerator exponent neither0 nor0x7FFF proceeds only when integer bit1;
// other cases restoreCW then direct divide. Probe preserves original denominator REGISTER value: discard current numerator register, duplicate originalD, multiply COPY by
// FLOAT665F08=2^63 and FSTP80 it back to denominator MEMORY B+0 (ten bytes only), reload numerator fromB+12, FXCH to restore originalD asST0, WAIT, restoreCW, then jump back to
// bit-classification at61BDC8 WITHOUT reloading denominator register. Thus modified denominator memory guides subsequent classification; quotient still uses retained originalD
// register unless selected shared scaling. No numerator-memory modification, saved-padding clearing, finite/zero guard, exception catch, iteration bound or rollback. Zero, infinity,
// NaN/unsupported encodings use literal field gates and x87 FLD/FDIV exception semantics; no software special-result policy is invented.
double __cdecl crt_x87_divide_ext80_with_pattern_scaling(_TBYTE a1, _TBYTE a2)
{
  double v2; // st7
  double v3; // st6
  unsigned int v4; // eax

  v2 = *(double *)&a2;
  v3 = *(double *)&a1;
  while ( !__CFADD__(DWORD1(a1), DWORD1(a1)) )
  {
    if ( !*(_QWORD *)&a1 || (HIWORD(a1) & 0x7FFF) != 0 )
      return v2 / v3;
    if ( (HIWORD(a2) & 0x7FFF) != 0 )
    {
      if ( (HIWORD(a2) & 0x7FFF) == 0x7FFF || !__CFADD__(DWORD1(a2), DWORD1(a2)) )
        return v2 / v3;
    }
    else if ( __CFADD__(DWORD1(a2), DWORD1(a2)) )
    {
      return v2 / v3;
    }
    *(double *)&a1 = v3 * flt_665F08;
    v2 = *(double *)&a2;
  }
  v4 = (2 * DWORD1(a1)) ^ 0xE000000;
  if ( (v4 & 0xE000000) != 0 )
    return v2 / v3;
  if ( !byte_665EF0[v4 >> 28] )
    return v2 / v3;
  if ( (HIWORD(a1) & 0x7FFF) == 0 || (HIWORD(a1) & 0x7FFF) == 0x7FFF )
    return v2 / v3;
  if ( (HIWORD(a2) & 0x7FFF) == 1 )
    return v2 * flt_665F04 / (v3 * flt_665F04);
  else
    return v2 * flt_665F00 / (v3 * flt_665F00);
}

