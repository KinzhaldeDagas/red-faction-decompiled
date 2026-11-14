// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DD27 __trandisp2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal x87 dispatch: incoming EDX descriptor, EBP caller-owned frame and ST0/ST1 numeric operands; not EAX numeric return or incoming fpstat argument. If
// descriptorBYTE+14==5, derive temporary CW from savedWORD[frame-164] by OR high-byte2,AND high-byte0xFE,set low-byte0x3F; otherwise CW0x133F. Store temporaryCW[frame-162],FLDCW it.
// FXAM ST0,save statusWORD[frame-160],store descriptor[frame-148],zero errorBYTE[frame-144]; FXCH,FXAM other operand,save status and FXCH back. Classify each status high nibble
// via16-byte lookup6650AC using sign/rotate/mask operations. Compute signed byteOffset=lookup(firstStatus) OR (lookup(secondStatus)<<2), sign-extend AL; ECX &=0x404 retains sign
// markers; tail-JMP descriptor DWORD[16+signedByteOffset], with NO additional multiply. No RET or own frame here; selected handlers own numeric computation and return ST0 to original
// caller. Does not pop caller stack args, allocate, validate descriptor/frame or restore CW itself; cintrinexit does restoration. FP status is produced by FXAM inside body; false
// incoming fpstat and EAX-result types corrected.
long double __usercall _trandisp2@<st0>(
        const void *descriptor@<edx>,
        void *frame@<ebp>,
        long double operand0@<st0>,
        long double operand1@<st1>)
{
  __int16 v4; // fps
  __int16 v5; // bx
  __int16 v7; // fps
  char v9; // cl
  __int16 v10; // cx
  char v13; // ah

  if ( *((_BYTE *)descriptor + 14) == 5 )
  {
    HIBYTE(v5) = HIBYTE(*((_WORD *)frame - 82)) & 0xFC | 2;
    LOBYTE(v5) = 63;
  }
  else
  {
    v5 = 4927;
  }
  *((_WORD *)frame - 81) = v5;
  _EBX = &unk_6650AC;
  __asm { fxam }
  *((_DWORD *)frame - 37) = descriptor;
  *((_WORD *)frame - 80) = v4;
  *((char *)frame - 144) = 0;
  _ST6 = operand0;
  v9 = *((char *)frame - 159);
  __asm { fxam }
  *((_WORD *)frame - 80) = v7;
  HIBYTE(v10) = __ROL1__((char)(2 * *((char *)frame - 159)) >> 1, 1);
  _AL = HIBYTE(v10) & 0xF;
  __asm { xlat }
  v13 = _AL;
  LOBYTE(v10) = __ROL1__((char)(2 * v9) >> 1, 1);
  _AL = v10 & 0xF;
  __asm { xlat }
  (*(void (__thiscall **)(int))((char *)descriptor + (char)((4 * v13) | _AL) + 16))(v10 & 0x404);
  return operand0;
}

