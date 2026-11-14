// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004545C0 rf_save_list_a_load_selected
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No incoming arguments consumed; callers454890 push two ignored DWORD slots. Signed selected6F1FA0 must be>=0 and <LIVE firstDWORD count of record
// array6F21AC; reject before path work otherwise. Unbounded byte-copy prefix C string AT88E7D0 into local FileName, append selected272-byte record filename includingNUL, without
// separator insertion or local capacity checks. Calls4F35B0(path,local260-byte levelOutput,NULL floatOutput,NULL titleOutput); only nonzero AL proceeds. Constructs local RFString
// level and path, then TWO8-byte by-value outgoing RFString copies (path first constructed, level next);4798E0 receives16 bytes and owns outgoing cleanup. Requests immediate panel5
// force0, ignores admission result, and unconditionally copies path includingNUL into global890400 before destroying local path then level. No explicit current-level destruction,
// music stop, client-entry4494C0 call or rollback on refused panel request. C++ states/unwind PE6592D8 map0->-1(level623A40),1->0(path623A4B),2->1(outgoing path623A56); state2
// protects first outgoing copy while second constructs, lowered to1 before transfer. Normal restores fs:0/security cookie; no defined application result. Validator failure may have
// altered only its own outputs, not admission to later string/queue/global-path operations.
void rf_save_list_a_load_selected()
{
  int v0; // eax
  int v1; // eax
  int v2[2]; // [esp-10h] [ebp-298h] BYREF
  int v3[5]; // [esp-8h] [ebp-290h] BYREF
  char v4; // [esp+Fh] [ebp-279h]
  char *v5; // [esp+10h] [ebp-278h]
  char *v6; // [esp+14h] [ebp-274h]
  char *v7; // [esp+18h] [ebp-270h]
  int v8; // [esp+1Ch] [ebp-26Ch]
  int v9; // [esp+20h] [ebp-268h]
  int v10; // [esp+24h] [ebp-264h]
  char *v12; // [esp+2Ch] [ebp-25Ch]
  unsigned int v13; // [esp+30h] [ebp-258h]
  const void *v14; // [esp+34h] [ebp-254h]
  const char *v15; // [esp+3Ch] [ebp-24Ch]
  const char *v16; // [esp+40h] [ebp-248h]
  CHAR v17; // [esp+47h] [ebp-241h]
  char *v18; // [esp+48h] [ebp-240h]
  char *v19; // [esp+4Ch] [ebp-23Ch]
  CHAR *v20; // [esp+50h] [ebp-238h]
  int *v21; // [esp+54h] [ebp-234h]
  void *v22; // [esp+58h] [ebp-230h]
  char *v23[2]; // [esp+5Ch] [ebp-22Ch] BYREF
  char *v24; // [esp+64h] [ebp-224h] BYREF
  char v25; // [esp+6Bh] [ebp-21Dh] BYREF
  char FileName[264]; // [esp+6Ch] [ebp-21Ch] BYREF
  char Source[260]; // [esp+174h] [ebp-114h] BYREF
  int v28; // [esp+284h] [ebp-4h]

  if ( unk_6F1FA0 >= 0 && unk_6F1FA0 < rf_receiver_get_first_dword(dword_6F21AC) )
  {
    v20 = MEMORY[0x88E7D0];
    v19 = FileName;
    v18 = FileName;
    do
    {
      v17 = *v20;
      *v19 = v17;
      ++v20;
      ++v19;
    }
    while ( v17 );
    v15 = (const char *)rf_record272_array_element_address_unchecked(dword_6F21AC, unk_6F1FA0);
    v16 = &v15[strlen(v15) + 1];
    v14 = v15;
    v13 = v16 - v15;
    v12 = &v25;
    while ( *++v12 )
      ;
    qmemcpy(v12, v14, v13);
    if ( rf_savegame_validate_headers_and_read_info(FileName, Source, nullptr, nullptr) )
    {
      rf_string_construct_from_cstr(v23, Source);
      v28 = 0;
      rf_string_construct_from_cstr(&v24, FileName);
      LOBYTE(v28) = 1;
      v22 = v3;
      rf_string_copy_construct_from_object(v3, &v24);
      v10 = v0;
      v9 = v0;
      LOBYTE(v28) = 2;
      v21 = v2;
      rf_string_copy_construct_from_object(v2, v23);
      v8 = v1;
      LOBYTE(v28) = 1;
      rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
      rf_ui_request_panel_immediate(5, 0);
      v7 = FileName;
      v6 = &unk_890400;
      v5 = &unk_890400;
      do
      {
        v4 = *v7;
        *v6 = v4;
        ++v7;
        ++v6;
      }
      while ( v4 );
      LOBYTE(v28) = 0;
      rf_string_destroy_buffer(&v24);
      v28 = -1;
      rf_string_destroy_buffer(v23);
    }
  }
}

