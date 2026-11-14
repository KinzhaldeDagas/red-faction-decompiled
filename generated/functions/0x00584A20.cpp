// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584A20 rf_format_shared_custom_cstring
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Cdecl CUSTOM VARIADIC formatter;old fixed second-int prototype incorrect. NULL format returns empty literal641610 without clearing shared buffer. NonNULL clears first byte of global18CD828 and appends via repeated strlen/strcat/unbounded copies,returns shared buffer (nonreentrant,overwritten by other users). Recognized specifiers and raw stack consumption:%% literal%;%c low byte of one4-byte argument;%d/%i signed32 decimal;%x32-bit lowercase hex,no0x;%k signed byte-count formatter,oneDWORD;%f promotedDOUBLE8 bytes,narrows tofloat then fixed3 decimals;%v BY-VALUE float3 struct12 bytes,formats< ... > at5 decimals;%m BY-VALUE matrix9f36 bytes,prints3 rows at5 decimals with leading newline;%t BY-VALUE RFString8 object8
// bytes,copy-constructs temporary,appends c_str,then destroys temporary;%s C-string pointer4 bytes,NULL substitutes(null). Not printf-compatible for vector/matrix/string object specifiers. Unknown specifier discards percent and next character WITHOUT consuming argument;no widths/flags/precision parser. Trailing bare percent advances past terminatingNUL before outer test,can read beyond format. No destination bound,argument count/type check or format/source alias protection;helper capacity arguments are ignored and float helper uses32-byte local. Returned pointer borrowed global/empty literal,not allocated.
char *rf_format_shared_custom_cstring(const char *a1, ...)
{
  char *v2; // [esp+38h] [ebp-450h]
  float v3; // [esp+58h] [ebp-430h]
  char v4[32]; // [esp+180h] [ebp-308h] BYREF
  char v5[32]; // [esp+1A0h] [ebp-2E8h] BYREF
  char v6[32]; // [esp+1C0h] [ebp-2C8h] BYREF
  int v7; // [esp+1E0h] [ebp-2A8h]
  char v8[64]; // [esp+1E4h] [ebp-2A4h] BYREF
  int v9; // [esp+224h] [ebp-264h]
  float v10[9]; // [esp+228h] [ebp-260h] BYREF
  char Buffer[260]; // [esp+24Ch] [ebp-23Ch] BYREF
  int v12; // [esp+350h] [ebp-138h]
  char v13[256]; // [esp+354h] [ebp-134h] BYREF
  float v14[3]; // [esp+458h] [ebp-30h] BYREF
  _DWORD v15[2]; // [esp+464h] [ebp-24h] BYREF
  const char *v16; // [esp+46Ch] [ebp-1Ch]
  char v17; // [esp+473h] [ebp-15h]
  const char *v18; // [esp+474h] [ebp-14h]
  va_list v19; // [esp+478h] [ebp-10h]
  int v20; // [esp+484h] [ebp-4h]
  va_list va; // [esp+494h] [ebp+Ch] BYREF

  va_start(va, a1);
  if ( !a1 )
    return (char *)&unk_641610;
  va_copy(v19, va);
  v18 = a1;
  unk_18CD828 = 0;
  while ( *v18 )
  {
    if ( *v18 == 37 )
    {
      v17 = *++v18;
      ++v18;
      switch ( v17 )
      {
        case '%':
          *(_WORD *)(&unk_18CD828 + strlen(&unk_18CD828)) = 37;
          break;
        case 'c':
          v7 = &unk_18CD828 + strlen(&unk_18CD828) + 1 - unk_18CD829;
          v19 += 4;
          *(&unk_18CD828 + v7) = *(v19 - 4);
          unk_18CD829[v7] = 0;
          break;
        case 'd':
        case 'i':
          v19 += 4;
          rf_format_signed_decimal_cstring(v6, 32, *((_DWORD *)v19 - 1));
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), v6, &v6[strlen(v6) + 1] - v6);
          break;
        case 'f':
          v19 += 8;
          v3 = *((double *)v19 - 1);
          rf_format_float_fixed_cstring(v4, 32, v3, 3);
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), v4, &v4[strlen(v4) + 1] - v4);
          break;
        case 'k':
          v19 += 4;
          v9 = *((_DWORD *)v19 - 1);
          rf_format_byte_count_cstring(v8, 64, v9);
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), v8, &v8[strlen(v8) + 1] - v8);
          break;
        case 'm':
          v12 = 5;
          v19 += 36;
          rf_matrix3_copy_construct((int)v10, v19 - 36);
          sprintf(Buffer, "\n| %.*f %.*f %.*f |\n", v12, v10[0], v12, v10[1], v12, v10[2]);
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), Buffer, &Buffer[strlen(Buffer) + 1] - Buffer);
          sprintf(Buffer, "| %.*f %.*f %.*f |\n", v12, v10[3], v12, v10[4], v12, v10[5]);
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), Buffer, &Buffer[strlen(Buffer) + 1] - Buffer);
          sprintf(Buffer, "| %.*f %.*f %.*f |\n", v12, v10[6], v12, v10[7], v12, v10[8]);
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), Buffer, &Buffer[strlen(Buffer) + 1] - Buffer);
          break;
        case 's':
          v19 += 4;
          v16 = *((const char **)v19 - 1);
          if ( v16 )
            strcat(&unk_18CD828, v16);
          else
            strcat(&unk_18CD828, "(null)");
          break;
        case 't':
          v19 += 8;
          rf_string_copy_construct_from_object(v15, (char **)v19 - 2);
          v20 = 0;
          strcat(&unk_18CD828, rf_string_object_c_str_or_empty(v15));
          v20 = -1;
          rf_string_destroy_buffer(v15);
          break;
        case 'v':
          v19 += 12;
          rf_vector3_copy_return_destination(v14, (float *)v19 - 3);
          rf_format_vector3_fixed_cstring(v13, 256, v14, 5);
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), v13, &v13[strlen(v13) + 1] - v13);
          break;
        case 'x':
          v19 += 4;
          sprintf(v5, "%x", *((_DWORD *)v19 - 1));
          qmemcpy(&unk_18CD828 + strlen(&unk_18CD828), v5, &v5[strlen(v5) + 1] - v5);
          break;
        default:
          continue;
      }
    }
    else
    {
      v2 = &unk_18CD828 + strlen(&unk_18CD828) + 1;
      *(&unk_18CD828 + v2 - unk_18CD829) = *v18++;
      *v2 = 0;
    }
  }
  return &unk_18CD828;
}

