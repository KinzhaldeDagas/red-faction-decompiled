// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00451750 rf_input_bindings_initialize_defaults
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(bindingContext), one DWORD, no NULL guard. First resets count DWORDcontext+3596=0. Makes29
// ordered4516A0 appends using LIVE localized labels (embedded English alternatives are unreachable constant-zero branches). Tuple(mode,key1,mouse) by ordinal
// is:0(1,-1,0),1(1,-1,1),2(0,28,-1),3(0,57,-1),4(1,46,-1),5(0,35,-1),6(0,19,-1),7(0,-1,4),8(0,-1,3),9(0,20,-1),10(0,21,-1),11(1,17,-1),12(1,31,-1),13(1,30,-1),14(1,32,-1),15(1,78,-1),16(1,156,-1),17(1,72,-1),18(1,80,-1),19(1,75,-1),20(1,77,-1),21(0,50,-1),22(1,15,-1),23(0,64,-1),24(0,67,-1),25(0,2,-1),26(0,3,-1),27(0,4,-1),28(0,5,-1);
// key2 ALWAYS-1. Labels respectively come from
// DWORD88E0D4,D8,88D684,688,68C,88E0DC,88D694,698,88E0E0,88E0BC,C0,C4,C8,88E0E4,E8,EC,F0,F4,F8,FC,88E100,88D6A8,88E104,108,10C,358,35C,360,364. Appender writes authored/current
// binding WORDs, DWORD mode and RFString label and increments live count; this caller ignores all append returns. Then scans up to32 cycle slots with16-byte stride, stopping ONLY on
// exact weapon-index-1. For each other raw index forms display RFString address by1360*index, obtains C string, appends(mode0,key1=-1,key2=-1,mouse=-1); no weapon-range or duplicate
// validation. Writes FLOAT32 context0=0.20000000298023224. For four16-byte axis records atcontext+3600, copies only enableBYTE+0,invertBYTE+1,sourceDWORD+4 from PE634AA8;
// defaults(1,0,0),(1,0,1),(0,0,-1),(0,0,-1). Other axis-record bytes, context+4/+8, and rows beyond new count are untouched here; row RFStrings are assigned rather than constructed
// by this body. Returns incidental full EAX48 from final source-indexed store, regardless of appender results.
int __cdecl rf_input_bindings_initialize_defaults(int a1)
{
  int result; // eax
  char *v2; // eax
  int i; // [esp+74h] [ebp-4h]
  int j; // [esp+74h] [ebp-4h]

  *(_DWORD *)(a1 + 3596) = 0;
  rf_binding_context_append_named_triplet_record(a1, unk_88E0D4, 1, -1, -1, 0);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0D8, 1, -1, -1, 1);
  rf_binding_context_append_named_triplet_record(a1, unk_88D684, 0, 28, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88D688, 0, 57, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88D68C, 1, 46, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0DC, 0, 35, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88D694, 0, 19, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88D698, 0, -1, -1, 4);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0E0, 0, -1, -1, 3);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0BC, 0, 20, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0C0, 0, 21, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0C4, 1, 17, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0C8, 1, 31, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0E4, 1, 30, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0E8, 1, 32, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0EC, 1, 78, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0F0, 1, 156, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0F4, 1, 72, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0F8, 1, 80, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E0FC, 1, 75, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E100, 1, 77, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88D6A8, 0, 50, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E104, 1, 15, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E108, 0, 64, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E10C, 0, 67, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E358, 0, 2, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E35C, 0, 3, -1, -1);
  rf_binding_context_append_named_triplet_record(a1, unk_88E360, 0, 4, -1, -1);
  result = rf_binding_context_append_named_triplet_record(a1, unk_88E364, 0, 5, -1, -1);
  for ( i = 0; i < 32 && rf_weapon_cycle_slots_weapon_index[4 * i] != -1; ++i )
  {
    v2 = (char *)rf_string_object_c_str_or_empty((char *)&rf_weapon_records_display_name + 1360
                                                                                         * rf_weapon_cycle_slots_weapon_index[4 * i]);
    rf_binding_context_append_named_triplet_record(a1, v2, 0, -1, -1, -1);
    result = i + 1;
  }
  *(float *)a1 = 0.2;
  for ( j = 0; j < 4; ++j )
  {
    *(_BYTE *)(a1 + 16 * j + 3600) = byte_634AA8[16 * j];
    *(_BYTE *)(a1 + 16 * j + 3601) = byte_634AA9[16 * j];
    result = 16 * j;
    *(_DWORD *)(a1 + 16 * j + 3604) = dword_634AAC[4 * j];
  }
  return result;
}

