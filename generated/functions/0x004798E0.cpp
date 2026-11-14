// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004798E0 rf_level_transition_assign_level_and_save_strings
// UNREALRED VERIFIED [event-registry-crc-20261028]: Assigns by-value RF string argument at stack+4 to global string0x6FC300, and RF string at stack+12 to0x6FC2F8 through0x55FF10, then destroys both argument strings through0x55F6D0. Each string occupies two dwords; decompiled three-int prototype obscures the by-value string ABI. Save-load callers supply level name and save path. No loading or panel change in this body.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Cdecl16-byte stack ABI verified atALL24 native call sites,eachdirectCALL followedby ADDESP,0x10. FourrawDWORD fields represent TWO8-byte by-value RFStrings:level(extent,buffer) at[EBP+8/+12],save(extent,buffer) at[EBP+16/+20]. Assign firstobject toglobal6FC300,second toglobal6FC2F8 through55FF10;destroy BOTH stackobjects through55F6D0,normal orderlevelthensave;SEH coversconstructed arguments. Returnvoid,no callee stackpop. Corrected previous three-DWORD IDA prototype tofour rawfields(int,char*,int,char*) withoutinventing a localRFStringtype. This exposes all16 suppliedbytes while preserving logical two-object ownership. No loading,panelchange,cacheclear,NULL/extentrepair orbufferborrow guarantee
// here;copiesglobals before destroying inputs. All24 call sites in21 unique callerfunctions freshly decompiled aftercorrection.
void __cdecl rf_level_transition_assign_level_and_save_strings(
        int level_extent,
        char *level_buffer,
        int save_extent,
        char *save_buffer)
{
  rf_string_assign_from_object(unk_6FC300, (int)&level_extent);
  rf_string_assign_from_object(unk_6FC2F8, (int)&save_extent);
  rf_string_destroy_buffer(&level_extent);
  rf_string_destroy_buffer(&save_extent);
}

