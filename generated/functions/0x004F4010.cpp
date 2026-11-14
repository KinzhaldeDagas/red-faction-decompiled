// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F4010 rf_savegame_pack_player_subrecord
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Pack player subrecord at save-header+62232, only when player pointer and resolved player entity exist. Save associated owner as stable id+0; low16 player fields+200..212 at+4..10; float+216 at+12; bounded31-byte player name at+20; flags low word+52, field+4600 word+54, player entity stable id+56, bytes player+24/+40 at+60/+61, vector+28 at+64. Pack32 presence bytes as one dword+76, selected monitor stable id+80,32 low-byte values from player+4436 at+84, orientation+4084 at+116 and vector+4120 at+152. Byte+172 low4 bits encode player+4156/+4164, entity+2000 mask0x10000 and shared undercover-mode LSB; higher bits preserved from existing output. Runtime restore consumes only subset of these fields.
void __cdecl rf_savegame_pack_player_subrecord(int a1, int a2)
{
  char v2; // [esp+Bh] [ebp-2Dh]
  _BYTE *v3; // [esp+10h] [ebp-28h]
  const char *v4; // [esp+14h] [ebp-24h]
  float v5[3]; // [esp+18h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-14h] BYREF
  int i; // [esp+30h] [ebp-8h]
  _DWORD *v8; // [esp+34h] [ebp-4h]

  if ( a2 )
  {
    v8 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(a2 + 20));
    if ( v8 )
    {
      *(_DWORD *)a1 = rf_object_runtime_identifier_to_saved_identifier(v8[128]);
      *(_WORD *)(a1 + 4) = *(_WORD *)(a2 + 200);
      *(_WORD *)(a1 + 6) = *(_WORD *)(a2 + 204);
      *(_WORD *)(a1 + 8) = *(_WORD *)(a2 + 208);
      *(_WORD *)(a1 + 10) = *(_WORD *)(a2 + 212);
      *(float *)(a1 + 12) = *(float *)(a2 + 216);
      if ( (int)rf_string_length_from_cstr((const char **)(a2 + 8)) < 32 )
      {
        v4 = rf_string_object_c_str_or_empty((const void *)(a2 + 8));
        v3 = (_BYTE *)(a1 + 20);
        do
        {
          v2 = *v4;
          *v3++ = *v4++;
        }
        while ( v2 );
      }
      else
      {
        qmemcpy((void *)(a1 + 20), rf_string_object_c_str_or_empty((const void *)(a2 + 8)), 0x1Fu);
        *(_BYTE *)(a1 + 51) = 0;
      }
      *(_WORD *)(a1 + 52) = *(_WORD *)(a2 + 16);
      *(_WORD *)(a1 + 54) = *(_WORD *)(a2 + 4600);
      *(_DWORD *)(a1 + 56) = v8[8];
      *(_BYTE *)(a1 + 60) = *(_BYTE *)(a2 + 24);
      *(_BYTE *)(a1 + 61) = *(_BYTE *)(a2 + 40);
      rf_vector_copy((float *)(a1 + 64), copy_result, (const float *)(a2 + 28));
      *(_DWORD *)(a1 + 76) = 0;
      for ( i = 0; i < 32; ++i )
        *(_DWORD *)(a1 + 76) |= (*(_BYTE *)(i + a2 + 80) != 0) << i;
      *(_DWORD *)(a1 + 80) = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(a2 + 180));
      for ( i = 0; i < 32; ++i )
        *(_BYTE *)(i + a1 + 84) = *(_BYTE *)(a2 + 4 * i + 4436);
      rf_vector_copy((float *)(a1 + 152), v5, (const float *)(a2 + 4120));
      rf_matrix3_copy((float *)(a1 + 116), (const float *)(a2 + 4084));
      *(_BYTE *)(a1 + 172) = (*(_BYTE *)(a2 + 4156) != 0) | *(_BYTE *)(a1 + 172) & 0xFE;
      *(_BYTE *)(a1 + 164) = *(_BYTE *)(a2 + 4160);
      *(_BYTE *)(a1 + 172) = (2 * (*(_BYTE *)(a2 + 4164) != 0)) | *(_BYTE *)(a1 + 172) & 0xFD;
      *(_BYTE *)(a1 + 172) = (4 * ((v8[500] & 0x10000) != 0)) | *(_BYTE *)(a1 + 172) & 0xFB;
      *(_BYTE *)(a1 + 172) = (8 * (unk_87FC0C & 1)) | *(_BYTE *)(a1 + 172) & 0xF7;
    }
  }
}

