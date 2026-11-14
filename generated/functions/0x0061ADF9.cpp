// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061ADF9 __input_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(FILE*,const format*,optional localeInfo*,raw
// byte cursor to varargs), int assignment count or -1. Fourth argument is by-value va cursor; destination pointers consume four-byte slots locally, no caller cursor writeback.
// Validate format FIRST, then FILE; NULL ->errno22,invalid_parameter5zeros,-1. FILE flag40 bypasses descriptor validation; otherwise fileno, -1/-2 use dummy665C30, others
// global2021E40[fd SAR5]+64*(fd&31), no own fd range guard. Require descriptor BYTE+36 low7zero AND highbit0. LocaleUpdate only AFTER these guards; normal postconstruction exits
// conditionally clear PTD+112bit2, no SEH/finally. All own returns check security cookie. No destination NULL/capacity guard, secure-size args, own stream lock, errno reset, integer
// range check or transactional rollback. Format whitespace uses GLOBAL isspace, decrements internal read counter before whiteout, then un_inc(returned,FILE) ignoring result; skip
// format whitespace run. This path does not store EOF into currentInput. Ordinary literals and %% increment counter/read/compare; mismatch ungets without counter decrement. GLOBAL
// isleadbyte matched literal reads second byte; mismatch attempts to unget second then first, ignoring results; successful pair decrements counter once. Thus counter is not a simple
// raw-byte total. Empty format returns0. After conversion/literal, stored currentInput EOF permits continuation ONLY when immediately next format is exact %n, not modified n. Percent
// parser initializes size BYTE1, wide modifier BYTE0, suppression BYTE0, width DWORD0/digit-count0 and int64 flag0. GLOBAL isdigit drives decimal width accumulation modulo32.
// Repeated * increments suppression BYTE; F/N ignored legacy modifiers, L increments size only, h decrements size and wide BYTE, single l increments both, w increments wide only.
// ll/I64 increment int64 flag and zero64 accumulator; I32 consumes suffix WITHOUT clearing prior64 flag. Bare I ignored only before d/i/o/x/X (u excluded); otherwise I becomes
// normalized i conversion. Duplicate modifiers/counter overflow/incomplete format unvalidated. Unsuppressed destination pointer fetched and cursor advanced BEFORE conversion validity
// is known. Default wide modifier: C/S ->+1, others ->-1; type normalized originalByte OR20h. n bypasses input read; c/[ read raw byte, other types use whiteout. Initial EOF fails.
// Explicit width0 attempts unget currentInput and exits, even n with stale currentInput. Unknown conversion compares original format byte against currentInput after whitespace skip.
// Match decrements successful-conversion BYTE, rewinds local va cursor if unsuppressed, then common increment cancels: literal match, no assignment. Still fetched a destination slot
// first. Mismatch ungets and exits; no invalid-format handler. OR20 admits uppercase D/U/O/P/E/G; F/N consumed as modifiers; a/A is unknown, not hex float. Strings: c default width1,
// no terminator; s stops internally only at ASCII9..13/space; [ uses 256-bit bitmap XOR inversion. Leading whitespace skipped only for s. First read byte ungot with counter
// decrement, then width-postdecrement/read loop; rejected byte or EOF decrements counter and attempts unget. Any positive progress succeeds, including partial c width at EOF.
// Unsuppressed assignment count increments once; s/[ append byte/WORD NUL. Suppression advances fake progress by1 and bypasses wide conversion/DBCS second read. Assigned narrow
// stores byte. Wide (signed modifier>0) tests GLOBAL isleadbyte; if lead, reads second byte without EOF/trail/width check. Only first1/2 bytes of source scratch initialized.
// Initialize output WCHAR to '?', call mbtowc_l with selected locale maximum-byte count, IGNORE status, store output WORD. Width counts loop iterations, not DBCS bytes; supplied
// conversion length may exceed initialized scratch bytes. Scanset: optional ^ inverts, initial ] included literal, zero32-byte bitmap. Hyphen range with previous byte and next!=]
// normalizes reversed endpoints ascending. Inclusive span stored BYTE; span256 wraps0 yet unconditional bitmap do-loop still runs, potentially writing outside bitmap until counter
// wrap/fault for malformed NUL endpoint. Parser scans until ] WITHOUT checking NUL; postloop NUL test unreachable since AL==]. Unterminated scanset reads beyond format terminator.
// Membership checks first byte only, even for wide destination. Integers d/u/o/p accept optional sign; p forces size BYTE1 but leaves int64 flag and does NOT use optional0x probing
// (generic hex parses0 then leaves x). i/x prefix flow reads leading-zero lookahead BEFORE accounting width; x prefix consumes next read then width-=2, i without x becomes octal and
// width--. Prefix/sign paths can consume beyond specified width; failed prefix not fully rolled back. GLOBAL digit/hex classifiers on lowBYTE, octal rejects ASCII>=8, hextodec then
// subtract48. Accumulators wrap32/64; 64 multiply via allmul; no overflow errno. Optional minus negates modulo32/64 including u/p. Accepted digit decrements nonzero width and exits
// at0 without extra read; rejected byte counter--/unget. Require digit flag. Unsuppressed count++; int64 flag stores8, otherwise size BYTE0 stores2 and all other sizes store4 (hh
// wraps toFF and stores4). Dead compare normalized type with uppercase F cannot be reached. n always enabled, no printf permission getter, no assignment-count increment. Normal store
// uses internal read counter, WORD iff size0 else DWORD. I64n/lln instead copies64 accumulator zeroed during modifier parsing: writes ZERO64, not extended read counter. Suppressed n
// stores nothing but still participates in successful-conversion BYTE. Float e/f/g (E/G via OR20) builds reusable scratch even suppressed: initial352-byte stack
// allocation/capacity350, growth check AFTER every appended byte; helper grows only used==capacity. Initial allocation failure publishes NULL with heapFlag0; later realloc failure
// preserves existing heap. Failure exits normal cleanup. Optional minus appended, plus omitted; sign decrements width and reads again without early limit test. Absent width becomes
// -1. GLOBAL isdigit mantissa, only FIRST byte of selected locale decimal point; accept e/E after at least one mantissa digit, normalize e, optional sign, but no exponent-digit
// requirement. Raw width postdecrement can leave -1 when old0 and permit later point/exponent stages; no strict bound guarantee. Unget only one final lookahead/counter--, consumed
// sign/point/exponent prefix retained. No explicit inf/nan/hex float grammar. Require at least mantissa digit. Unsuppressed count++ BEFORE NUL/callback; decode LIVE66507C, call four
// cdecl slots {signed sizeBYTE-1,destination,buffer,&selectedLocaleInfo}, ignore status/no decoded NULL check. Verified ordinary fassign_l interprets mode0 float32, any nonzero
// double64: default float, l/L double, h also double due -1; int64 flag irrelevant. Suppressed field skips assignment,NUL,callback but still builds/grows buffer. Reuse allocation
// across fields, free only heapFlag==1 at normal exit. Successful-conversion evidence is BYTE, incremented on common success and wraps256; assignments are DWORD. Normal result is
// assignmentCount except stored currentInput==-1 AND assignments0 AND successBYTE0 ->-1. Suppressed/n successes affect EOF result; BYTE wrap can erase that evidence. Whitespace-only
// EOF can return0 because currentInput was not updated. Retain consumed input and any partial destination writes on failure; own cleanup frees scratch then releases locale pin,
// checks cookie.
int __cdecl _input_l(FILE *Stream, const char *a2, struct localeinfo_struct *a3, char *a4)
{
  const char *v4; // edi
  int result; // eax
  int v6; // eax
  _BYTE *v7; // ecx
  char *v8; // eax
  unsigned __int8 v9; // al
  FILE *v10; // esi
  int v11; // eax
  int v12; // ebx
  char v13; // cl
  const char *v14; // eax
  _WORD *v15; // esi
  char v16; // bl
  char v17; // al
  int v18; // eax
  int v19; // eax
  int v20; // edi
  int v21; // ebx
  int i; // eax
  int j; // eax
  int k; // eax
  void (__cdecl *v31)(int, _WORD *, void *, __crt_locale_pointers *); // eax
  FILE *v32; // edi
  int v34; // eax
  unsigned __int8 *v35; // edi
  unsigned __int8 *v36; // esi
  unsigned __int8 v37; // dl
  unsigned __int8 v38; // cl
  unsigned __int8 v39; // al
  unsigned int v40; // edi
  int v41; // edx
  unsigned __int8 v42; // al
  int v43; // eax
  __int64 v44; // kr00_8
  unsigned int v45; // edi
  unsigned int v46; // esi
  int v47; // edi
  int v48; // ebx
  int v49; // eax
  int v50; // eax
  int v51; // ecx
  int v52; // [esp-14h] [ebp-218h]
  _WORD *v53; // [esp-10h] [ebp-214h]
  void *v54; // [esp-Ch] [ebp-210h]
  char *v55; // [esp+8h] [ebp-1FCh]
  __crt_locale_pointers Locale; // [esp+Ch] [ebp-1F8h] BYREF
  int v57; // [esp+14h] [ebp-1F0h]
  char v58; // [esp+18h] [ebp-1ECh]
  wchar_t DstCh[2]; // [esp+1Ch] [ebp-1E8h] BYREF
  char *v60; // [esp+20h] [ebp-1E4h]
  char SrcCh[4]; // [esp+24h] [ebp-1E0h] BYREF
  size_t v62; // [esp+28h] [ebp-1DCh] BYREF
  int v63; // [esp+2Ch] [ebp-1D8h]
  unsigned __int8 v64; // [esp+33h] [ebp-1D1h]
  int v65; // [esp+34h] [ebp-1D0h] BYREF
  unsigned __int64 v66; // [esp+38h] [ebp-1CCh]
  int v67; // [esp+40h] [ebp-1C4h]
  _WORD *v68; // [esp+44h] [ebp-1C0h]
  _WORD *v69; // [esp+48h] [ebp-1BCh]
  const char *v70; // [esp+4Ch] [ebp-1B8h]
  int v71; // [esp+50h] [ebp-1B4h]
  char v72; // [esp+57h] [ebp-1ADh]
  void *Block; // [esp+58h] [ebp-1ACh] BYREF
  int v74; // [esp+5Ch] [ebp-1A8h]
  int v75; // [esp+60h] [ebp-1A4h]
  char v76; // [esp+64h] [ebp-1A0h]
  char v77; // [esp+65h] [ebp-19Fh]
  char v78; // [esp+66h] [ebp-19Eh]
  char v79; // [esp+67h] [ebp-19Dh]
  void *stream; // [esp+68h] [ebp-19Ch]
  char v81; // [esp+6Eh] [ebp-196h]
  char v82; // [esp+6Fh] [ebp-195h]
  int v83; // [esp+70h] [ebp-194h]
  char v84; // [esp+77h] [ebp-18Dh]
  int v85; // [esp+78h] [ebp-18Ch] BYREF
  int v86; // [esp+7Ch] [ebp-188h]
  _BYTE Src[352]; // [esp+80h] [ebp-184h] BYREF
  _BYTE v88[32]; // [esp+1E0h] [ebp-24h] BYREF

  v4 = a2;
  v60 = a4;
  stream = Stream;
  Block = Src;
  v62 = 350;
  v65 = 0;
  *(_DWORD *)DstCh = 0;
  v86 = 0;
  if ( !a2 || !Stream )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  if ( (Stream->_flag & 0x40) == 0 )
  {
    v6 = _fileno(Stream);
    if ( v6 == -1 || v6 == -2 )
      v7 = &unk_665C30;
    else
      v7 = (_BYTE *)(unk_2021E40[v6 >> 5] + ((v6 & 0x1F) << 6));
    if ( (v7[36] & 0x7F) != 0
      || (v6 == -1 || v6 == -2 ? (v8 = (char *)&unk_665C30) : (v8 = (char *)(unk_2021E40[v6 >> 5] + ((v6 & 0x1F) << 6))),
          v8[36] < 0) )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return -1;
    }
  }
  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&Locale, a3);
  v9 = *a2;
  v79 = 0;
  v85 = 0;
  v67 = 0;
  if ( !v9 )
    goto LABEL_273;
  while ( 1 )
  {
    v10 = (FILE *)stream;
    if ( isspace(v9) )
    {
      --v85;
      v11 = _whiteout(&v85, v10);
      _un_inc(v11, v10);
      do
        ++v4;
      while ( isspace(*(unsigned __int8 *)v4) );
      goto LABEL_260;
    }
    if ( *v4 == 37 )
      break;
LABEL_252:
    ++v85;
    v48 = _inc(v10);
    v49 = *(unsigned __int8 *)v4++;
    v86 = v48;
    v70 = v4;
    if ( v49 != v48 )
    {
      _un_inc(v48, v10);
      goto $error_return$29126;
    }
    if ( isleadbyte((unsigned __int8)v48) )
    {
      ++v85;
      v50 = _inc(v10);
      v51 = *(unsigned __int8 *)v4++;
      v70 = v4;
      if ( v51 != v50 )
      {
        _un_inc(v50, v10);
        _un_inc(v48, v10);
        goto $error_return$29126;
      }
      --v85;
    }
LABEL_256:
    if ( v86 == -1 )
    {
      if ( *v4 != 37 || v70[1] != 110 )
        goto $error_return$29126;
      v4 = v70;
    }
LABEL_260:
    v9 = *v4;
    if ( !*v4 )
      goto $error_return$29126;
  }
  if ( v4[1] == 37 )
  {
    ++v4;
    goto LABEL_252;
  }
  v68 = nullptr;
  v64 = 0;
  v74 = 0;
  v71 = 0;
  v83 = 0;
  v77 = 0;
  v76 = 0;
  v81 = 0;
  v72 = 0;
  v78 = 0;
  v84 = 0;
  v82 = 1;
  v63 = 0;
  do
  {
    v12 = *(unsigned __int8 *)++v4;
    if ( isdigit((unsigned __int8)v12) )
    {
      ++v71;
      v83 = 10 * v83 + v12 - 48;
      continue;
    }
    if ( v12 > 78 )
    {
      if ( v12 == 104 )
      {
        --v82;
        --v84;
      }
      else
      {
        if ( v12 == 108 )
        {
          v14 = v4 + 1;
          if ( v4[1] == 108 )
            goto LABEL_35;
          ++v82;
        }
        else if ( v12 != 119 )
        {
          goto $DEFAULT_LABEL$29099;
        }
        ++v84;
      }
    }
    else
    {
      switch ( v12 )
      {
        case 'N':
          continue;
        case '*':
          ++v81;
          continue;
        case 'F':
          continue;
      }
      if ( v12 != 73 )
      {
        if ( v12 == 76 )
        {
          ++v82;
          continue;
        }
$DEFAULT_LABEL$29099:
        ++v72;
        continue;
      }
      v13 = v4[1];
      if ( v13 == 54 )
      {
        v14 = v4 + 2;
        if ( v4[2] == 52 )
        {
LABEL_35:
          ++v63;
          v4 = v14;
          v66 = 0;
          continue;
        }
      }
      if ( v13 == 51 && v4[2] == 50 )
      {
        v4 += 2;
        continue;
      }
      if ( v13 != 100 && v13 != 105 && v13 != 111 && v13 != 120 && v13 != 88 )
        goto $DEFAULT_LABEL$29099;
    }
  }
  while ( !v72 );
  v70 = v4;
  if ( v81 )
  {
    v15 = nullptr;
  }
  else
  {
    v15 = *(_WORD **)v60;
    v55 = v60;
    v60 += 4;
  }
  v16 = 0;
  v69 = v15;
  if ( !v84 )
  {
    v17 = *v4;
    if ( *v4 == 83 || (v84 = -1, v17 == 67) )
      v84 = 1;
  }
  v18 = *(unsigned __int8 *)v4 | 0x20;
  v75 = v18;
  if ( v18 == 110 )
  {
LABEL_69:
    if ( v71 && !v83 )
      goto LABEL_262;
    if ( v75 > 111 )
    {
      if ( v75 == 112 )
      {
        v82 = 1;
        goto LABEL_200;
      }
      if ( v75 != 115 )
      {
        if ( v75 == 117 )
          goto LABEL_200;
        if ( v75 == 120 )
          goto LABEL_82;
        if ( v75 != 123 )
          goto LABEL_148;
        if ( v84 > 0 )
          v78 = 1;
        v35 = (unsigned __int8 *)(v4 + 1);
        v36 = v35;
        if ( *v35 == 94 )
        {
          v36 = v35 + 1;
          v77 = -1;
        }
        memset(v88, 0, sizeof(v88));
        if ( *v36 == 93 )
        {
          v37 = 93;
          ++v36;
          v88[11] = 32;
        }
        else
        {
          v37 = v64;
        }
        while ( 1 )
        {
          v42 = *v36;
          if ( *v36 == 93 )
            break;
          ++v36;
          if ( v42 == 45 && v37 && (v38 = *v36, *v36 != 93) )
          {
            ++v36;
            if ( v37 >= v38 )
            {
              v39 = v37;
              v37 = v38;
            }
            else
            {
              v39 = v38;
            }
            if ( v37 <= v39 )
            {
              v40 = v37;
              v41 = (unsigned __int8)(v39 - v37 + 1);
              do
              {
                v88[v40 >> 3] |= 1 << (v40 & 7);
                ++v40;
                --v41;
              }
              while ( v41 );
            }
            v37 = 0;
          }
          else
          {
            v37 = v42;
            v88[v42 >> 3] |= 1 << (v42 & 7);
          }
        }
        v70 = (const char *)v36;
        v15 = v69;
$scanit$29137:
        v32 = (FILE *)stream;
        --v85;
        v68 = v15;
        _un_inc(v86, (FILE *)stream);
        while ( 1 )
        {
          if ( v71 )
          {
            if ( !v83-- )
              break;
          }
          ++v85;
          v34 = _inc(v32);
          v86 = v34;
          if ( v34 == -1 )
            goto LABEL_192;
          if ( v75 != 99 )
          {
            if ( v75 != 115 )
              goto LABEL_137;
            if ( v34 >= 9 && v34 <= 13 )
            {
LABEL_192:
              --v85;
              _un_inc(v34, v32);
              break;
            }
            if ( v34 == 32 )
            {
LABEL_137:
              if ( v75 != 123 || ((1 << (v34 & 7)) & (v77 ^ (char)v88[v34 >> 3])) == 0 )
                goto LABEL_192;
            }
          }
          if ( v81 )
          {
            v68 = (_WORD *)((char *)v68 + 1);
          }
          else
          {
            if ( v78 )
            {
              SrcCh[0] = v34;
              if ( isleadbyte((unsigned __int8)v34) )
              {
                ++v85;
                SrcCh[1] = _inc(v32);
              }
              wcscpy(DstCh, L"?");
              _mbtowc_l(DstCh, SrcCh, *((_DWORD *)Locale.locinfo + 43), &Locale);
              *v15++ = DstCh[0];
            }
            else
            {
              *(_BYTE *)v15 = v34;
              v15 = (_WORD *)((char *)v15 + 1);
            }
            v69 = v15;
          }
        }
        if ( v68 == v15 )
          goto $error_return$29126;
        if ( !v81 )
        {
          ++v67;
          if ( v75 != 99 )
          {
            if ( v78 )
              *v69 = 0;
            else
              *(_BYTE *)v69 = 0;
          }
        }
        goto LABEL_250;
      }
    }
    else
    {
      if ( v75 == 111 )
        goto LABEL_200;
      if ( v75 != 99 )
      {
        if ( v75 != 100 )
        {
          if ( v75 > 100 )
          {
            if ( v75 > 103 )
            {
              if ( v75 != 105 )
              {
                if ( v75 == 110 )
                {
                  v20 = v85;
                  if ( v81 )
                    goto LABEL_250;
$assign_num$29279:
                  if ( v63 )
                  {
                    *(_QWORD *)v15 = v66;
                  }
                  else if ( v82 )
                  {
                    *(_DWORD *)v15 = v20;
                  }
                  else
                  {
                    *v15 = v20;
                  }
                  goto LABEL_250;
                }
                goto LABEL_148;
              }
              v75 = 100;
LABEL_82:
              if ( v86 == 45 )
              {
                v76 = 1;
              }
              else if ( v86 != 43 )
              {
                goto LABEL_176;
              }
              if ( --v83 || !v71 )
              {
                ++v85;
                v86 = _inc(stream);
              }
              else
              {
                v16 = 1;
              }
LABEL_176:
              if ( v86 == 48 )
              {
                ++v85;
                v43 = _inc(stream);
                v86 = v43;
                if ( (_BYTE)v43 == 120 || (_BYTE)v43 == 88 )
                {
                  ++v85;
                  v86 = _inc(stream);
                  if ( v71 )
                  {
                    v83 -= 2;
                    if ( v83 < 1 )
                      ++v16;
                  }
                  v75 = 120;
                }
                else
                {
                  v74 = 1;
                  if ( v75 == 120 )
                  {
                    --v85;
                    _un_inc(v43, (FILE *)stream);
                    v86 = 48;
                  }
                  else
                  {
                    if ( v71 )
                    {
                      if ( !--v83 )
                        ++v16;
                    }
                    v75 = 111;
                  }
                }
              }
              goto $getnum$29217;
            }
            v21 = 0;
            if ( v86 == 45 )
            {
              *(_BYTE *)Block = 45;
              v21 = 1;
            }
            else if ( v86 != 43 )
            {
LABEL_88:
              if ( !v71 )
                v83 = -1;
              for ( i = (unsigned __int8)v86; isdigit(i); i = (unsigned __int8)v86 )
              {
                if ( !v83-- )
                  break;
                ++v74;
                *((_BYTE *)Block + v21) = v86;
                if ( !__check_float_string(&Block, &v62, ++v21, Src, &v65) )
                  goto $error_return$29126;
                ++v85;
                v86 = _inc(stream);
              }
              v77 = ***((_BYTE ***)Locale.locinfo + 47);
              if ( v77 == (_BYTE)v86 )
              {
                if ( v83-- )
                {
                  ++v85;
                  v86 = _inc(stream);
                  *((_BYTE *)Block + v21) = v77;
                  if ( !__check_float_string(&Block, &v62, ++v21, Src, &v65) )
                    goto $error_return$29126;
                  for ( j = (unsigned __int8)v86; isdigit(j); j = (unsigned __int8)v86 )
                  {
                    if ( !v83-- )
                      break;
                    ++v74;
                    *((_BYTE *)Block + v21) = v86;
                    if ( !__check_float_string(&Block, &v62, ++v21, Src, &v65) )
                      goto $error_return$29126;
                    ++v85;
                    v86 = _inc(stream);
                  }
                }
              }
              if ( !v74 || v86 != 101 && v86 != 69 )
                goto LABEL_120;
              if ( !v83-- )
                goto LABEL_120;
              *((_BYTE *)Block + v21) = 101;
              if ( !__check_float_string(&Block, &v62, ++v21, Src, &v65) )
                goto $error_return$29126;
              ++v85;
              v86 = _inc(stream);
              if ( v86 == 45 )
              {
                *((_BYTE *)Block + v21) = 45;
                if ( !__check_float_string(&Block, &v62, ++v21, Src, &v65) )
                  goto $error_return$29126;
              }
              else if ( v86 != 43 )
              {
                goto LABEL_115;
              }
              if ( v83-- )
              {
                ++v85;
                v86 = _inc(stream);
              }
              else
              {
                v83 = 0;
              }
LABEL_115:
              for ( k = (unsigned __int8)v86; isdigit(k); k = (unsigned __int8)v86 )
              {
                if ( !v83-- )
                  break;
                ++v74;
                *((_BYTE *)Block + v21) = v86;
                if ( !__check_float_string(&Block, &v62, ++v21, Src, &v65) )
                  goto $error_return$29126;
                ++v85;
                v86 = _inc(stream);
              }
LABEL_120:
              --v85;
              _un_inc(v86, (FILE *)stream);
              if ( !v74 )
                goto $error_return$29126;
              if ( !v81 )
              {
                ++v67;
                v54 = Block;
                v53 = v69;
                *((_BYTE *)Block + v21) = 0;
                v52 = v82 - 1;
                v31 = (void (__cdecl *)(int, _WORD *, void *, __crt_locale_pointers *))_decode_pointer(off_66507C[0]);
                v31(v52, v53, v54, &Locale);
              }
              goto LABEL_250;
            }
            --v83;
            ++v85;
            v86 = _inc(stream);
            goto LABEL_88;
          }
LABEL_148:
          if ( *(unsigned __int8 *)v4 == v86 )
          {
            --v79;
            if ( !v81 )
              v60 = v55;
            goto LABEL_250;
          }
LABEL_262:
          _un_inc(v86, (FILE *)stream);
          goto $error_return$29126;
        }
LABEL_200:
        if ( v86 == 45 )
        {
          v76 = 1;
        }
        else if ( v86 != 43 )
        {
          goto $getnum$29217;
        }
        if ( --v83 || !v71 )
        {
          ++v85;
          v86 = _inc(stream);
        }
        else
        {
          v16 = 1;
        }
$getnum$29217:
        if ( v63 )
        {
          if ( !v16 )
          {
            while ( 1 )
            {
              if ( v75 == 120 || v75 == 112 )
              {
                if ( !isxdigit((unsigned __int8)v86) )
                {
LABEL_221:
                  --v85;
                  _un_inc(v86, (FILE *)stream);
                  break;
                }
                v45 = v66 >> 28;
                v46 = 16 * v66;
                v86 = _hextodec(v86);
                v44 = __PAIR64__(v45, v46);
              }
              else
              {
                if ( !isdigit((unsigned __int8)v86) )
                  goto LABEL_221;
                if ( v75 == 111 )
                {
                  if ( v86 >= 56 )
                    goto LABEL_221;
                  v44 = 8 * v66;
                }
                else
                {
                  v44 = 10 * v66;
                }
              }
              ++v74;
              v66 = v86 - 48 + v44;
              if ( v71 )
              {
                if ( !--v83 )
                  break;
              }
              ++v85;
              v86 = _inc(stream);
            }
          }
          v20 = (int)v68;
          if ( v76 )
            v66 = -(__int64)v66;
        }
        else
        {
          v20 = (int)v68;
          if ( !v16 )
          {
            while ( 1 )
            {
              if ( v75 == 120 || v75 == 112 )
              {
                if ( !isxdigit((unsigned __int8)v86) )
                {
LABEL_237:
                  --v85;
                  _un_inc(v86, (FILE *)stream);
                  break;
                }
                v47 = 16 * v20;
                v86 = _hextodec(v86);
              }
              else
              {
                if ( !isdigit((unsigned __int8)v86) )
                  goto LABEL_237;
                if ( v75 == 111 )
                {
                  if ( v86 >= 56 )
                    goto LABEL_237;
                  v47 = 8 * v20;
                }
                else
                {
                  v47 = 10 * v20;
                }
              }
              ++v74;
              v20 = v47 + v86 - 48;
              if ( v71 )
              {
                if ( !--v83 )
                  break;
              }
              ++v85;
              v86 = _inc(stream);
            }
          }
          if ( v76 )
            v20 = -v20;
        }
        if ( v75 == 70 )
          v74 = 0;
        if ( !v74 )
          goto $error_return$29126;
        if ( !v81 )
        {
          ++v67;
          v15 = v69;
          goto $assign_num$29279;
        }
LABEL_250:
        ++v79;
        v4 = ++v70;
        goto LABEL_256;
      }
      if ( !v71 )
      {
        ++v83;
        v71 = 1;
      }
    }
    if ( v84 > 0 )
      v78 = 1;
    goto $scanit$29137;
  }
  if ( v18 == 99 || v18 == 123 )
  {
    ++v85;
    v19 = _inc(stream);
  }
  else
  {
    v19 = _whiteout(&v85, (FILE *)stream);
  }
  v86 = v19;
  if ( v19 != -1 )
  {
    v15 = v69;
    v4 = v70;
    goto LABEL_69;
  }
$error_return$29126:
  if ( v65 == 1 )
    free(Block);
  if ( v86 == -1 )
  {
    result = v67;
    if ( !v67 && !v79 )
      result = -1;
    if ( v58 )
      *(_DWORD *)(v57 + 112) &= ~2u;
    return result;
  }
LABEL_273:
  if ( v58 )
    *(_DWORD *)(v57 + 112) &= ~2u;
  return v67;
}

