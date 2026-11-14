// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00618F47 ___strgtold12_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(output12*,MANDATORY
// endPointerSlot*,text*,preserveGuardFlag,fallbackExponent,implicitFractionDigits,allowBareExponentSign,LocaleUpdate*), int status mask. First/output and final locale-update pointer
// types corrected. Only explicit argument validation is LocaleUpdate!=NULL: failure errno22 + invalid_parameter5zeros; if handler returns, return0 WITHOUT output/end writes, despite0
// otherwise meaning no coarse error. No input/output/end NULL guards, length limit or LocaleUpdate acquisition/cleanup. Normal cookie check; no SEH/finally. Packed output12 layout:
// unsigned80-bit significand bytes0..9, sign/exponentWORD at10; writes WORD0,DWORD2,DWORD6,WORD10. Integer-only decimal parser, no x87 instructions, infinity/NaN names or hexadecimal
// syntax. Initially skip EXACT bytes SPACE,HT,LF,CR (not VT/FF/locale whitespace); decimal separator is ONLY first byte via LocaleUpdate.locinfo+188 -> lconv -> decimal_point.
// Original-byte-verified12-entry table61960F dispatches states0..11 (state10 default/exit). Optional initial +/-, leading zeros, integer digits, separator/fraction, D/d/E/e exponent
// accepted. Signs encountered after mantissa become an exponent ONLY if allowBareExponentSign!=0; otherwise parsing stops before that sign. Marker without valid exponent digits rolls
// end pointer back to D/E marker; bare-sign failure rolls back to that sign. Explicit exponent zeros count as an exponent and suppress fallbackExponent. Exponent magnitude clamps
// at5201 once>5200, but consumes remaining decimal exponent digits. Store at most25 NUMERIC digit bytes, skipping leading integer zeros and fractional leading zeros; extra integer
// digits beyond25 increment decimal offset, extra fractional digits beyond25 do NOT. Fractional leading zeros decrement offset, each stored fractional digit decrements it. Reaching
// valid stop ALWAYS publishes current end pointer BEFORE conversion. No-mantissa-digit flag -> status4, signed zero. Rollback is STATE-DEPENDENT: invalid after initial sign or
// initial separator returns original untrimmed text pointer; invalid initial character/whitespace-only state can leave end at stop after skipped whitespace. Valid allzero mantissa ->
// status0 signed zero without calling mtold12. IMPORTANT exact boundary behavior: with25 collected digits, compare signed BYTE at EBP-9 with5 and increment THAT SAME BYTE if>=5;
// buffer starts EBP-32, so this is retained digit INDEX23 (24th), NOT discarded digit index24 at EBP-8. Then drop25th digit, set count24, increment decimal offset. Native bytes
// independently verify displacements; no correction to conventional rounding is applied. Increment can create numeric byte10, handled arithmetically by mtold12. Strip trailing stored
// numeric zero bytes, decrement count/increment offset, then mtold12(nonzero numeric digits,count,local12). First stored digit nonzero makes zero-normalization hang in mtold12
// unreachable on this intended path. Effective decimal exponent = signed explicitExponent + decimalOffset; ADD fallbackExponent iff NO explicit exponent digits; SUBTRACT
// implicitFractionDigits iff NO decimal separator, all32-bit arithmetic. >5200 -> signed extended infinity/status2; <-5200 -> signed zero/status1. These are COARSE exponent checks,
// not exhaustive representability checks. For nonzero effective exponent, preserveGuardFlag0 clears LOW WORD of internal80-bit significand BEFORE scaling; zero effective exponent
// does NOT clear it. Consume abs(exponent) base8, positive selects positive-power table6660F8, negative selects inverse666258; selected record=base+84*group+12*(digit-1). Reviewed29
// records each side: groups7 entries for powers1..7,8..56,64..448,512..3584, then4096. All58 entries verified against powers10 with native bias correction (guardWORD>=8000 -> copy12
// bytes and decrement DWORD+2), rational relative error<2^-70. Coarse exponent bound5200 keeps highest base8 digit<=1 for fifth group; table/index bounds not separately checked. Each
// inlined multiply clears96-bit scratch, performs triangular5+4+3+2+1 unsigned16-bit selected-limb products with explicit DWORD carries/adjacent WORD increments; sign XOR and LOW16
// exponent sum. Either exponent>=7FFF or sum>BFFD -> infinity; sum<=3FBF -> zero. Zero-exponent operands increment sum, with zero-mantissa shortcuts. Subtract3FFE; normalize left96
// until topbit or exponent<=0, then underflow right shifts with sticky lowbit. Guard16>8000 OR low17==18000 -> nearest-even retained-limb increment with carry/exponent adjustment.
// Retain product bits16..95 as80-bit significand; exponent>=7FFF -> infinity. No unbounded-precision assertion: this is native selected-limb arithmetic. Internal multiplication
// zero/infinity outcomes DO NOT SET status1/2; ordinary status can remain0 even when scaling produces those values. Finally OR parsed input sign into output exponent, return
// status0/1/2/4. No errno range assignment, full-consumption requirement or public endptr-optional policy.
int __cdecl __strgtold12_l(_BYTE *a1, char **a2, char *a3, int a4, int a5, int a6, int a7, _LocaleUpdate *a8)
{
  int v8; // ecx
  signed __int8 *v9; // edi
  char *v11; // edx
  char v12; // al
  char v13; // al
  int v14; // eax
  int v15; // eax
  char *v16; // edx
  int v17; // eax
  int v18; // eax
  bool v19; // zf
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // eax
  char *v24; // ecx
  char v25; // al
  char *v26; // ecx
  int v27; // eax
  char *v28; // ebx
  __int16 v29; // cx
  __int16 v30; // si
  unsigned __int16 v31; // cx
  __int16 v32; // si
  unsigned __int16 v33; // dx
  int v34; // eax
  _WORD *v35; // edi
  unsigned int v36; // eax
  unsigned int v37; // ecx
  unsigned int v38; // esi
  __int16 v39; // dx
  unsigned int v40; // eax
  int v41; // esi
  int v42; // eax
  int v43; // esi
  int v44; // eax
  int v45; // edi
  int v46; // eax
  __int16 v47; // cx
  int v48; // esi
  unsigned int v49; // edx
  __int16 v50; // ax
  int v51; // [esp-4h] [ebp-8Ch]
  int v52; // [esp-4h] [ebp-8Ch]
  char *v53; // [esp+Ch] [ebp-7Ch]
  __int16 v54; // [esp+14h] [ebp-74h]
  __int16 v55; // [esp+18h] [ebp-70h]
  int v56; // [esp+1Ch] [ebp-6Ch]
  int v57; // [esp+20h] [ebp-68h]
  int v58; // [esp+20h] [ebp-68h]
  int v59; // [esp+24h] [ebp-64h]
  int v60; // [esp+24h] [ebp-64h]
  int v61; // [esp+28h] [ebp-60h]
  unsigned __int16 *v62; // [esp+28h] [ebp-60h]
  int v63; // [esp+2Ch] [ebp-5Ch]
  unsigned __int16 *v64; // [esp+2Ch] [ebp-5Ch]
  int v65; // [esp+30h] [ebp-58h]
  int i; // [esp+30h] [ebp-58h]
  char *v67; // [esp+34h] [ebp-54h]
  int v68; // [esp+34h] [ebp-54h]
  int v69; // [esp+38h] [ebp-50h]
  int v70; // [esp+38h] [ebp-50h]
  unsigned int v71; // [esp+3Ch] [ebp-4Ch]
  unsigned int v72; // [esp+3Ch] [ebp-4Ch]
  __int64 v73; // [esp+40h] [ebp-48h] BYREF
  int v74; // [esp+48h] [ebp-40h]
  _DWORD v75[7]; // [esp+4Ch] [ebp-3Ch] BYREF
  signed __int8 v76[23]; // [esp+68h] [ebp-20h] BYREF
  char v77; // [esp+7Fh] [ebp-9h]

  v8 = 0;
  v9 = v76;
  v54 = 0;
  v57 = 1;
  v71 = 0;
  v65 = 0;
  v63 = 0;
  v61 = 0;
  v59 = 0;
  v69 = 0;
  v56 = 0;
  if ( !a8 )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 0;
  }
  v11 = a3;
  v67 = a3;
  while ( 1 )
  {
    v12 = *v11;
    if ( *v11 != 32 && v12 != 9 && v12 != 10 && v12 != 13 )
      break;
    ++v11;
  }
  while ( 2 )
  {
    v13 = *v11++;
    switch ( v8 )
    {
      case 0:
        if ( (unsigned __int8)(v13 - 49) <= 8u )
          goto LABEL_11;
        if ( v13 == ***(_BYTE ***)(*(_DWORD *)a8 + 188) )
          goto LABEL_14;
        v14 = v13 - 43;
        if ( !v14 )
        {
          v54 = 0;
          v8 = 2;
          continue;
        }
        v15 = v14 - 2;
        if ( !v15 )
        {
          v8 = 2;
          v54 = 0x8000;
          continue;
        }
        if ( v15 != 3 )
          goto LABEL_75;
        goto LABEL_19;
      case 1:
        v65 = 1;
        if ( (unsigned __int8)(v13 - 49) <= 8u )
          goto LABEL_11;
        if ( v13 == ***(_BYTE ***)(*(_DWORD *)a8 + 188) )
          goto LABEL_24;
        if ( v13 == 43 || v13 == 45 )
          goto LABEL_33;
        if ( v13 == 48 )
          goto LABEL_19;
LABEL_28:
        if ( v13 <= 67 || v13 > 69 && (v13 <= 99 || v13 > 101) )
          goto LABEL_75;
        v52 = 6;
        goto LABEL_15;
      case 2:
        if ( (unsigned __int8)(v13 - 49) <= 8u )
        {
LABEL_11:
          v51 = 3;
LABEL_12:
          v8 = v51;
          --v11;
        }
        else
        {
          if ( v13 == ***(_BYTE ***)(*(_DWORD *)a8 + 188) )
          {
LABEL_14:
            v52 = 5;
            goto LABEL_15;
          }
          if ( v13 != 48 )
          {
LABEL_37:
            v16 = v67;
            goto LABEL_82;
          }
LABEL_19:
          v8 = 1;
        }
        continue;
      case 3:
        v65 = 1;
        while ( v13 >= 48 && v13 <= 57 )
        {
          if ( v71 >= 0x19 )
          {
            ++v69;
          }
          else
          {
            ++v71;
            *v9++ = v13 - 48;
          }
          v13 = *v11++;
        }
        if ( v13 != ***(_BYTE ***)(*(_DWORD *)a8 + 188) )
          goto LABEL_46;
LABEL_24:
        v52 = 4;
        goto LABEL_15;
      case 4:
        v65 = 1;
        v63 = 1;
        if ( !v71 )
        {
          while ( v13 == 48 )
          {
            --v69;
            v13 = *v11++;
          }
        }
        while ( v13 >= 48 && v13 <= 57 )
        {
          if ( v71 < 0x19 )
          {
            ++v71;
            *v9++ = v13 - 48;
            --v69;
          }
          v13 = *v11++;
        }
LABEL_46:
        if ( v13 != 43 && v13 != 45 )
          goto LABEL_28;
LABEL_33:
        --v11;
        v52 = 11;
        goto LABEL_15;
      case 5:
        v63 = 1;
        if ( (unsigned __int8)(v13 - 48) > 9u )
          goto LABEL_37;
        v51 = 4;
        goto LABEL_12;
      case 6:
        v67 = v11 - 2;
        if ( (unsigned __int8)(v13 - 49) <= 8u )
          goto LABEL_63;
        v17 = v13 - 43;
        if ( !v17 )
          goto LABEL_70;
        v18 = v17 - 2;
        if ( !v18 )
          goto LABEL_69;
        v19 = v18 == 3;
LABEL_67:
        if ( !v19 )
          goto LABEL_37;
        v52 = 8;
        goto LABEL_15;
      case 7:
        if ( (unsigned __int8)(v13 - 49) <= 8u )
          goto LABEL_63;
        v19 = v13 == 48;
        goto LABEL_67;
      case 8:
        v61 = 1;
        while ( v13 == 48 )
          v13 = *v11++;
        if ( (unsigned __int8)(v13 - 49) > 8u )
          goto LABEL_75;
LABEL_63:
        v51 = 9;
        goto LABEL_12;
      case 9:
        v61 = 1;
        v21 = 0;
        while ( 2 )
        {
          if ( v13 >= 48 && v13 <= 57 )
          {
            v21 = 10 * v21 + v13 - 48;
            if ( v21 <= 5200 )
            {
              v13 = *v11++;
              continue;
            }
            v21 = 5201;
          }
          break;
        }
        v59 = v21;
        while ( v13 >= 48 && v13 <= 57 )
          v13 = *v11++;
LABEL_75:
        v16 = v11 - 1;
        goto LABEL_82;
      case 11:
        if ( a7 )
        {
          v20 = v13 - 43;
          v67 = v11 - 1;
          if ( v20 )
          {
            if ( v20 != 2 )
            {
              v16 = v11 - 1;
              goto LABEL_82;
            }
LABEL_69:
            v57 = -1;
            v8 = 7;
          }
          else
          {
LABEL_70:
            v52 = 7;
LABEL_15:
            v8 = v52;
          }
          continue;
        }
        v16 = v11 - 1;
LABEL_82:
        *a2 = v16;
        if ( !v65 )
        {
          v56 = 4;
LABEL_177:
          v47 = 0;
          v50 = 0;
          v49 = 0;
          v48 = 0;
          goto LABEL_178;
        }
        if ( v71 > 0x18 )
        {
          if ( v77 >= 5 )
            ++v77;
          --v9;
          ++v69;
          v71 = 24;
        }
        if ( !v71 )
          goto LABEL_177;
        while ( !*--v9 )
        {
          --v71;
          ++v69;
        }
        __mtold12(v76, v71, v75);
        v22 = v59;
        if ( v57 < 0 )
          v22 = -v59;
        v23 = v69 + v22;
        if ( !v61 )
          v23 += a5;
        if ( !v63 )
          v23 -= a6;
        if ( v23 > 5200 )
        {
          v48 = 0;
          v50 = 0x7FFF;
          v49 = 0x80000000;
          v47 = 0;
          v56 = 2;
          goto LABEL_178;
        }
        if ( v23 < -5200 )
        {
          v56 = 1;
          goto LABEL_177;
        }
        v24 = (char *)&unk_6660F8 - 96;
        v68 = v23;
        if ( v23 )
        {
          if ( v23 < 0 )
          {
            v68 = -v23;
            v24 = (char *)&unk_666258 - 96;
          }
          if ( !a4 )
            LOWORD(v75[0]) = 0;
          if ( v68 )
          {
            while ( 1 )
            {
              v25 = v68;
              v68 >>= 3;
              v26 = v24 + 84;
              v27 = v25 & 7;
              v53 = v26;
              if ( !v27 )
                goto LABEL_172;
              v28 = &v26[12 * v27];
              if ( *(_WORD *)v28 >= 0x8000u )
              {
                v73 = *(_QWORD *)v28;
                v74 = *((_DWORD *)v28 + 2);
                --*(_DWORD *)((char *)&v73 + 2);
                v28 = (char *)&v73;
              }
              v29 = *((_WORD *)v28 + 5);
              v70 = 0;
              memset(&v75[4], 0, 12);
              v30 = HIWORD(v75[2]) ^ v29;
              v31 = v29 & 0x7FFF;
              v32 = v30 & 0x8000;
              v55 = v32;
              v33 = v31 + (HIWORD(v75[2]) & 0x7FFF);
              if ( (HIWORD(v75[2]) & 0x7FFF) == 0x7FFF || v31 >= 0x7FFFu || v33 > 0xBFFDu )
                break;
              if ( v33 <= 0x3FBFu )
              {
                v34 = 0;
                v75[1] = 0;
                v75[0] = 0;
LABEL_171:
                v75[2] = v34;
                goto LABEL_172;
              }
              if ( (v75[2] & 0x7FFF0000) != 0 || (++v33, (v75[2] & 0x7FFFFFFF) != 0) || v75[1] || v75[0] )
              {
                if ( v31 || (++v33, (*((_DWORD *)v28 + 2) & 0x7FFFFFFF) != 0) || *((_DWORD *)v28 + 1) || *(_DWORD *)v28 )
                {
                  v58 = 0;
                  v35 = &v75[5];
                  for ( i = 5; i > 0; --i )
                  {
                    v60 = i;
                    v64 = (unsigned __int16 *)v75 + v58;
                    v62 = (unsigned __int16 *)(v28 + 8);
                    do
                    {
                      v72 = 0;
                      v36 = *v64 * *v62;
                      v37 = *((_DWORD *)v35 - 1);
                      v38 = v37 + v36;
                      if ( v37 + v36 < v37 || v38 < v36 )
                        v72 = 1;
                      *((_DWORD *)v35 - 1) = v38;
                      if ( v72 )
                        ++*v35;
                      ++v64;
                      --v62;
                      --v60;
                    }
                    while ( v60 > 0 );
                    ++v35;
                    ++v58;
                  }
                  v39 = v33 - 16382;
                  if ( v39 <= 0 )
                    goto LABEL_181;
                  do
                  {
                    if ( v75[6] < 0 )
                      break;
                    v40 = v75[4];
                    v75[4] *= 2;
                    v41 = (v40 >> 31) | (2 * v75[5]);
                    v42 = *(__int64 *)&v75[5] >> 31;
                    --v39;
                    v75[5] = v41;
                    v75[6] = v42;
                  }
                  while ( v39 > 0 );
                  if ( v39 <= 0 )
                  {
LABEL_181:
                    if ( --v39 < 0 )
                    {
                      v43 = (unsigned __int16)-v39;
                      v39 = 0;
                      do
                      {
                        if ( (v75[4] & 1) != 0 )
                          ++v70;
                        v44 = v75[6];
                        v75[6] >>= 1;
                        v45 = (v44 << 31) | (v75[5] >> 1);
                        v46 = *(__int64 *)&v75[4] >> 1;
                        --v43;
                        v75[5] = v45;
                        v75[4] = v46;
                      }
                      while ( v43 );
                      if ( v70 )
                        LOWORD(v75[4]) |= 1u;
                    }
                  }
                  if ( LOWORD(v75[4]) > 0x8000u || (v75[4] & 0x1FFFF) == 0x18000 )
                  {
                    if ( *(_DWORD *)((char *)&v75[4] + 2) == -1 )
                    {
                      *(_DWORD *)((char *)&v75[4] + 2) = 0;
                      if ( *(_DWORD *)((char *)&v75[5] + 2) == -1 )
                      {
                        *(_DWORD *)((char *)&v75[5] + 2) = 0;
                        if ( HIWORD(v75[6]) == 0xFFFF )
                        {
                          HIWORD(v75[6]) = 0x8000;
                          ++v39;
                        }
                        else
                        {
                          ++HIWORD(v75[6]);
                        }
                      }
                      else
                      {
                        ++*(_DWORD *)((char *)&v75[5] + 2);
                      }
                    }
                    else
                    {
                      ++*(_DWORD *)((char *)&v75[4] + 2);
                    }
                  }
                  if ( (unsigned __int16)v39 < 0x7FFFu )
                  {
                    LOWORD(v75[0]) = HIWORD(v75[4]);
                    *(_QWORD *)((char *)v75 + 2) = *(_QWORD *)&v75[5];
                    HIWORD(v75[2]) = v55 | v39;
                  }
                  else
                  {
                    v75[1] = 0;
                    v75[0] = 0;
                    v75[2] = v55 == 0 ? 2147450880 : -32768;
                  }
                }
                else
                {
                  memset(v75, 0, 12);
                }
              }
              else
              {
                HIWORD(v75[2]) = 0;
              }
LABEL_172:
              if ( !v68 )
                goto LABEL_173;
              v24 = v53;
            }
            v75[1] = 0;
            v34 = v32 == 0 ? 2147450880 : -32768;
            v75[0] = 0;
            goto LABEL_171;
          }
        }
LABEL_173:
        v47 = v75[0];
        v48 = *(_DWORD *)((char *)v75 + 2);
        v49 = *(_DWORD *)((char *)&v75[1] + 2);
        v50 = HIWORD(v75[2]);
LABEL_178:
        *(_WORD *)a1 = v47;
        *((_WORD *)a1 + 5) = v54 | v50;
        *(_DWORD *)(a1 + 2) = v48;
        *(_DWORD *)(a1 + 6) = v49;
        return v56;
    }
  }
}

