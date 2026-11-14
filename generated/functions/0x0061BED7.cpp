// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061BED7 crt_x87_divide_register_form_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime register-form x87 divide dispatcher, KEEP library flag. No stack arguments consumed; operand encoding is FULL EAX masked with0x3F
// (equivalently low6AL bits), then PE-verified64-DWORD table665F4E. Reserve44-byte private workspace first. Let i=selector>>3 (0..7), k=selector&7, initial valid x87 values A0..A7.
// Cases k1 or3 restoreESP then execute software INT6 with no own RET/fallback; a resuming interrupt handler would fall through into following code after workspace was removed, so do
// not turn this into a safe default return. i0 cases k0/4 execute raw FDIV ST0,ST0, k2/6 raw FDIVR ST0,ST0; k5 FDIVP ST0,ST0 and k7 FDIVRP ST0,ST0 compute then POP/discard that top
// result. Divide-by-zero/NaN effects are native, not constant1 substitutions.  For i1..7 every valid case marshals two80-bit operands into workspace0/12 and calls61BDC0 once;
// slots24/28 are coreCW scratch and auxiliary80-bit slot32 preserves a value when needed. Exact normal-stack effects: k0 replaceST0 with A0/Ai retainingAi; k2 replaceST0 withAi/A0
// retainingAi; k4 replaceSTi withAi/A0 retainingA0; k6 replaceSTi withA0/Ai retainingA0; k5 replaceSTi withAi/A0 then pop originalST0; k7 replaceSTi withA0/Ai then pop originalST0.
// All other original entries retain relative values/order; raw FXCH/FSTP80/FLD80 marshaling and core scaling/status behavior are authoritative for exceptional encodings. No pop for
// k0/2/4/6, one for k5/7. Restore44-byte workspace on ordinary paths. EAX is masked selector or core scratch residue, not a quotient/status integer; incoming ECX/EDX are not
// interface arguments. No allocation, RF state, extra subtype, bounds fallback or universal FP-status restoration.
// positive sp value has been detected, the output may be wrong!
void __usercall crt_x87_divide_register_form_dispatch(char a1@<al>)
{
  _TBYTE v1; // [esp-2Ch] [ebp-58h]
  _TBYTE v2; // [esp-20h] [ebp-4Ch]
  _TBYTE v17; // [esp+0h] [ebp-2Ch]
  _TBYTE v18; // [esp+Ch] [ebp-20h]

  switch ( a1 & 0x3F )
  {
    case 0:
      __asm { fdiv    st, st; UNREALRED VERIFIED: i0rawselfdivision,notconstant1; zero/NaN stillnativeexceptionbehavior. }
      return;
    case 1:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_4;
    case 2:
LABEL_4:
      __asm { fdivr   st, st; jumptable 0061BEDD case 2 }
      return;
    case 3:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_6;
    case 4:
LABEL_6:
      __asm { fdiv    st, st; jumptable 0061BEDD case 4 }
      return;
    case 5:
      __asm { fdivp   st, st; UNREALRED VERIFIED: FDIVP ST0,ST0 computesANDPOPS/discardstopresult; deeperentriesmoveup. }
      return;
    case 6:
      __asm { fdivr   st, st; jumptable 0061BEDD case 6 }
      return;
    case 7:
      __asm { fdivrp  st, st; jumptable 0061BEDD case 7 }
      return;
    case 8:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 8
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fld     [esp+2Ch+var_C]
        fxch    st(1)
      }
      return;
    case 9:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_12;
    case 0xA:
LABEL_12:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0061BEDD case 10
        fstp    [esp+arg_8]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fld     [esp+arg_8]
        fxch    st(1)
      }
      return;
    case 0xB:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_14;
    case 0xC:
LABEL_14:
      __asm
      {
        fxch    st(1); jumptable 0061BEDD case 12
        fstp    [esp+arg_8]; _TBYTE
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm { fld     [esp+arg_1C] }
      return;
    case 0xD:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0061BEDD case 13
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      return;
    case 0xE:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 14
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fld     [esp+2Ch+var_20] }
      return;
    case 0xF:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 15
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      return;
    case 0x10:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 16
        fxch    st(1); UNREALRED VERIFIED: Higheri formsuseFXCH(i-1) afterpoppingtop; actualindexshift matters.
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(1)
        fld     [esp+2Ch+var_C]
        fxch    st(2)
      }
      return;
    case 0x11:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_20;
    case 0x12:
LABEL_20:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0061BEDD case 18
        fxch    st(1)
        fstp    [esp+arg_8]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(1)
        fld     [esp+arg_8]
        fxch    st(2)
      }
      return;
    case 0x13:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_22;
    case 0x14:
LABEL_22:
      __asm
      {
        fxch    st(2); jumptable 0061BEDD case 20
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(1)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(1)
        fld     [esp+arg_1C]
      }
      return;
    case 0x15:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0061BEDD case 21
        fxch    st(1)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(1) }
      return;
    case 0x16:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 22
        fxch    st(1)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(1)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x17:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 23
        fxch    st(1)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(1) }
      return;
    case 0x18:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 24
        fxch    st(2)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(2)
        fld     [esp+2Ch+var_C]
        fxch    st(3)
      }
      return;
    case 0x19:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_28;
    case 0x1A:
LABEL_28:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0061BEDD case 26
        fxch    st(2)
        fstp    [esp+arg_8]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(2)
        fld     [esp+arg_8]
        fxch    st(3)
      }
      return;
    case 0x1B:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_30;
    case 0x1C:
LABEL_30:
      __asm
      {
        fxch    st(3); jumptable 0061BEDD case 28
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(2)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(2)
        fld     [esp+arg_1C]
      }
      return;
    case 0x1D:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0061BEDD case 29
        fxch    st(2)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(2) }
      return;
    case 0x1E:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 30
        fxch    st(2)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(2)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x1F:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 31
        fxch    st(2)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(2) }
      return;
    case 0x20:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 32
        fxch    st(3)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(3)
        fld     [esp+2Ch+var_C]
        fxch    st(4)
      }
      return;
    case 0x21:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_36;
    case 0x22:
LABEL_36:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0061BEDD case 34
        fxch    st(3)
        fstp    [esp+arg_8]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(3)
        fld     [esp+arg_8]
        fxch    st(4)
      }
      return;
    case 0x23:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_38;
    case 0x24:
LABEL_38:
      __asm
      {
        fxch    st(4); jumptable 0061BEDD case 36
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(3)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(3)
        fld     [esp+arg_1C]
      }
      return;
    case 0x25:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0061BEDD case 37
        fxch    st(3)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(3) }
      return;
    case 0x26:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 38
        fxch    st(3)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(3)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x27:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 39
        fxch    st(3)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(3) }
      return;
    case 0x28:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 40
        fxch    st(4)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(4)
        fld     [esp+2Ch+var_C]
        fxch    st(5)
      }
      return;
    case 0x29:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_44;
    case 0x2A:
LABEL_44:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0061BEDD case 42
        fxch    st(4)
        fstp    [esp+arg_8]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(4)
        fld     [esp+arg_8]
        fxch    st(5)
      }
      return;
    case 0x2B:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_46;
    case 0x2C:
LABEL_46:
      __asm
      {
        fxch    st(5); jumptable 0061BEDD case 44
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(4)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(4)
        fld     [esp+arg_1C]
      }
      return;
    case 0x2D:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0061BEDD case 45
        fxch    st(4)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(4) }
      return;
    case 0x2E:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 46
        fxch    st(4)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(4)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x2F:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 47
        fxch    st(4)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(4) }
      return;
    case 0x30:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 48
        fxch    st(5)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(5)
        fld     [esp+2Ch+var_C]
        fxch    st(6)
      }
      return;
    case 0x31:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_52;
    case 0x32:
LABEL_52:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0061BEDD case 50
        fxch    st(5)
        fstp    [esp+arg_8]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(5)
        fld     [esp+arg_8]
        fxch    st(6)
      }
      return;
    case 0x33:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_54;
    case 0x34:
LABEL_54:
      __asm
      {
        fxch    st(6); jumptable 0061BEDD case 52
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(5)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(5)
        fld     [esp+arg_1C]
      }
      return;
    case 0x35:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0061BEDD case 53
        fxch    st(5)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(5) }
      return;
    case 0x36:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 54
        fxch    st(5)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(5)
        fld     [esp+2Ch+var_20]
      }
      return;
    case 0x37:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 55
        fxch    st(5)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(5) }
      return;
    case 0x38:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 56
        fxch    st(6)
        fld     st
        fstp    [esp+2Ch+var_2C]; _TBYTE
        fstp    [esp+2Ch+var_C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(6)
        fld     [esp+2Ch+var_C]
        fxch    st(7)
      }
      return;
    case 0x39:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_60;
    case 0x3A:
LABEL_60:
      __asm
      {
        fstp    tbyte ptr [esp+0]; jumptable 0061BEDD case 58
        fxch    st(6)
        fstp    [esp+arg_8]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(6)
        fld     [esp+arg_8]
        fxch    st(7)
      }
      return;
    case 0x3B:
      __asm { int     6;  - internal hardware - UNDEFINED OPCODE (80286+) }
      goto LABEL_62;
    case 0x3C:
LABEL_62:
      __asm
      {
        fxch    st(7); jumptable 0061BEDD case 60
        fstp    [esp+arg_8]; _TBYTE
        fxch    st(6)
        fld     st
        fstp    tbyte ptr [esp+0]; _TBYTE
        fstp    [esp+arg_1C]
      }
      crt_x87_divide_ext80_with_pattern_scaling(v17, v18);
      __asm
      {
        fxch    st(6)
        fld     [esp+arg_1C]
      }
      break;
    case 0x3D:
      __asm
      {
        fstp    [esp+2Ch+var_2C]; jumptable 0061BEDD case 61
        fxch    st(6)
        fstp    [esp+2Ch+var_20]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(6) }
      break;
    case 0x3E:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 62
        fxch    st(6)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm
      {
        fxch    st(6)
        fld     [esp+2Ch+var_20]
      }
      break;
    case 0x3F:
      __asm
      {
        fstp    [esp+2Ch+var_20]; jumptable 0061BEDD case 63
        fxch    st(6)
        fstp    [esp+2Ch+var_2C]; _TBYTE
      }
      crt_x87_divide_ext80_with_pattern_scaling(v1, v2);
      __asm { fxch    st(6) }
      break;
  }
}

