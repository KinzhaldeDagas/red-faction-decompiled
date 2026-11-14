// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004526E0 rf_control_binding_construct_display_names
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(caller RFString output,binding-context pointer,action-name C-string), plainRET and EAX=output object on every normal
// path. First452680(context,name) searches ascending live signed count3596 for the first case-insensitive name match and supplies signed index; ANY index<=-1 constructs output from
// exact "?" and skips local display-string work. Nonnegative index is not upper-bounded: multiply by28 with32-bit wrap, sign-extend WORD[context+28*index+32] to first code and
// WORD[context+28*index+36] to second code, pass to4525C0/452600 respectively with distinct initially empty RFStrings. First formatter accepts signed0..255, second signed0..4; all
// other codes replace their local with empty and return-1, status ignored here. Accumulator begins empty (PE634CF9 is NUL). Append first name iff case-insensitive RFString-vs-empty
// predicate560AA0 AL nonzero. Append second iff likewise nonempty, preceding it with exact ", " only if first name is also nonempty. All four PE literals634CF9/FA/FB/634D01 are empty
// strings; apparent address differences do not denote distinct text or key sentinels. Copy-CONSTRUCT caller RFString from accumulated text via55F660, then destroy
// secondary,first,accumulator locals in reverse construction order. If both names empty, output is empty rather than "?"; missing lookup alone chooses "?". Output must be
// construction storage: constructors clear buffer pointer without freeing any preexisting owned buffer; this is not safe reassignment of an already owning RFString. No
// output/context/name NULL guard, code validation, text-length cap, dollar delimiter/escaping, numeric action dispatch or global binding update in this body. Three local cleanup
// funclets/states0..2 and original unwind table659200 preserve reverse destruction; output construction is marked separately in local compiler flag. Returns owning output object, not
// local C-string or status.
_DWORD *__cdecl rf_control_binding_construct_display_names(_DWORD *a1, int a2, char *String2)
{
  int v4[2]; // [esp+8h] [ebp-28h] BYREF
  int v5[2]; // [esp+10h] [ebp-20h] BYREF
  char *v6[2]; // [esp+18h] [ebp-18h] BYREF
  int first_action_name_case_insensitive; // [esp+20h] [ebp-10h]
  int v8; // [esp+2Ch] [ebp-4h]

  first_action_name_case_insensitive = rf_control_find_first_action_name_case_insensitive(a2, String2);
  if ( first_action_name_case_insensitive <= -1 )
  {
    rf_string_construct_from_cstr(a1, "?");
    return a1;
  }
  else
  {
    rf_string_construct_from_cstr(v6, (char *)&byte_634CF9);
    v8 = 0;
    rf_string_construct_empty(v4);
    LOBYTE(v8) = 1;
    rf_string_construct_empty(v5);
    LOBYTE(v8) = 2;
    rf_control_assign_code_name_from_table256(v4, *(__int16 *)(a2 + 28 * first_action_name_case_insensitive + 32));
    rf_control_assign_code_name_from_registry5(v5, *(__int16 *)(a2 + 28 * first_action_name_case_insensitive + 36));
    if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v4, (char *)&byte_634CFA) )
      rf_string_append_object_in_place(v6, (int)v4);
    if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v5, (char *)&byte_634CFB) )
    {
      if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v4, (char *)byte_634D01) )
        rf_string_append_cstr_in_place(v6, (int)", ");
      rf_string_append_object_in_place(v6, (int)v5);
    }
    rf_string_copy_construct_from_object(a1, v6);
    LOBYTE(v8) = 1;
    rf_string_destroy_buffer(v5);
    LOBYTE(v8) = 0;
    rf_string_destroy_buffer(v4);
    v8 = -1;
    rf_string_destroy_buffer(v6);
    return a1;
  }
}

