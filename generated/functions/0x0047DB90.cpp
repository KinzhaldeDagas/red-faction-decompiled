// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047DB90 rf_rfl_validate_header_and_read_prelude
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl(stream,error-buffer Cstring destination), AL Boolean. Requires first int32 magic0xD4BADA55. Reads signed version into global6FC310; accepts inclusive40..200, sets stream
// version. Reads uint32 global6FC334(min114,default0), int32 globals6FCCA4 and6FCCB0(min0,default0),6FCCAC(min160,default35),6FCCB4(min160,default0). These mutations occur before mod
// compatibility failure and are not rolled back.
// Reads title via u16-length helper capacity256,min170,fallback '<untitled>'. Searches 'XSTR(' ANYWHERE; if found advances5, overwrites LAST byte of whole title with NUL without
// validating closing parenthesis, and atoi parses suffix. Negative id assigns '?'; nonnegative directly indexes localization pointer table88D438 without upper bound. Otherwise
// assigns title literally to RFString6FC314. Case-insensitive 'Blasted Canyon' then replaced with localized pointer88DFD0.
// Reads required-mod string capacity31,min178,fallback empty. Copies enabled archive basename into local32-byte buffer through helper with NO capacity parameter; ignores helper
// status. Accepts case-insensitive match OR empty required mod. Failure sprintf writes unbounded caller error buffer and returns0; magic/version errors likewise format messages, with
// no buffer-size argument. Success saves current offset, seeks origin0 to global6FCCB0, invokes prelude parser47DF60, seeks back to saved offset and returns1. Does not check either
// seek or parser's internal header status; success leaves caller error buffer untouched. No full-level payload validation here.
char __cdecl rf_rfl_validate_header_and_read_prelude(_DWORD *a1, char *Buffer)
{
  const char *v3; // eax
  int v4; // [esp+28h] [ebp-138h]
  int Offset; // [esp+2Ch] [ebp-134h]
  char String1[32]; // [esp+34h] [ebp-12Ch] BYREF
  int v7; // [esp+54h] [ebp-10Ch]
  char String2; // [esp+58h] [ebp-108h] BYREF
  _BYTE v9[3]; // [esp+59h] [ebp-107h] BYREF
  char *String; // [esp+15Ch] [ebp-4h]

  if ( rf_binary_stream_read_int32_versioned(a1, 0, 0) == -725951915 )
  {
    dword_6FC310 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    if ( dword_6FC310 >= 40 )
    {
      if ( dword_6FC310 <= 200 )
      {
        rf_vfile_set_open_slot_version(a1, dword_6FC310);
        unk_6FC334 = rf_binary_stream_read_uint32_versioned(a1, 114, 0);
        unk_6FCCA4 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
        MEMORY[0x6FCCB0] = rf_binary_stream_read_int32_versioned(a1, 0, 0);
        unk_6FCCAC = rf_binary_stream_read_int32_versioned(a1, 160, 35);
        unk_6FCCB4 = rf_binary_stream_read_int32_versioned(a1, 160, 0);
        rf_binary_stream_read_u16_string_to_buffer(a1, &String2, 256, 170, "<untitled>");
        String = rf_cstring_find_first_substring(&String2, "XSTR(");
        if ( String )
        {
          String += 5;
          *((_BYTE *)&v7 + &v9[strlen(&String2)] - v9 + 3) = 0;
          v4 = atoi(String);
          if ( v4 >= 0 )
            rf_string_assign_from_cstr(unk_6FC314, (char *)unk_88D438[v4]);
          else
            rf_string_assign_from_cstr(unk_6FC314, "?");
        }
        else
        {
          rf_string_assign_from_cstr(unk_6FC314, &String2);
        }
        v3 = rf_string_object_c_str_or_empty(unk_6FC314);
        if ( !_stricmp("Blasted Canyon", v3) )
          rf_string_assign_from_cstr(unk_6FC314, unk_88DFD0);
        rf_binary_stream_read_u16_string_to_buffer(a1, &String2, 31, 178, (char *)&byte_6387ED);
        v7 = rf_command_line_copy_enabled_archive_basename(String1);
        if ( !_stricmp(String1, &String2) || !_stricmp(&String2, &byte_6387EE) )
        {
          Offset = rf_vfile_get_open_slot_offset(a1);
          rf_vfile_seek(a1, MEMORY[0x6FCCB0], 0);
          rf_rfl_prelude_metadata_read((int)a1);
          rf_vfile_seek(a1, Offset, 0);
          return 1;
        }
        else
        {
          sprintf(Buffer, "Level needs mod: %s\nGame is using mod: %s", &String2, String1);
          return 0;
        }
      }
      else
      {
        sprintf(Buffer, "Unsupported version (%d)\n", dword_6FC310);
        return 0;
      }
    }
    else
    {
      sprintf(Buffer, "Unsupported version (%d)\n", dword_6FC310);
      return 0;
    }
  }
  else
  {
    sprintf(Buffer, "Verification failed. Not a valid level file.");
    return 0;
  }
}

