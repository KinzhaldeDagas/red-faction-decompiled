// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F4CF0 rf_ui_inputbox_parse_rejected_character_ranges
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Writes expanded reject-string at1144. Parses character-set expression into128-byte stack membership map,then emits selected characters in fixed95-byte alphabet0x6470C8. Supports inclusive digit/uppercase/lowercase ranges with endpoints normalized (9-0 accepted);range endpoint must have same character class. Dangling alphanumeric range or cross-class range returns0;double hyphen after a pending class commits literal hyphen and prior endpoint. Nonclass characters use pending-literal states;no general escape grammar. NULL returns0,empty produces empty string with success. Failure occurs before output write,leaving prior set. Map index casts input to unsignedBYTE without a <128 guard;high-byte membership writes can exceed128-byte map. Final alphabet excludes ampersand and includes caret twice,so
// selecting caret emits duplicate carets and selected ampersand is omitted. Only alphabet characters emitted,not full128/256 set. Returns1 on success;no text sanitization or event.
int __thiscall rf_ui_inputbox_parse_rejected_character_ranges(_BYTE *this, const char *a2)
{
  int result; // eax
  char v3; // [esp+16h] [ebp-D2h]
  char v4; // [esp+17h] [ebp-D1h]
  char v5; // [esp+1Eh] [ebp-CAh]
  char v6; // [esp+1Fh] [ebp-C9h]
  char v7; // [esp+26h] [ebp-C2h]
  char v8; // [esp+27h] [ebp-C1h]
  int v10; // [esp+44h] [ebp-A4h]
  int v11; // [esp+48h] [ebp-A0h]
  char j; // [esp+4Fh] [ebp-99h]
  char k; // [esp+4Fh] [ebp-99h]
  char m; // [esp+4Fh] [ebp-99h]
  _BYTE v15[45]; // [esp+50h] [ebp-98h]
  char v16; // [esp+7Dh] [ebp-6Bh]
  char v17; // [esp+DBh] [ebp-Dh]
  unsigned int i; // [esp+DCh] [ebp-Ch]
  unsigned int v19; // [esp+E0h] [ebp-8h]
  char v20; // [esp+E7h] [ebp-1h]

  v11 = 0;
  if ( !a2 )
    return 0;
  v19 = strlen(a2);
  for ( i = 0; i < 0x80; ++i )
    v15[i] = 0;
  i = 0;
  while ( i <= v19 )
  {
    if ( !a2[i] )
    {
      switch ( v11 )
      {
        case 0:
          goto LABEL_7;
        case 2:
        case 4:
        case 6:
          result = 0;
          break;
        default:
          v15[(unsigned __int8)a2[i - 1]] = 1;
          goto LABEL_7;
      }
      return result;
    }
    if ( isdigit(a2[i]) )
    {
      switch ( v11 )
      {
        case 0:
          v11 = 1;
          goto LABEL_7;
        case 2:
          if ( a2[i - 2] >= a2[i] )
            v8 = a2[i];
          else
            v8 = a2[i - 2];
          v20 = v8;
          if ( a2[i - 2] < a2[i] )
            v7 = a2[i];
          else
            v7 = a2[i - 2];
          v17 = v7;
          for ( j = v20; j <= v17; ++j )
            v15[(unsigned __int8)j] = 1;
          v11 = 0;
          goto LABEL_7;
        case 4:
        case 6:
          result = 0;
          break;
        case 7:
          result = 0;
          break;
        default:
          v15[(unsigned __int8)a2[i - 1]] = 1;
          v11 = 1;
          goto LABEL_7;
      }
      return result;
    }
    if ( isupper(a2[i]) )
    {
      switch ( v11 )
      {
        case 0:
          v11 = 3;
          goto LABEL_7;
        case 2:
        case 6:
          result = 0;
          break;
        case 4:
          if ( a2[i - 2] >= a2[i] )
            v6 = a2[i];
          else
            v6 = a2[i - 2];
          v20 = v6;
          if ( a2[i - 2] < a2[i] )
            v5 = a2[i];
          else
            v5 = a2[i - 2];
          v17 = v5;
          for ( k = v20; k <= v17; ++k )
            v15[(unsigned __int8)k] = 1;
          v11 = 0;
          goto LABEL_7;
        case 7:
          result = 0;
          break;
        default:
          v15[(unsigned __int8)a2[i - 1]] = 1;
          v11 = 3;
          goto LABEL_7;
      }
      return result;
    }
    if ( islower(a2[i]) )
    {
      switch ( v11 )
      {
        case 0:
          v11 = 5;
          goto LABEL_7;
        case 2:
        case 4:
          result = 0;
          break;
        case 6:
          if ( a2[i - 2] >= a2[i] )
            v4 = a2[i];
          else
            v4 = a2[i - 2];
          v20 = v4;
          if ( a2[i - 2] < a2[i] )
            v3 = a2[i];
          else
            v3 = a2[i - 2];
          v17 = v3;
          for ( m = v20; m <= v17; ++m )
            v15[(unsigned __int8)m] = 1;
          v11 = 0;
          goto LABEL_7;
        case 7:
          result = 0;
          break;
        default:
          v15[(unsigned __int8)a2[i - 1]] = 1;
          v11 = 5;
          goto LABEL_7;
      }
      return result;
    }
    switch ( v11 )
    {
      case 0:
        v11 = 8;
        goto LABEL_7;
      case 1:
        if ( a2[i] == 45 )
        {
          v11 = 2;
        }
        else
        {
          v15[(unsigned __int8)a2[i - 1]] = 1;
          v11 = 8;
        }
        goto LABEL_7;
      case 2:
      case 4:
      case 6:
        if ( a2[i] != 45 )
          return 0;
        v16 = 1;
        v15[(unsigned __int8)a2[i - 2]] = 1;
        v11 = 0;
LABEL_7:
        ++i;
        break;
      case 3:
        if ( a2[i] == 45 )
        {
          v11 = 4;
        }
        else
        {
          v15[(unsigned __int8)a2[i - 1]] = 1;
          v11 = 8;
        }
        goto LABEL_7;
      case 5:
        if ( a2[i] == 45 )
        {
          v11 = 6;
        }
        else
        {
          v15[(unsigned __int8)a2[i - 1]] = 1;
          v11 = 8;
        }
        goto LABEL_7;
      case 7:
        v16 = 1;
        v11 = 0;
        goto LABEL_7;
      default:
        v15[(unsigned __int8)a2[i - 1]] = 1;
        if ( a2[i] == 45 )
          v11 = 7;
        else
          v11 = 8;
        goto LABEL_7;
    }
  }
  i = 0;
  v10 = 0;
  while ( i < strlen(" !\"#$%^'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~") )
  {
    if ( v15[(unsigned __int8)a0123456789Abcd[i]] )
    {
      *(this + v10 + 1144) = a0123456789Abcd[i];
      ++v10;
    }
    ++i;
  }
  *(this + v10 + 1144) = 0;
  return 1;
}

